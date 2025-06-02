#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
template <typename T>
class Container{
    public:
        virtual T& operator[](int) = 0;
        virtual size_t size() const = 0;
        virtual ~Container() {};
        // 纯虚函数要求子类必须实现
        virtual void printData() const{
            cout << "base func." << endl;
        }
};


template <typename T>
class SimpleVector : public Container<T>{
private:
    T* data;
    size_t capacity_; //总容量
    size_t size_; // 当前元素个数

public:
    SimpleVector() : data(nullptr), capacity_(0), size_(0) {}
    
    ~SimpleVector() { delete[] data; }

    // 带初始大小的构造函数
    explicit SimpleVector(int size) : data(new T[size]), capacity_(size), size_(size){};

    //初始化列表构造函数
    SimpleVector(std::initializer_list<T> init) : 
        data(new T[init.size()]), capacity_(init.size()), size_(init.size()){
        std::copy(init.begin(), init.end(), data);
    }
    // 拷贝构造函数
    SimpleVector(const SimpleVector &other):
        data(new T[other.capacity_]), // 这里能直接访问私有成员
        capacity_(other.capacity_),
        size_(other.size_)    
    {
        cout << "calling copy constructor func." << endl;
        std::copy(other.data, other.data + other.size_, data);
    }
    // 赋值运算符
    SimpleVector& operator=(SimpleVector &other){
        swap(*this, other);
        return *this;
    }

    // 友元 swap 函数
    friend void swap(SimpleVector& first, SimpleVector& second) noexcept {
        using std::swap;
        swap(first.data, second.data);   // 交换指针
        swap(first.size_, second.size_);   // 交换大小
    }


    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data[size_++] = value;
    }

    void pop_back(){
        if(size_ > 0)
            size_--;

    }

    void clear(){
        size_ = 0;
    }

    T* data_pointer() const {
        return data;
    }

    void reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            T* new_data = new T[new_cap];
            for (size_t i = 0; i < size_; ++i)
                new_data[i] = data[i];
            delete[] data;
            data = new_data;
            capacity_ = new_cap;
        }
    }

    T& operator[](int index) override{ return data[index]; }
    size_t size() const override{ return size_; }
    size_t capacity() const { return capacity_; }
    bool empty(){return size_ == 0;}

    void printData() const override{
        for(int i = 0; i < size_; i++)
        cout << data[i] << " ";
    cout << endl;
    }

}; 

int main(int argc, char *argv[]){
    {
        SimpleVector<int> v1 = {1, 2, 3}; // 初始化列表构造函数 
        v1.printData();
        SimpleVector<int> v2(v1); // 拷贝复制构造函数 
        v2.push_back(7);
        v2.printData();
        SimpleVector<int> v3; 
        v3 = v2; // 赋值运算符   
        cout << "---------------------------------push" << endl;
        v1.push_back(5);
        v1.push_back(10); 
        v1.printData(); 
        cout << "---------------------------------pop" << endl;
        v1.pop_back(); 
        v1.printData();
        cout << "---------------------------------clear" << endl;
        v3.clear();
        cout << v2.empty() << endl;
    } 
    cout << "--------------------------------------------" << endl;
    {
        Container<int> *base_c = new SimpleVector<int> {4,5,6,7};
        base_c->printData(); // 基类指针或引用，运行时多态
    }

}