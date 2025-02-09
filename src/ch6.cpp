#include <iostream>
#include <string>
int count(const std::string str, char, int a){
    std::cout << a << " ";
    return 0;
}

int (*print_array(int (&a)[10])){ // 传入一个指针引用作为形参，返回一个数组指针
    a[9] = 9;
    for(size_t i = 0; i < 10; i++)
        std::cout << a[i] << " " << std::endl;
    return a;
}

int (*print_arr(int i))[10]{ // 返回一个数组指针,指向一个含有10个整数的数组
    static int b[10] = {3,4,5,6,7,8,9,1,2};
    b[1] = i;
    return &b;
}

int* print_(int* a){
    for(size_t i = 0; i < 10; i++)
        std::cout << a[i] << " " << std::endl;
    return a;
}

int (&getArray())[5] { // 返回一个包含 5 个元素的数组的引用
    static int arr[5] = {10, 20, 30, 40, 50};
    return arr;
}

int main()
{
    {
        int i = 42;
        const int *cp = &i;
        const int &r = i;
        const int &r2 = 42;
        // int *p = cp; // p是int型指针，而cp是const int*，类型不匹配
        // int &r3 = r; // r是常引用，r3是普通int引用，类型不匹配，如果合法，则r3能修改r的值，与r矛盾
        // int &r4 = 42; // 如果合法，则r4可以修改42的值，但是42是个字面值常量
    }

    {
        //这个函数的形参不是const，意味着不能传入字面值字符串，改成const std::string
        // bool is_empty(string& s){return s.empty();}
        count("Heel", 'a', 3.5);
    }
    {
        int j = 0, i[2] = {1,2};
        std::cout << &j << " " << i << std::endl;
        // printf("-----0x", &j);
        
    }
    // 重载和const形参
    {
        //以下四个函数1、2/ 3,4是等价的
        // int lookup(int); 无顶层const
        // int lookup(const int); 和上面一行等价，有顶层const

        // int lookup(int*);  无顶层const
        // int lookup(int* const) 和上面一行等价，有顶层const
        //以下四个函数1,2/3,4不是等价的， 因为非常量指针或引用可以都能传，但是如果是常指针或者常变量，则只能用带const的函数
        // int lookup(int*);
        // int lookup(const int*);和上面一行不等价，带有底层const
        // int lookup(int&);
        // int lookup(const int&); 和上面一行不等价，带有底层const

    }

    {
        int a[10] = {1,2,3,4,5};
        
        int *b = print_array(a);
        // int *b = print_(a); // OK
        for(size_t i = 0; i < 10; i++)
            std::cout << b[i] << " " << std::endl;

    }
    std::cout << "----------------------1------------------" << std::endl;
    {
        //定义一个返回数组指针的函数
        typedef int arr_t[10]; // arrt_t是一个类型别名，表示的类型是含有10个整数的数组
        using arrT = int[10]; // 同上
        arr_t b = {0};
        // arr_t func(int i); // 该函数返回一个指向10个整数的数组指针
        for(size_t i = 0; i < 10; i++)
            std::cout << b[i] << " " << std::endl;
        // int arr[10];
        // int *arr[10]; 指针数组
        // int (*p)[10] = &arr; p 是一个指针，指向含有10个整数的数组 

    }
    std::cout << "----------------------2------------------" << std::endl;
    {
        int i = 345;
        int (*b)[10] =  print_arr(i); // b是一个指向含有10个整数的数组指针
        // std::cout << b[0] << b[1] << " " << std::endl; 打印的是地址
        for(size_t i = 0; i < 10; i++)
            std::cout << (*b)[i] << " " << std::endl; // 这个地方很重要  一定是（*b）解引用
    }
    std::cout << "----------------------3------------------" << std::endl;
    {
        int (&arr)[5] = getArray(); // 获取数组的引用

        for (int i = 0; i < 5; ++i) {
            std::cout << arr[i] << " "; // 输出数组内容
        }
    }



    return 0;
}