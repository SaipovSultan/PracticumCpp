//
// Created by Progs on 12.04.2022.
//

#ifndef PRACTICUMCPP_PAGINATOR_H
#define PRACTICUMCPP_PAGINATOR_H

#include <vector>
#include <stdexcept>


template <typename Iterator>
struct IteratorRange{
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end){}
    Iterator begin(){
        return begin_;
    }
    Iterator end(){
        return end_;
    }
    Iterator begin() const{
        return begin_;
    }
    Iterator end() const{
        return end_;
    }
private:
    Iterator begin_, end_;
};

template <typename Iterator>
class Paginator{
public:
    Paginator(Iterator begin, Iterator end, size_t page_size){
        if(page_size == 0){
            throw std::invalid_argument("Invalid argument");
        }

        auto distance = std::distance(begin, end);
        auto page_cnt = distance / page_size;
        for(size_t cnt = 0;cnt < page_cnt;++cnt){
            auto page_end = std::next(begin, page_size);
            pages.emplace_back(begin, page_end);
            begin = page_end;
        }
        if(begin != end){
            pages.emplace_back(begin, end);
        }
    }
    auto begin(){
        return pages.begin();
    }
    auto end(){
        return pages.end();
    }
    auto begin() const{
        return pages.cbegin();
    }
    auto end() const{
        return pages.cend();
    }

private:
    std::vector<IteratorRange<Iterator>> pages;
};

template <typename Iterator>
Paginator<Iterator> paginate(Iterator begin, Iterator end, size_t page_size){
    return Paginator<Iterator>(begin, end, page_size);
}
#endif //PRACTICUMCPP_PAGINATOR_H
