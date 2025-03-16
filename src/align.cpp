#include <iostream>
#include <type_traits>
// g++ .\src\align.cpp -std=c++11 -o hh
class Entity{
    private:
        
        char ccc[9] = "d";
        char cc[16] = "how";
        char* c;
        // int* a;
        // int b = 3;
        // int bb[16] = {0};
    public:
        void print(){
            std::cout << "hello." << std::endl;
        }
};
alignas(16) int data;

struct  Struct{
    char a;
    double b;
};

struct alignas(32) Aligned32Struct{
    char a;
    double b;
};

int main(){ 
    std::cout << alignof(data) << std::endl; //16
    std::cout << sizeof(data) << std::endl;  // 4

    std::cout << alignof(Struct) << std::endl;  //8
    std::cout << sizeof(Struct) << std::endl;  //16

    std::cout << alignof(Aligned32Struct) << std::endl;  //32
    std::cout << sizeof(Aligned32Struct) << std::endl;  //32
}