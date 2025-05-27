#include<iostream>
#include <vector>
#include <string>
#include <utility>
using std::vector;
using std::string;
using std::cout;
using std::endl;
// 右值引用通过 T&& 表示，专门用于绑定到右值。例如：int&& rvalue_ref = 42; // 绑定到右值 42
// 右值引用不能绑定到左值，但可以通过 std::move 将左值转换为右值。移动操作后，原对象的状态可能无效，应避免继续使用。
// 右值引用的另一个重要应用是实现完美转发 ，即在模板中将参数原封不动地转发给其他函数，同时保留其左值或右值属性
/* 
    @发生拷贝初始化的集中情况：
    1. 将一个对象作为实参传递给一个非引用类型的形参；
    2. 从一个返回类型为非引用类型的函数返回一个对象；
    3. 用花括号列表初始化一个数组中的元素或一个聚合类中的成员。 e.g MyClass myclass[4] = {obj1, obj2}
*/
/*
拷贝初始化有时会使用移动构造函数
用=初始化可看作是拷贝初始化
*/
/*
    编译器自己合成的成员函数有：析构，默认构造，拷贝构造，拷贝赋值运算符， 移动构造函数，移动赋值运算符
*/
class numbered{
    public:
        numbered(){
            mysn = unique++;
        }
        numbered(const numbered &obj) : mysn(unique++){cout << "ddd";}; // 注释掉看现象

        int mysn;
    private:
        
        static int unique;
        
};
// void f(numbered n)
void f(const numbered &n)  //如果是const引用则不会执行拷贝构造
{
    std::cout << n.mysn << std::endl;
}
int numbered::unique = 10;

struct X
{
	X() { std::cout << "X()" << std::endl; }
	X(const X&) { std::cout << "X(const X&)" << std::endl; }
	X& operator=(const X&) { std::cout << "X& operator=(const X&)" << std::endl; return *this; }
	~X() { std::cout << "~X()" << std::endl; }
};

void f(const X &rx, X x) // 调用拷贝构造函数3次
{  // 非引用传参x 1  引用传参不调用
	std::vector<X> vec;
	vec.reserve(2);
	vec.push_back(rx); // 2
	vec.push_back(x); // 3
}

class MyClass{
    public:
        vector<int> data;
        int *p = new int;
        int num;
        static MyClass default_class; // 合法，因为此时MyClass是正在定义的类类型，所以可以声明，但是不能定义！
        // static MyClass default_class = {5};  // 错误 不能定义
        MyClass() = default; // 只能对编译器自己合成版本的成员函数使用=default
        MyClass(vector<int> d): data(d){};  // 默认情况下，单参数的构造函数都应该声明为explicit， 只能用于直接初始化
        explicit MyClass(int n): num(n){
            num = default_class.num; // 初始化列表初始化后，重新赋值
        };  // 默认情况下，单参数的构造函数都应该声明为explicit， 只能用于直接初始化
        // 拷贝构造函数定义:第一个参数是自身类类型的引用且任何额外参数都有默认值而且几乎都是const引用
        // 如果没有为一个类定义拷贝构造函数，编译器会定义一个合成拷贝构造函数
        MyClass(const MyClass& other) : data(other.data){
            cout << "calling copy constructor.\n";
        }; 
        // 拷贝构造函数的入参必须是引用
        // MyClass(MyClass myclass); 如果不是引用会产生循环调用，因此是错误的，因为值传递会调用拷贝构造函数，而此时拷贝构造函数正在定义！ 
        // 拷贝赋值运算符
        MyClass& operator=(const MyClass &obj){ // operator=相当于一个函数名
            cout << "calling copy asignment operator.\n";
            data = obj.data;
            return *this; // 支持chain rule
            // this->data = obj.data;
        };
        ~MyClass(){
            delete p;
            // 析构函数体
        }; // 析构函数体自身并不直接销毁成员，比如data是自己调用自己的析构函数销毁，如果有定义动态指针，则需要在函数体里面析构
}; 
MyClass MyClass::default_class{50};

MyClass func_through(MyClass obj){
    cout << "-------start" << endl;
    MyClass tmp = obj; // 只是一个临时变量， 返回时执行类的拷贝构造函数，将data赋值给外面的接收方，然后被释放
    tmp.data.pop_back();
    cout << "-------end" << endl;
    return tmp; // 移动构造函数，将tmp的值移出func_through(),移动到保存func_through(obj)结果的临时变量中
};

class HasPtr{
    public:
        HasPtr(const string &s = string()): ps(new string(s)), i(0){}
        HasPtr(const HasPtr &obj){ // 必须定义拷贝构造函数， 不然析构的时候会重复delete
            cout << "calling HasPtr copy constructor." << endl;
            this->ps = new string(*obj.ps); 
            this->i = obj.i;
        }
        HasPtr& operator=(const HasPtr &obj){
            cout << "calling HasPtr copy assignment operator." << endl;
            delete ps;
            this->ps = new string(*obj.ps); 
            this->i = obj.i;
            return *this;
        }
        void print(){
            cout << *this->ps << " " << this->i << endl;
        }
        ~HasPtr(){
            delete ps;
        }
    private:
        string *ps;
        int i;
};

void process(int&);
void process(int&&);
template <typename T>
void wrapper(T&& arg){
    process(std::forward<T>(arg));
}

void process(int& x) { std::cout << "Lvalue reference: " << x << "\n"; }
void process(int&& x) { std::cout << "Rvalue reference: " << x << "\n"; }

int main(void){ 
    {
        numbered a, b = a, c = b; // 如果没有拷贝构造函数，那么a b c 的打印都是一样的
        f(a);
        f(b);
        f(c);
    }

    {
        X *px = new X;
        f(*px, *px);
        delete px;
        cout << "-----------------------------------------------" << endl;
    }

    {
        // 定义析构函数的类，也要求定义拷贝构造函数和拷贝赋值运算符
        HasPtr hasptr("ptr");
        HasPtr obj(hasptr); // 调用拷贝构造函数
        HasPtr obj1;
        obj1 = obj; // 如果不定义拷贝赋值运算符，用合成的默认拷贝赋值运算符，会导致析构重复delete  三五法则
        obj.print();
        hasptr.print();
    }

    {
        vector<int> data = {1, 2, 3};
        int num = 4;
        MyClass obj = data; // 调用拷贝构造函数
        // MyClass obj1 = 4; // 因为接受该单个参数的构造函数是explicit的，因此只能用于直接初始化
        MyClass hh(5);
        cout << "------------" << hh.num << endl;
        MyClass recv = func_through(obj); // 将func_through(obj)的值移动到recv里面， 移动赋值操作
        for(int i = 0; i < recv.data.size(); i++)
            cout << "data is: " << recv.data[i] << endl; // 1 ， 2
    }
    {
        MyClass obj; // 默认构造函数
        MyClass c = obj; // 拷贝构造函数 注意与拷贝赋值运算符的区别
        MyClass b; // 已经调用构造函数了
        b = obj; // 拷贝赋值运算符
        vector<MyClass> vec;
        vec.push_back(obj); // 拷贝构造函数

    }




    {
        // MyClass obj1 = std::move(obj); //std::move把左值变为右值 调用移动构造函数

        // int x = 42;
        // wrapper(x);       // 传的是左值
        // wrapper(42);      // 传的是右值
    }
    return 0;
}