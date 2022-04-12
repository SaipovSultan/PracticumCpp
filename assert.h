//
// Created by Sultan on 04.04.2022.
//
#ifndef YANDEXPRACTICUMCPP_ASSERT_H
#define YANDEXPRACTICUMCPP_ASSERT_H

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

template <typename T, typename U>
void AssertEqualImp(const T& t, const U& u, const std::string& t_str, const std::string& u_str, const std::string& file, const std::string func, unsigned line, const std::string& hint){
    if(t != u){
        std::cerr << std::boolalpha;
        std::cerr << file << "(" << line << "): " << func << ": ";
        std::cerr << "ASSERT_EQUAL(" << t_str << ", " << u_str << ") failed: ";
        std::cerr << t << " != " << u << ". ";
        if(!hint.empty()){
            std::cerr << "Hint: " << hint;
        }
        std::cerr << std::endl;
        abort();
    }
}

void AssertImp(bool value, const std::string& expr_str, const std::string& file, const std::string& func, unsigned line, const std::string& hint){
    if(!value){
        std::cerr << file << "(" << line << "): " << func << ": ";
        std::cerr << "ASSERT(" << expr_str << ") failed. ";
        if(!hint.empty()){
            std::cerr << "Hint: " << hint;
        }
        std::cerr << std::endl;
        abort();
    }
}

#define ASSERT_EQUAL(a, b) AssertEqualImp((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, "")

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImp((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

#define ASSERT(value) AssertImp((value), #value, __FILE__, __FUNCTION__, __LINE__, "")

#define ASSERT_HINT(value, hint) AssertImp((value), #value, __FILE__, __FUNCTION__, __LINE__, (hint))



#endif //YANDEXPRACTICUMCPP_ASSERT_H
