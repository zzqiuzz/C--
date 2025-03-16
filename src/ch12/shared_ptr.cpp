/*
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

#include <memory>
#include <iostream>

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


}