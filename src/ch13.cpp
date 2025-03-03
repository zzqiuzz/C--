#include<iostream>
#include <vector>
#include <utility>
using std::vector;
// 右值引用通过 T&& 表示，专门用于绑定到右值。例如：int&& rvalue_ref = 42; // 绑定到右值 42
// 右值引用不能绑定到左值，但可以通过 std::move 将左值转换为右值。
// 右值引用的另一个重要应用是实现完美转发 ，即在模板中将参数原封不动地转发给其他函数，同时保留其左值或右值属性
class MyClass{
    public:
        vector<int> data;

        MyClass() = default;
        // 拷贝构造函数
        MyClass(const MyClass& other) : data(other.data){}; 
        //移动构造函数
        MyClass(MyClass&& tmp) noexcept : data(std::move(tmp.data)){};
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
    MyClass obj;
    obj.data = {1, 2, 3};

    MyClass obj1 = std::move(obj); //std::move把左值变为右值 调用移动构造函数

    int x = 42;
    wrapper(x);       // 传的是左值
    wrapper(42);      // 传的是右值
    return 0;
}