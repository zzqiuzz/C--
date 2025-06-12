#include <iostream>
using namespace std;
#include <string>

int main(){
    // 显式转换
    {
        {
            // static_cast  更推荐用于void*转换
            // 任何具有明确定义的转换，只要不能包含底层const,都可以使用
            // 主要用于基本数据类型的转换，以及具有继承关系的类对象之间的转换
            int a = 2, b = 3, *const p = &a, *pp = &b; 
            uint32_t a_int32 = 9;
            float c = static_cast<float>(*pp); // 整数还都能转浮点
            double dd = static_cast<double>(a_int32);
            //算数类型指针看来都不能用static_cast转，可以通过void*中转或者用reinterpret_cast
            // char *cp = static_cast<char*>(a); error 
            // double *c = static_cast<double*>(pp);//error 不能将int* 转换成double* 
            // float *cc = static_cast<float*>(pp); //error 不能将int* 转换成float*,因为它们没有继承关系或标准转换路径。
            void* v = &b;
            int *d = static_cast<int*>(v); 
        }
        {
            // const_cast 尽量避免使用，主要用于去除const属性
            // 只能改变运算对象的底层const，即改变常量属性， 可以去除cosnt属性，也可以增加

            const char* cp = "hello.";
            int a = 1; const int* p = &a;
            void *v = reinterpret_cast<void*>(const_cast<int*>(p));
           //试图通过非 const 指针或引用去修改原本声明为 const 的对象，其行为是未定义行为
            // char *pp = const_cast<char*>(cp); // 通过p写值是未定义的行为
            // *pp = 'n';
            printf("--------%s--", cp);
        }
        // reinterpret_cast 用于低层次、与平台和实现相关的类型转换
        {
            int *ip;
            // double *dp = static_cast<double*>(ip); error
            double *dp = reinterpret_cast<double*>(ip);
            
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