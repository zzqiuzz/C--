#include <iostream>
#include <string>

template <typename T>
class UniquePtr{
    private:
        T* _ptr = nullptr; // 要管理的对象

    public:
        explicit UniquePtr(T* ptr = nullptr) : _ptr(ptr){}
        ~UniquePtr(){
            delete _ptr;
        }
        // 禁用拷贝
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr& operator=(const UniquePtr& other) = delete;
        // 允许移动
        UniquePtr(UniquePtr&& other) noexcept : _ptr(other._ptr){
            other._ptr = nullptr;
        }
        //在移动构造函数和移动赋值运算符中使用noexcept是很有必要的，因为标准库容器在重新分配内存时，会优先选用不会抛出异常的移动操作。
        UniquePtr& operator=(UniquePtr&& other) noexcept{ //
            if(this != &other){
                delete _ptr;
                _ptr = other._ptr;
                other._ptr = nullptr;
            }
            return *this;
        }

        T* operator->() const{
            return _ptr;
        }

        T& operator*() const{
            return *_ptr;
        }

        T* get() const {
            return _ptr;
        }

        explicit operator bool() const{
            return _ptr != nullptr;
        }
        T* release(){
            T* temp = _ptr;
            _ptr = nullptr;
            return temp;
        }

        void reset(T* p = nullptr){
            if(_ptr != p){
                delete _ptr;
                _ptr = p;
            }
        }

};

int main(){
    UniquePtr<std::string> ptr1(new std::string("Hello"));
    std::string* rawPtr = ptr1.release();
    std::cout << "rawPtr: " << *rawPtr << std::endl; // 输出: Hello
    // 此时 ptr1 不再拥有资源，变为空指针
    if (!ptr1) {
        std::cout << "ptr1 is now null" << std::endl; // 会执行此语句
    }

    // 需要手动管理 rawPtr 的内存
    delete rawPtr;

    // 使用 reset 方法重置指针
    ptr1.reset(new std::string("World"));
    std::cout << "ptr1 after reset: " << *ptr1 << std::endl; // 输出: World

    // 重置为 nullptr，会自动释放当前资源
    ptr1.reset();
    if (!ptr1) {
        std::cout << "ptr1 is null after reset to nullptr" << std::endl; // 会执行此语句
    }

    // 创建另一个智能指针
    UniquePtr<int> ptr2(new int(42));
    std::cout << "ptr2: " << *ptr2 << std::endl; // 输出: 42

    // 使用 reset 替换资源，会先释放原有资源
    ptr2.reset(new int(99));
    std::cout << "ptr2 after reset: " << *ptr2 << std::endl; // 输出: 99

    return 0;
}