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

int* print_(int* a){
    for(size_t i = 0; i < 10; i++)
        std::cout << a[i] << " " << std::endl;
    return a;
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
    return 0;
}