#include <iostream>
#include <memory>
using std::cout;
using std::endl;

template<typename T>
class MemoryHandle{
    private:
        T* data;
        size_t size;

    public:
        explicit MemoryHandle(size_t arraySize) : size(arraySize){ 
            cout << "Allocating array of size " << size << endl;
            data = new int[size];
        };

        ~MemoryHandle(){
            if(data){
                cout << "Releaseing memory at: " << data << endl;
                delete[] data; 
            }
        };
        // 禁止拷贝（避免多个句柄管理同一块内存）
        MemoryHandle(const MemoryHandle&) = delete;
        MemoryHandle& operator=(const MemoryHandle&) = delete;

        // allow move
        MemoryHandle(MemoryHandle &&other) noexcept : data(other.data), size(other.size){
            // delete other.data;
             other.data = nullptr;
             other.size = 0;
        }

        MemoryHandle& operator=(MemoryHandle && other) noexcept {
            if(this != &other){
                delete[] this->data;
                data = other.data;
                size = other.size;
                other.data = nullptr;
                other.size = 0;
            }
            return *this;

        };
        // 下标访问
        T& operator[](size_t index){
            if(index > size) throw std::out_of_range("index out of range.");
            return data[index];
        }
        const T& operator[](size_t index) const {
            if(index > size) throw std::out_of_range("index out of range.");
            return data[index];
        }
        // 获取原始指针
        T* get() const{return data;}
        //解引用
        T& operator*() const {return data[0];} 
        // 成员访问操作符 （虽然没有成员，但可以保留）
        T* operator->() const {return data;}
 
        size_t getSize() const {
            return size;
        }

    // 判断是否持有有效指针
    // operator bool() const { return data != nullptr; } 
};

 
int main(int argc, char *argv[]){
    {
        MemoryHandle<int> arr(5); 
        for (size_t i = 0; i < arr.getSize(); ++i) {
            arr[i] = static_cast<int>(i * 10);
        }
        int *data = arr.get();
        cout << "visit data by nake ptr " << data[3] << endl;
        MemoryHandle<int> *p = &arr;
        cout << "arr[2] " << arr[2] << endl;
        printf("%d\n", (*p)[2]); 
        cout << p->get()[3] << endl;  
    }



    return 0;
}