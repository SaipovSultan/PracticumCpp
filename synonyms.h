#ifndef YANDEXPRACTICUMCPP_SYNONYMS_H
#define YANDEXPRACTICUMCPP_SYNONYMS_H

#endif //YANDEXPRACTICUMCPP_SYNONYMS_H

#include <map>
#include <set>
#include <string>
#include <string_view>
#include <deque>

class Synonyms{
public:
    void Add(const std::string& first_word, const std::string& second_word){
        std::string_view first_word_sv = GetCopyString(std::string_view(first_word));
        std::string_view second_word_sv = GetCopyString(std::string_view(second_word));
        synonyms_[first_word_sv].insert(second_word_sv);
        synonyms_[second_word_sv].insert(first_word_sv);
    }

    size_t GetSynonymCount(const std::string& word) const{
        if(auto it = synonyms_.find(std::string_view(word));it != synonyms_.end()){
            return it->second.size();
        }
        return 0;
    }

    bool AreSynonyms(const std::string& first_word, const std::string& second_word) const{
        if(auto it = synonyms_.find(std::string_view(first_word));it != synonyms_.end()){
            return it->second.count(second_word);
        }
        return false;
    }
private:
    std::map<std::string_view, std::set<std::string_view>> synonyms_;
    std::deque<std::string> data;
    std::string_view GetCopyString(const std::string_view& sv){
        if(auto it = synonyms_.find(sv);it == synonyms_.end()){
            return data.emplace_back(std::string(sv));
        }else{
            return it->first;
        }
    }
};