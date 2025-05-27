/*
    C++ primer 5th edition: chapter 2 notes;
    左值（Lvalue） ：具有持久存储位置的对象，通常可以取地址。int x = 10; // x 是左值
    右值（Rvalue） ：临时对象或字面量，没有持久存储位置。 int y = 10 + 20; // 10 + 20 是右值
    右值引用通过 T&& 表示，专门用于绑定到右值。例如：int&& rvalue_ref = 42; // 绑定到右值 42
    右值引用不能绑定到左值，但可以通过 std::move 将左值转换为右值。
*/


#include <iostream>
#include <string>
#include <string.h>
using std::cout;
using std::endl;
std::string outer_str; // 未显式初始化，函数外定义则默认初始化为空串 如果是局部变量，则状态未知
int outer_varibale; // 未显式初始化，函数外定义则默认初始化为0
int block_scope_var = 2;

#define _CAT(A, B) A##B // ## 操作符将两个参数 A 和 B 连接在一起


// 定义函数指针类型 指向函数的指针，函数接受 int 参数并返回 int
typedef int (*FuncPtr)(int, int);
typedef FuncPtr (*FType)(int); 
// (*(void(*)())0)(); 这是啥意思
constexpr int constexpr_int = 1;
constexpr unsigned long long fibonacci(int i) { // 表明该函数是一个编译器期间可以算出的常量
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}
int static_(){
    static int count = -1;
    count ++;
    return count;
}

static int func(int param) { //  声明是静态函数，该函数仅在该文件可见
    static int static_ = param; // param仅在第一次初始化static_有效，后续都无效
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++; // 先返回static_ ,后++
}

int add (int x, int y){
    return x + y;
};

int multiply(int x, int y) {
    return x * y;
}

// 示例函数，返回一个函数指针
FuncPtr get_function(int op) {
    if (op == 1) {
        return add;
    } else {
        return multiply;
    }
}
// argc 表示命令行参数的数量，argv是一个指向字符数组的指针数组，每个元素指向一个命令行参数字符串
int main(int argc, char *argv[]){
    // argc argv
    cout << "number of args is: " << argc << endl; 
    for(int i = 0; i < argc; i++)
        cout << "argv[" << i << "] = " << argv[i] << endl;
    

    {
        // 因为指针的本质是一个内存地址，地址的长度取决于系统架构和编译器
        cout << "number of bytes of different type of pointers" << endl;
        cout << sizeof(char*) << " " << sizeof(int*) << " " << sizeof(double*) << " " << sizeof(float*)<< " "  << endl; //8 8 8 8 根据操作系统
    }
    {
        int xy = 42;
        int hello_world = 100; 
        cout << _CAT(x, y) << " " << _CAT(hello, _world) << endl; // 42 100
    } 
    {
        unsigned char a = -1;  //  无符号超出范围 255
        // signed char b = 256; // 有符号超出范围 undefined value warning overflow 可能正常运行，崩溃，产生垃圾数据
        int month = 9;
        int mont = 017; // octal number 八进制 
        // int aa = {3.14}; {}初始化,只要存在信息丢失的风险，编译器报错。
        int inner_var; // 函数内部声明而没有初始化，则值由定义的位置所决定（不确定）
        // std::cout << outer_varibale << outer_str << inner_var;
    }
    // scope
    {
        int block_scope_var = 1; // 覆盖全局作用域变量 可以通过 ::block_scope_var 来访问全局作用域里的变量
        int block_scope_var1 = 1; // 块作用域，出了此作用域即失效，无法访问
        int i = 100, sum = 0;
        for(int i = 0; i != 10; ++i)
            sum += i ; //运算完后 for里面的i出作用域失效
        // std::cout << i << ", " << sum; // i = 100, sum = 45
    }
    {
        //reference must initilize being declared, only once. binded only by just one var.
        int ii , &ri = ii;
        ii = 5;
        ri = 10;
        // std::cout << ii << " " << ri << std::endl; // 10 10 
    }
    {
        //pointer
        int* p, p1; // p is a pointer while p1 is var of type int.
        double dval = 0.2;
        double* pd = &dval; // declare a pointer which represents the addr of a var.
        double* pd2 = pd; // both addr.
        double* &rr = pd; // reference that refers to a pointer.
        void* pp = &dval;
        double* ppp = static_cast<double*>(pp);
        std::cout << pd << " " << pd2 << *rr << std::endl;
    }
    //constexpr
    {
        constexpr int num = 10;
        int a[num] = {0};
        constexpr int* constexpr_p = &block_scope_var; // 该变量必须在函数体外定义(不能是局部变量)，constexpr_p是常量指针，不能改变指向
        // constexpr_p = nullptr; // error constexpr_p是常量指
        // constexpr int* constexpr_p1 = &constexpr_int;  //constexpr_int是const
        constexpr const int* constexpr_p1 = &constexpr_int; //constexpr_p1是指向常量的常量指针 == const int * const p  
        // 编译期间算出这个结果了
        // constexpr auto FIB90 = fibonacci(90); // exceed recursion depth, you can relax returned type from costexpr to non-constexpr
        // std::cout << "fibonacci(90) = " << FIB90 << std::endl;
    }
    
    // typedef
    {
        typedef int a_t[10]; // a_t是一个类型别名，表示的类型是含有10个整数的数组
        using a__t = int[10]; // 和typedef等价
        int a = 0, b = 1;
        typedef int *my_int_p, my_int;
        const my_int_p p = &a;
        *p = 1;
        // p = &b; // 这里的p是const ptr，can not be modified.
    }
    //auto
    {
        const int a = 0;
        int b = 1;

        const int* const p = &a; // 指向常量的常指针
        auto c = p;
        c = &b; // c本身可以变指向的对象(忽略顶层const),只有指针同时具有顶层const和底层const
        // *c = 100; // error 保留了底层const,即指向的内容不可以变

        const int& p_ref = a;
        auto p_ref_auto = p_ref; // 忽略顶层const,  
        p_ref_auto = 1; // 指向的内容可以变

        auto d = a; // 忽略顶层const 
        d = 2;

        auto *pp = &a; 
        // *pp = 100;// pp是指向整数常量大的指针， 无法修改a的值
        
        std::cout << *c << " " << d << std::endl;
    }
    //decltype
    {
        int a = 0, *p = &a, aa = 10;
        decltype(p) b = &a; // b 是指针
        auto c = b; // c也是指针
        *c = 3; // 改变了a的值
        // std::cout << a << " " << *b << " " << *c << std::endl; // 3 3 3 
        decltype(*p)  d = a; // *p 解引用生成一个左值
        d = 1; // d 是一个引用
        decltype((a)) e = a;
        e = 100; // e 是一个引用
        // std::cout << a << " " << *b << " " << *c << std::endl; // 1 1 1

        {
            int a = 3, b = 4;
            decltype(a = b) d = a; // a = b 是赋值表达式,会产生引用,但是不会改变a的值 
            std::cout << a << b << d << std::endl; // 3 4 3
            // d = 5; //是引用
        }
    }

    //static 
    {
        int count = 0;
        while (++count < 10){
            std::cout << static_() << " " << std::endl;

        }
    }

    {
        char a[20] = "hello world", tmp;
        char *start, *end;
        start = end = a;
        end += strlen(a) - 1;
        std::cout << *start << " " << *start++ << std::endl; // h h
        std::cout << "0------------------" << *start << std::endl; // e
        std::cout << *end << " " << *end-- << std::endl; // d d
        std::cout << "1------------------" << *end << std::endl; //l
        while(start < end){
            tmp = *start;
            *start++ = *end;
            *end-- = tmp;
        }
        std::cout << a << std::endl;

    } 

    { // C/C++ 的声明遵循“螺旋法则”（Spiral Rule），即从变量名开始，按照优先级向内解析。 see doc/spiral_rule.md
        /* 
            1. f 是一个指针，指向某种类型的对象。
            2. *f 表示 f 是一个指针，指向一个函数。这个函数有两个参数，类型分别为 int 和 int，并且返回值是一个指针。 
            3. 返回值是一个指针，指向一个函数。这个函数有一个 int 类型的参数，并返回一个 int 类型的值。
        */
        // take an example 
        
        FType f = get_function;

        // 使用 f
        FuncPtr func = f(1); // 获取 add 函数
        printf("Result: %d\n", func(3, 4)); // 输出 7

        FuncPtr func1 = f(2); // 获取 add 函数
        printf("Result: %d\n", func1(3, 4)); // 输出 7 
    }



    

    return 0;
}