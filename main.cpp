#include <iostream>

class Greeting{
public:
    Greeting(const std::string& name) : name(name){
        std::cout << "+" << name << std::endl;
    }
    ~Greeting(){
        std::cout << "-" << name << std::endl;
    }
private:
    std::string name;
};

Greeting greeting{"Apple"};


int main() {
    std::cout << "main" << std::endl;
    return 0;
}
