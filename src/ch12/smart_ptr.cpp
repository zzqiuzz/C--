/*可以解引用
std::shared_ptr 是 C++ 标准库中的一种智能指针，它提供了对对象的共享所有权。当多个 std::shared_ptr 实例指向同一个对象时，
它们会共同管理该对象的生命周期：即当最后一个 std::shared_ptr 被销毁或重置（不再指向该对象）时，这个对象将会被自动删除以释放资源。
std::shared_ptr 通过引用计数来跟踪有多少个 std::shared_ptr 正在共享同一对象。每当一个新的 std::shared_ptr 指向一个对象时，
引用计数就会增加；而当一个 std::shared_ptr 不再指向该对象（例如，它被销毁或者被赋予了一个新的值）时，引用计数就会减少。如果引用计数降到零，
这意味着没有 std::shared_ptr 再指向这个对象了，于是对象会被销毁。

注意事项
循环引用：使用 std::shared_ptr 时要小心不要造成循环引用，这会导致内存泄漏。可以使用 std::weak_ptr 来打破这种循环。
性能开销：由于引用计数的维护，std::shared_ptr 相比原始指针有一定的性能开销。
线程安全：std::shared_ptr 的引用计数操作是线程安全的，但对象本身的访问不是线程安全的，需要程序员自己确保线程同步。
*/

/*不能解引用
std::weak_ptr 是 C++ 标准库中的一种智能指针，它和 std::shared_ptr 一起工作。std::weak_ptr 不会增加指向对象的引用计数，
因此不会阻止所指向的对象被销毁。它主要用于实现观察者模式或者解决循环引用问题。
*/

/* 可以解引用
std::unique_ptr 是 C++11 引入的一种智能指针，它拥有独占所有权的语义。这意味着在任意时刻只能有一个 std::unique_ptr 拥有某个对象。
当 std::unique_ptr 被销毁或者被赋予新的值时，它原来管理的对象会被自动删除。
*/
#include <iostream>
#include <memory>

class Entity{ 
    public:
        Entity(){
            std::cout << "Default Constructor called." << std::endl;
        };
        Entity(int num) : a(num){
            std::cout << "num Constructor called." << std::endl;
        } 
        void print(){
            std::cout << "----------" << a << "---------" << std::endl;
        }
        Entity(const Entity& other){
            std::cout << "Copy Constructor called." << std::endl;
        }
        ~Entity(){

        };
    private:
        int a = 0;
};


int main(){
    // 使用 make_shared 创建 std::shared_ptr  推荐这种方式  对象实例化和引用计数块初始化 同时进行
    auto sp1 = std::make_shared<int>(42); // 
    std::cout << "Value: " << *sp1 << std::endl;
    //直接创建 std::shared_ptr 并分配新对象
    std::shared_ptr<int> sp2(new int(1));
    std::cout << "Value: " << *sp2 << std::endl;

    auto sp3 = std::make_shared<int>(5);
    {
        std::shared_ptr<int> sp4 = sp3; // sp4/sp3 同时指向5
        std::cout << "sp3 used count: " << sp3.use_count() << std::endl;   // 2
        std::cout << "sp4 used count: " << sp4.use_count() << std::endl;   // 2
    }// sp4 超出作用域
    std::cout << "sp3 used count: " << sp3.use_count() << std::endl;  // 1

    // 获取原始指针；
    int* rawPtr = sp3.get();
    std::cout << "Value via raw pointer: " << *rawPtr << "\n";
    std::cout << "Value via shared_ptr: " << *sp3 << "\n"; 
    std::cout << "---------------------1--------------------" << std::endl;  

    {
        std::shared_ptr<Entity> e0;
        std::weak_ptr<Entity> w; 
        {
            std::shared_ptr<Entity> e2 = std::make_shared<Entity>(100);
            e0 = e2;  
            std:: cout << "e0 used count: " << e0.use_count() << ", e2 used count: " << e2.use_count() << std::endl; // 2
            w = e2; // w 没有增加指向对象的引用计数
            std:: cout << "w used count: " << w.use_count()  << ", e2 used count: " << e2.use_count() << std::endl; // 2
        }// e2 释放
        std::cout << "---------------------2--------------------" << std::endl;  
        std::cout << "e0 used count: " << e0.use_count() << std::endl; // 1
        e0->print() ;
        std::cout << "w used count: " << w.use_count()  << std::endl; // 1
        // w->print(); weak_ptr 不能直接访问，必须先通过lock()获得一个std::shared_ptr
        std::shared_ptr<Entity> sp = w.lock();//引用计数增加到2
        /*
            本身没有解锁的概念，因为它的设计目的就是不持有资源。一旦你使用 lock() 得到了 std::shared_ptr，
            你需要确保在不再需要的时候释放这个 std::shared_ptr（通常是在作用域结束时自动完成），以避免不必要的延长对象生命周期。
        */
        if(sp){
            sp->print();
        }
        else{
            std::cout << "weak ptr has been destroyed." << std::endl; 
        }
        std::cout << "sp used count: " << sp.use_count()  << std::endl; // 2
        std::cout << "w used count: " << w.use_count()  << std::endl;  // 2
        std::cout << "---------------------3--------------------" << std::endl;  
        //使用 reset() 方法可以让 std::weak_ptr 不再指向任何对象（将其设置为空）
        sp.reset();
        w.reset();
        std::cout << "sp used count: " << sp.use_count()  << std::endl; //0
        std::cout << "w used count: " << w.use_count()  << std::endl;//0
        //使用 expired() 方法来检查 std::weak_ptr 所指向的对象是否已经被销毁。
        std::cout << w.expired() << std::endl; // 1 已经销毁
    } //e0/w释放

    std::cout << "---------------------4--------------------" << std::endl;  
    { 
        auto unique_ptr = std::make_unique<int>(9);
        std::cout << "Value via unique_ptr: " << *unique_ptr << "\n";
        //std::unique_ptr 不支持复制，但是可以移动给另一个 std::unique_ptr。
        std::unique_ptr<int> u1 = std::move(unique_ptr);
        // std::cout << "Value via unique_ptr: " << *unique_ptr << "\n"; 崩溃 此时unique_ptr已经被释放
        std::cout << "Value via unique_ptr: " << *u1 << "\n"; 
    }



    return 0;
}