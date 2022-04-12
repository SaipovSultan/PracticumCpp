#ifndef YANDEXPRACTICUMCPP_SIMPLETEST_H
#define YANDEXPRACTICUMCPP_SIMPLETEST_H

#include <string>
#include <iostream>


template <typename Func>
void RunTestImp(Func func, const std::string func_str){
    func();
    std::cerr << func_str << " OK" << std::endl;
}

#define RUN_TEST(func) RunTestImp(func, #func)

#endif //PRACTICUMCPP_RATIONAL_H