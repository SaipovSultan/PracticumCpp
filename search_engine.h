#ifndef YANDEXPRACTICUMCPP_SEARCHENGINE_H
#define YANDEXPRACTICUMCPP_SEARCHENGINE_H

#endif //YANDEXPRACTICUMCPP_SEARCHENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <optional>
#include <tuple>

const int MAX_RESULT_DOCUMENT_COUNT = 5;

std::string ReadLine();

int ReadLineWithNumber();

std::vector<std::string> SplitIntoWords(const std::string&);

struct Document {
    explicit Document() : id(0), relevance(0), rating(0) {}
    explicit Document(int id, double relevance, int rating) : id(id), relevance(relevance), rating(rating) {}
    int id;
    double relevance;
    int rating;
};

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

template <typename StringContainer>
std::set<std::string> MakeUniqueNonEmptyStrings(const StringContainer& strings){
    std::set<std::string> non_empty_strings;
    for(const std::string str : strings){
        if(!str.empty()){
            non_empty_strings.insert(str);
        }
    }
    return non_empty_strings;
}

class SearchServer {
public:

    inline static constexpr int INVALID_DOCUMENT_ID = -1;

    SearchServer() = default;

    template <typename StringContainer>
    explicit SearchServer(const StringContainer& stop_words) : stop_words_(MakeUniqueNonEmptyStrings(stop_words)){}

    explicit SearchServer(const std::string& stop_words_text) : SearchServer(SplitIntoWords(stop_words_text)) {}

    void SetStopWords(const std::string&);

    void AddDocument(int, const std::string&, DocumentStatus, const std::vector<int>&);

    template <typename DocumentPredicate>
    std::vector<Document> FindTopDocuments(const std::string& raw_query, DocumentPredicate document_predicate) const {
        const Query query = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query, document_predicate);

        std::sort(matched_documents.begin(), matched_documents.end(),
                  [](const Document& lhs, const Document& rhs) {
                      if (abs(lhs.relevance - rhs.relevance) < 1e-6) {
                          return lhs.rating > rhs.rating;
                      } else {
                          return lhs.relevance > rhs.relevance;
                      }
                  });
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }

    std::vector<Document> FindTopDocuments(const std::string&, DocumentStatus) const;

    std::vector<Document> FindTopDocuments(const std::string&) const;

    int GetDocumentCount() const;

    std::tuple<std::vector<std::string>, DocumentStatus>  MatchDocument(const std::string&, int) const;

    int GetDocumentId(size_t) const;

    static bool IsValidWord(const std::string& word) {
        return std::none_of(word.cbegin(), word.cend(),[](char c){
            return c >= '\0' && c < ' ';
        });
    }

    struct DocumentData {
        int rating;
        DocumentStatus status;
    };

    struct QueryWord {
        std::string data;
        bool is_minus;
        bool is_stop;
    };

    struct Query {
        std::set<std::string> plus_words;
        std::set<std::string> minus_words;
    };

private:

    std::set<std::string> stop_words_;
    std::map<std::string, std::map<int, double>> word_to_document_freqs_;
    std::map<int, DocumentData> documents_;
    std::vector<int> document_ids_;

    bool IsStopWord(const std::string&) const;

    std::vector<std::string> SplitIntoWordsNoStop(const std::string&) const;

    static int ComputeAverageRating(const std::vector<int>& ratings){
        if (ratings.empty()) {
            return 0;
        }
        return std::accumulate(ratings.cbegin(), ratings.cend(), .0) / static_cast<int>(ratings.size());
    }

    QueryWord ParseQueryWord(std::string text) const;

    Query ParseQuery(const std::string& text) const;

    double ComputeWordInverseDocumentFreq(const std::string&) const;

    template <typename DocumentPredicate>
    std::vector<Document> FindAllDocuments(const Query& query, DocumentPredicate document_predicate) const {
        std::map<int, double> document_to_relevance;
        for (const std::string& word : query.plus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            const double inverse_document_freq = ComputeWordInverseDocumentFreq(word);
            for (const auto [document_id, term_freq] : word_to_document_freqs_.at(word)) {
                const auto& document_data = documents_.at(document_id);
                if (document_predicate(document_id, document_data.status, document_data.rating)) {
                    document_to_relevance[document_id] += term_freq * inverse_document_freq;
                }
            }
        }

        for (const std::string& word : query.minus_words) {
            if (word_to_document_freqs_.count(word) == 0) {
                continue;
            }
            for (const auto [document_id, _] : word_to_document_freqs_.at(word)) {
                document_to_relevance.erase(document_id);
            }
        }
        std::vector<Document> matched_documents;
        for (const auto [document_id, relevance] : document_to_relevance) {
            matched_documents.push_back(Document{
                    document_id,
                    relevance,
                    documents_.at(document_id).rating
            });
        }
        return matched_documents;
    }
};

void PrintDocument(const Document&);