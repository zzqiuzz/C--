#include <iostream>

template <typename T>
class SharedPtr{
    private:
        T* ptr;
        int *ref_count; // 使用堆分配的 int* 而非普通 int，确保多个 SharedPtr 实例能共享同一个计数

    public:
        SharedPtr() : ptr(nullptr), ref_count(nullptr){};

        explicit SharedPtr(T *p) : ptr(p), ref_count(new int(1)){};

        //copy constructor
        SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count){
            if(ref_count)
                (*ref_count)++;
        }
        //move constructor
        ~SharedPtr(){ // 每次析构时减少计数，当计数为 0 时释放资源。
            release();
        }

        SharedPtr& operator=(const SharedPtr& other){
            if(this != &other){
                release(); // 赋值前先释放当前资源 见76行
                ptr = other.ptr;
                ref_count = other.ref_count;
                if(ref_count){
                    (*ref_count)++;
                }
            }
            return *this;
        }

        T& operator*() const{
            return *ptr;
        }

        T* operator->() const{
            return ptr;
        }

        int use_count(){
            return ref_count ? *ref_count : 0;
        }

        void release(){
            if(ref_count){
                (*ref_count)--;
                if(*ref_count == 0){
                    delete ptr;
                    delete ref_count;
                }
            }
        }



};

int main(){
    SharedPtr<int> sp1(new int(42));
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;

    SharedPtr<int> sp2 = sp1;
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use count: " << sp2.use_count() << std::endl;

    SharedPtr<int> sp3;
    sp3 = sp1;
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use count: " << sp2.use_count() << std::endl;
    std::cout << "sp3 use count: " << sp3.use_count() << std::endl;

    sp3 = sp2; // 这里再次赋值的话，计数应维持不变
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use count: " << sp2.use_count() << std::endl;
    std::cout << "sp3 use count: " << sp3.use_count() << std::endl;
    return 0;
}