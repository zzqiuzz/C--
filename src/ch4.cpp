#include <iostream>
using namespace std;
#include <string>

int main(){
    // 显示转换
    {
        {
            // static_cast 
            // 任何具有明确定义的转换，只要不能包含底层const,都可以使用
            // 主要用于基本数据类型的转换，以及具有继承关系的类对象之间的转换
            int a = 2, b = 3, *const p = &a, *pp = &b; 
            float c = static_cast<float>(*pp);
            // float *cc = static_cast<float*>(pp); errr
            void* v = &b;
            int *d = static_cast<int*>(v); 
        }
        {
            // const_cast
            // 只能改变运算对象的底层const，即改变常量属性， 可以去除，也可以增加
            const char* cp = "hello.";
            int a = 1; const int* p = &a;
            void *v = reinterpret_cast<void*>(const_cast<int*>(p));

            // char *pp = const_cast<char*>(cp); // 通过p写值是未定义的行为
            // *pp = 'n';
            printf("--------%s--", cp);
        }
        {
            int *ip;
            // char *pc = reinterpret_cast<char*>(ip); //及其危险
            // std::string str(pc) //可能导致异常行为
        }
        int i; double d; const string *ps; char *pc; 
        // void *pv = (void*)ps;
        void *pv = reinterpret_cast<void*>(const_cast<string*>(ps)); // 先去除const属性然后使用reinterpret_cast  
        // i = int(*pc);
        i = static_cast<int>(*pc);

        // pv = &d;
        pv = static_cast<void*>(&d);

        // pc = (char*) pv;
        pc = reinterpret_cast<char*>(pv);
    }

    return 0;
}