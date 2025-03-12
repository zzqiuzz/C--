#include<string>
#include<iostream>
using namespace std;
/*1.初始化变量以及以值的方式传递或者返回一个对象，执行拷贝操作；
  2.定义在类内部的函数是自动inline的;
  3.mutable 关键字成员变量，即使在const对象内，也可以修改；
  4.如果成员是const、引用或者某种未提供默认构造函数的类类型，必须通过构造函数初始值列表为这些成员提供初始值；
  5.常量对象以及常量对象的引用或指针都只能调用常量成员函数
*/
// 声明之后，定义之前是一个不完全里类型，只知道它是一个类类型，但是不清楚它包含哪些成员
// 只能在有限的情况下使用，可以定义指向这种类型的指针或引用
class Screen; 

class Link_screen{
    Screen *window;
    // Screen hh; 错误 上述不完全类型 只能定义指向这种类型的指针或引用
    Link_screen *next;
    Link_screen *prev;
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
    static const int value = 0; // 可以初始化
    static constexpr int v = 1;
    // static  int value = 0; // 不可以初始化
    static int hh; // 类外初始化
    int number = 0;
    string name = "";
    public:
        friend Test add_obj(const Test&, const Test&); // 友元函数可以访问类的私有成员
        Test() = default;
        Test(int num, string name) : number(num), name(name){};
        Test(int num) : number(num){}; // 接受单个参数的构造函数，编译器可以执行隐式转换；
        explicit Test(string n) : name(n){}; // 禁用隐式转换，必须显式构造, 只对一个实参的构造函数有效 多个参数的构造函数不能用隐式转换
        ~Test(){};
        Test& add_(Test &t);
        string print_name() const { // 常成员函数, 只能由常对象/常指针/引用来调用 这里的const是修改隐式this指针的类型
            cout << "const " ;
            return name;
            };
        string print_name() { // 类成员函数自动inline
            cout << "no const ";
            return name;};
        void print_number(){
            cout << "numnber is " << this->number << endl;
        } 
        static int get_hh(); // 只能访问静态成员变量，因为没有this指针，所以不能访问其它成员变量

};
int Test::hh = 5; // 初始化静态成员变量 
int Test::get_hh(){return hh;};
Test add_obj(const Test &t1, const Test& t2){
    Test tmp;
    tmp.number = t1.number + t2.number;
    return tmp;
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
        Test t = 123; // 
        cout << "------------------" << t.get_hh();
        // << " " << Test::hh; 无法直接访问 因为是private
    }
    {
        //隐式转换；
        Test t = 250;
        Test tt = t;
        string name = "nihao";
        // Test t_ = name; // 失败，因为禁用了隐式初始化，必须显式构造
        Test t_ = static_cast<Test>(name); // 这里用static_cast显示转换成了Test对象
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