#include <iostream>
#include <memory>
using std::cout;
using std::endl;
class B;
class A{
    public:
        A() = default;
        ~A(){};
        std::shared_ptr<B> b_ptr;
        
};

class B{
    public:
        B() = default;
        ~B(){};
        // std::shared_ptr<A> a_ptr; // 会导致循环引用
        std::weak_ptr<A> a_ptr;
        
};

int main(int argc, char *argv[]){
    {
        auto a = std::make_shared<A>(); // 引用 1
        auto b = std::make_shared<B>(); // 引用 1 
        a->b_ptr = b; // b的引用2
        b->a_ptr = a; // a的引用还是1
    } // 离开作用域时， a引用计数为0，a析构时会把a->b_ptr也释放，因此b引用计数为1，此时b本身析构进而再减1为0
    return 0;


}