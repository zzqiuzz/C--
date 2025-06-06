#include<string>
#include<vector>
#include<iostream>
using namespace std;
/*1.初始化变量以及以值的方式传递或者返回一个对象，执行拷贝操作；
  2.定义在类内部的函数是自动inline的;
  3.mutable 关键字成员变量，即使在const对象内，也可以修改；
  4.如果成员是const、引用或者某种未提供默认构造函数的类类型，必须通过构造函数初始值列表为这些成员提供初始值；
  5.常量对象以及常量对象的引用或指针都只能调用常量成员函数
*/
// 声明之后，定义之前是一个不完全类型，只知道它是一个类类型，但是不清楚它包含哪些成员
// 只能在有限的情况下使用，可以定义指向这种类型的指针或引用
class Screen; 

class Link_screen{
    Screen *window;
    // Screen hh; 错误 上述不完全类型 只能定义指向这种类型的指针或引用
    Link_screen *next; // 指针或者引用可以这样定义，可以是不完全类型
    Link_screen *prev;
    static Link_screen l; // 静态成员也可以是不完全类型
    // Link_screen r; error 常规对象不能是不完全类型
};

class NoDefault{
    int number = 0;
    public:
        // NoDefault(){} = default;
        NoDefault(int num): number(num){};//由于你自己定义了一个构造函数（B(int)），编译器不会再生成默认构造函数 。
                                       //如果你仍然想要支持 B b; 这样的调用，你需要显式定义默认构造函数或使用 = default。
        void print(){cout << number << std::endl;}
};

class C{
    public:
        NoDefault nodefault_obj;
        C(): nodefault_obj(0){};  // 必须对成员nodefault_obj初始化，该成员无默认构造函数
        void print(){
            nodefault_obj.print() ;
        };      
};
/*
explicit 关键字用于防止隐式类型转换。
它通常应用于单参数构造函数或多参数但可以退化为单参数的构造函数。
使用 explicit 可以提高代码的安全性、可读性和可维护性，避免因隐式转换导致的潜在问题。
*/
/*
类的静态成员函数不能被声明为const的原因（标准规定）：因为const是修饰成员函数，要求有this指针，而静态成员函数没有this指针，
*/
class Test{
    // 静态成员属于类，不属于任何一个对象，并不是在创建类的对象时被定义的，一般来说不能在类的内部初始化的，只能定义一次
    // 但是可以进行const整数里类型的类内初始化
    static const int value = 0; // 可以初始化
    // static double rate = 1.0; error 
    // static const double r = 2.0; // error
    static constexpr double r = 2.0; // duoble只能用constexpr 

    // static  int value = 0; // 不可以初始化 必须是const或者constexpr
    static int hh; // 类外初始化
    int number = 0; // 初始化的时候按照顺序来
    string name = "";

    friend void printTestName(Test); // 声明友元函数
    public:
    
        static constexpr int v = 1; 
        friend Test add_obj(const Test&, const Test&); // 友元函数可以访问类的私有成员
        Test() = default;
        Test(int *num, string name) : Test(*num, name){}; // 委托构造函数
        Test(int num, string name) : number(num){
            this->name = name; // this是一个const指针，用于指向具体的实例对象，不能在静态成员函数中使用，因为静态成员函数不绑定任何实例对象
        };
        Test(int num) : number(num){}; // 接受单个参数的构造函数，编译器可以执行隐式转换
        explicit Test(string n) : name(n){}; // 禁用隐式转换，必须显式构造, 只对一个实参的构造函数有效 多个参数的构造函数不能用隐式转换
        ~Test(){};

        string print_name() const { // 常成员函数, 只能由常对象/常指针/引用来调用 这里的const是修改隐式this指针的类型
            cout << "const " ;
            return name;
            };
        string print_name() { // 类成员函数自动inline
            cout << "no const ";
            return name;};
        void print_number(){
            cout << "number is " << this->number << endl;
        } 
        static int get_hh(); // 只能访问静态成员变量，因为没有this指针，所以不能访问其它成员变量
        Test& add_(Test &t);
        Test& add(int);
};

void printTestName(Test t){
    cout << "-----visit Test private member by friend, the name is: " << t.name;// 因为是友元可以访问Test成员
}

Test& Test::add(int num){
    this->number += num;
    return *this; // for method chaining e.g Test a.add(1).add(5)
}

int Test::hh = 5; // 初始化静态成员变量 
int Test::get_hh(){return hh;};
Test add_obj(const Test &t1, const Test& t2){
    Test tmp;
    tmp.number = t1.number + t2.number;
    printf("----------------tmp addr%p", &tmp);
    return tmp; // 返回tmp这个对象执行拷贝操作后被释放
}

Test& Test::add_(Test &t){
    number += t.number; 
    return *this;
}

Test return_obj(Test &t){
    Test tmp = t;
    return tmp;
}

Test* return_p(Test &t){
    Test* tmp = &t; // local var
    return tmp;
}

Test* return_p(){
    Test p = {222, "p"}; // local var will be released after called.
    Test* tmp = &p; 
    return tmp;
}

class Y;  // 一定要有这句话 要声明
class X{
    public:
        X() = default; 
        Y* y = nullptr;
        int num_x = 1;
};

class Y{
    public:
        Y() = default;
        Y(int num) : num_y(num) {}; 
        X x = {};
        int num_y = 2;
};
int main(){
    {
        // NoDefault nodefault; // 无默认构造函数，初始化失败
        // std::vector<NoDefault> vec(10); // 无默认构造函数，初始化失败
        std::vector<C> vec(10); // 合法
        C c;
        c.print();

    }
    {
        Test t = 123; // 
        cout << "---------static---------" << t.get_hh() << endl; // 常规对象访问静态成员
        cout << "---------static---------" << Test::get_hh() << endl; 
        // << " " << Test::hh; 无法直接访问 因为是private
        // const int &num = Test::v; // 这里会报错 undefined reference to Test::v 找不到定义， 因为是在类中定义
    }
    {
        // 当构造函数接受一个参数的时候，允许隐式转换
        Test t = 250;
        Test t1 = {23, "zz"};
        Test tt = t;
        string name = "nihao";
        Test t2(name); // 直接初始化也叫显式初始化
        // Test t_ = name; // 失败，因为不能将explicit构造函数用于拷贝形式的初始化过程

        Test t_ = static_cast<Test>(name); // 这里用static_cast显式转换成了Test对象
        add_obj(2, 3); // 这里编译器将2， 3 隐式转换成了Test临时对象 这种显然会造成困扰
    }
    {
        Test test1(1, "test1");
        Test test2(2, "test2");
        const Test test3 = {3, "test3"};
        test1.add_(test2);
        test1.print_number();
        // const Test tmp = test1.add_(test2);
        // cout << tmp.print_name() << endl;

        cout << test1.print_name() << endl;// 调用非const成员函数
        cout << test3.print_name() << endl;// 调用const成员函数

    }
    // 返回引用/指针/对象的差异
    {
        Test t = {111, "t"};
        Test ttt, t1 = {222, "t1"};
        ttt = add_obj(t, t1);
        printf("----------------ttt addr%p\n", &ttt);
        ttt.print_number();

        // OK
        // Test tmp = return_obj(t);
        // cout << tmp.print_name() << endl;
        // tmp.print_number();
        // OK
        // Test* tmp = return_p(t);
        // cout << tmp->print_name() << endl;
        // tmp->print_number();
         
        // error undefined behaviour
        // Test* tmp = return_p();
        // cout << tmp->print_name() << endl;jdsaA
        // tmp->print_number();
    }
    {//  定义一对类X和Y,X包含一个指向Y的指针， Y包含一个类型为X的对象
        X x;
        Y y = {100};
        x.y = &y;
        std::cout << "-------------------" << x.y->num_y << std::endl; 
    }





    return 0;
}