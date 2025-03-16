/*
移动构造函数（Move Constructor）是C++11引入的一个特性，它允许对象在创建时直接“移动”另一个对象的资源，
而不是复制它们。这可以显著提高性能，特别是在处理大型或昂贵的对象（如包含动态分配内存的类）时。
如果你没有显式定义移动构造函数，编译器会根据情况为你生成默认的移动构造函数。
但是，如果你定义了自己的拷贝构造函数或者析构函数，编编器可能不会自动生成移动构造函数，因此你可能需要自己定义它们以确保你的类支持高效的移动语义。
command: g++ .\src\move_constructor.cpp -std=c++11
*/
#include <iostream>
#include <utility> // for std::move
class MyClass{
    private:
        int* data = nullptr;
        std::string _name = "UnKnown";
    public:
        //构造函数
        explicit MyClass(){};
        MyClass(int value, std::string name) : data(new int(value)), _name(name){
            std::cout << "construct from value" << std::endl;
        } // 管理一块动态分配的内存
        //拷贝构造函数
        MyClass(const MyClass& other) : data(new int(*other.data)){
            std::cout << "copy constructor called." << std::endl;
        }
        //赋值操作符
        MyClass& operator=(const MyClass&) = delete;
        MyClass& operator=(const MyClass&&) = delete;
        //移动构造函数, 接受一个右值对象
        MyClass(MyClass&& other) : data(new int(*other.data)), _name(other._name){
            other.data = nullptr; // 将源对象的资源置为nullptr 
            std::cout << "Move constructor called." << std::endl;
        }
        //禁用赋值操作符
        ~MyClass(){
            delete data;
        }
        void print(){
            std::cout << "------------------name:" << this->_name << " data is:" << std::endl;
        }
    
};

int main(){ 
    MyClass obj1 = {1, "obj1"};   
    MyClass obj2(std::move(obj1)); // 调用移动构造函数
    obj2.print();
    obj1.print();  // invoke unpredictable behaviour.
     
    MyClass obj4(obj2); // 
    obj2.print();
    // obj4 = obj2; // 禁用
    // obj4 = std::move(obj2); // 禁用

}

