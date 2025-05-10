template <typename T>
class SimpleVector {
private:
    T* data;
    size_t capacity_;
    size_t size_;

public:
    SimpleVector() : data(nullptr), capacity_(0), size_(0) {}
    
    ~SimpleVector() { delete[] data; }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data[size_++] = value;
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

    T& operator[](size_t index) { return data[index]; }
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
};