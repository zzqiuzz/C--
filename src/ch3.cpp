#include <iostream>
using namespace std;
#include <string>

int &get(int* array, int index){
    return array[index];
}

int main()
{
    //array
    {
        int a[10] = {0};
        int *p[10]; // 存放10个int类型指针数组
        // int &p[10] = ; 不存在引用的数组
        int (*b)[10] = &a; // b 指向一个含有10个元素的数组 a
        int (&ref)[10] = a;// ref引用一个含有10个元素的数组 a 
        std::cout << a << " " << &a << " " << b <<std::endl;
        // int a[8-6] = {0}; // 错误
    }
    {
        int ia[10];
        for(int i = 0; i != 10; ++i){
            get(ia, i) = i;
        }
    }
    {
        int a = 1;  // 0x... [1]
        int *p = &a; // 0x... [a的地址=p] 此时p的值就是a的地址，里面存放的是a的地址！
        int **pp = &p; // 0x... [p的地址]， 此时pp的值的就是p的地址
        // std::cout << *pp << p << &a << std::endl; 他仨一样的
    }
        std::cout << "----------------------1------------------" << std::endl;
    {
        int arr[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        };
    
        // 定义一个指向一维数组的指针
        int (*ptr)[4] = arr; // 指向包含 4 个元素的一维数组 ptr = &arr[0] ptr存放的是数组第一个元素(也即arr[0])的首地址 所以ptr+1 代表arr[1]的地址 而arr[1]又是第二行的首地址，arr[1] = &arr[1][0], 所以*(ptr+1) = *arr[1] 的是arr[1][0]地址
        std::cout << ptr << " " <<  arr  << " " << arr[0] <<  " " << arr+1 << " " << *(arr + 1) << " " << arr[1] << std::endl;
        // 使用索引访问二维数组元素
        std::cout << "二维数组内容: " << std::endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::cout << *(*(ptr + i) + j) << " "; // 等价于 *(*(ptr + i) + j)
            }
            std::cout << std::endl;
        }

    }
    return 0;
}

