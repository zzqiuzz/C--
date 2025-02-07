#include <iostream>
using namespace std;
#include <string>

int &get(int* array, int index){
    return array[index];
}

int main()
{
    //array
    {
        int a[10] = {0};
        int *p[10]; // 存放10个int类型指针数组
        // int &p[10] = ; 不存在引用的数组
        int (*b)[10] = &a; // b 指向一个含有10个元素的数组 a
        int (&ref)[10] = a;// ref引用一个含有10个元素的数组 a 
        std::cout << a << " " << &a << " " << b <<std::endl;
        // int a[8-6] = {0}; // 错误
    }
    {
        int ia[10];
        for(int i = 0; i != 10; ++i){
            get(ia, i) = i;
        }
    }
    return 0;
}

