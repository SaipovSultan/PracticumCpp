#ifndef YANDEXPRACTICUMCPP_COLLECTIONSTREAM_H
#define YANDEXPRACTICUMCPP_COLLECTIONSTREAM_H

#endif //YANDEXPRACTICUMCPP_COLLECTIONSTREAM_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vector_){
    out << "[";
    if(vector_.empty()){
        return out << "]";
    }
    auto begin = vector_.cbegin(), prev_end = std::prev(vector_.cend());
    std::for_each(begin, prev_end,[&out](const T& value){
        out << value << ", ";
    });
    return out << *prev_end << "]";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& set_){
    out << "{";
    if(set_.empty()){
        return out << "}";
    }
    auto begin = set_.cbegin(), prev_end = std::prev(set_.cend());
    std::for_each(begin, prev_end,[&out](const T& value){
        out << value << ", ";
    });
    return out << *prev_end << "}";
}

template <typename K, typename T>
std::ostream& operator<<(std::ostream& out, const std::map<K, T>& map_){
    out << "{";
    if(map_.empty()){
        return out << "}";
    }
    auto begin = map_.cbegin(), prev_end = std::prev(map_.cend());
    std::for_each(begin, prev_end,[&out](const auto& p){
        out << p.first << ": " << p.second << ", ";
    });
    return out << prev_end->first << ": " << prev_end->second << "}";
}