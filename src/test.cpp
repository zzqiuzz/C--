#include <iostream>
#include <type_traits>

void foo(char*);
void foo(int);
typedef enum model{
    qwen=0,
    llama
}model_t;

int main(){
    {   
        int a[10] = {1,2,3};
        model_t model_type = model::qwen;
        switch(model_type){
            case model::qwen:
                std::cout << "a" << a[5] << std::endl;
            case model::llama:
                // int c[10] = {1,2,3,4};
                std::cout << "hh" << std::endl;
            default:
            std::cout << "h h" << std::endl;
        }
    }
    if (std::is_same<decltype(NULL), decltype(0)>::value)
        std::cout << "NULL == 0" << std::endl;
    if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
        std::cout << "NULL == (void*)0" << std::endl;
    if (std::is_same<decltype(NULL), std::nullptr_t>::value)
        std::cout << "NULL == nullprt" << std::endl;
    if (std::is_same<decltype((void*)0), std::nullptr_t>::value)
        std::cout << "void*0 == nullprt" << std::endl;
    if (std::is_same<decltype((void*)0), decltype(0)>::value)
        std::cout << "void*0 == 0" << std::endl;
    if (std::is_same<decltype(1), decltype(0)>::value)
        std::cout << "type 1 == type 0" << std::endl;

    foo(0);
    foo(nullptr);
    int len = 10;
    const int len_2 = len + 1;
    char arr_4[len_2];

    return 0;
}

void foo(char*) {
    std::cout << "foo(char*) is called." << std::endl;
}

void foo(int i) {
    std::cout << "foo(int) is called." << std::endl;
}