#include<string>
#include<iostream>
using namespace std;
/*1.初始化变量以及以值的方式传递或者返回一个对象，执行拷贝操作；
  2.定义在类内部的函数是自动inline的;
  3.mutable 关键字成员变量，即使在const对象内，也可以修改；
  4.如果成员是const、引用或者某种未提供默认构造函数的类类型，必须通过构造函数初始值列表为这些成员提供初始值；
*/
class Test{
    int number = 0;
    string name = "";
    public:
        friend Test add_obj(const Test&, const Test&); // 友元函数可以访问类的私有成员
        Test() = default;
        Test(int num, string name) : number(num), name(name){};
        ~Test(){};
        Test& add_(Test &t);
        string print_name() const { // 常成员函数, 只能由常对象/常指针/引用来调用
            cout << "const " ;
            return name;
            };
        string print_name() {
            cout << "no const ";
            return name;};
        void print_number(){
            cout << "numnber is " << this->number << endl;
        }

};

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