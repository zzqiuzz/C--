#include <iostream> 
#include <vector>
#include <string>
#define Qnew(T) (new T) 
using std::string;
using std::cout;
using std::endl;
using std::vector;
int &get(int* array, int index){
    return array[index];
}

int main()
{
    {// initialize string
     //Notice: sizeof(std::string) 返回的是 std::string 对象本身的大小，而不是它所管理的字符串数据的大小。
        string s1; // default init, empty str.
        string s2 = s1; // s2 copy from s1
        string s3 = "hiyao"; // s3 is a copy of string literal "hiya"  拷贝初始化
        string s5("hiyao"); // 直接初始化
        string s4(10, 'c'); // ccccccccccc 直接初始化
        const char* c = "hiya";
        const char c_ar[] = "hiya";
        // cout << sizeof(s3) << " " << sizeof(c) << " " << sizeof(c_ar) << endl; // 32 8 5
        bool a = s3.size() < -1; // True size()返回的是无符号std::size_type 与-1比较 -1会变成一个很大的数
        // cout << a << " " << s3.size() << endl; 1 5
        int size = s4.size(); // 实际返回的类型是string::size_type
        // cout << size << endl; // 10
    // compare
        string str = "Hello", phrase = "Hello World", slang = "Hiya";
        // cout << bool(slang > phrase)  << " " << bool(phrase > str) << endl; 1 1
        //assignment
        string st1(10, 'c'), st2;
        st1 = st2; // st1 被st2赋值，此时都是空字符串
        // add
        {
            string s1 = "hello, ", s2 = "world\n";
            string s3 = s1 + s2;
            s1 += s2;
            decltype(s1.size()) cnt = 0;
            // string::size_type cnt = 0; the same
            for(auto c : s1){
                if(ispunct(c))++cnt; // 判断是否是标点符号
            }
            cout << cnt << endl;  // 1
        }
        
    }
    //vector 圆括号是用提供的值来构造vector对象，花括号是想用列表表达式来初始化vector对象
    {
        vector<int> v1(10); // 有十个元素，每个值默认初始化为0
        vector<int> v2{10}; // 有一个元素，值是10
        vector<int> v3(10, 1); // 有十个元素，每个值初始化为1
        vector<int> v4{10, 1}; // 有两个元素，10和1
        vector<int> v5 = {1,2};
        vector<int> v6 = v3;
    }

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
        /*一维数组作为函数的参数时，数组名就转换为数组首元素的地址。二维数组作为函数的参数时，数组名同样转换为数组首元素的地址&arr[0],
        只不过这个首元素是一个int[5]类型的数组*/
        // 定义一个指向一维数组的指针
        int (*ptr)[4] = arr; // 指向包含 4 个元素的一维数组 ptr = &arr[0] ptr存放的是数组第一个元素(也即arr[0])的首地址 所以ptr+1 代表arr[1]的地址 而arr[1]又是第二行的首地址，arr[1] = &arr[1][0], 所以*(ptr+1) = *arr[1] 的是arr[1][0]地址
        std::cout << ptr << " " <<  arr  << " " << arr[0] <<  " " << arr+1 << " " << *(arr + 1) << " " << arr[1] << " " << arr[1]+1 << std::endl;
        std::cout << arr+1 << " " <<  &arr[1]  << " " << &arr[1][0] <<  " " << *(arr+1) << std::endl; // the same
        // 使用索引访问二维数组元素
        std::cout << "二维数组内容: " << std::endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::cout << *(*(ptr + i) + j) << " "; // 等价于 *(*(ptr + i) + j)
            }
            std::cout << std::endl;
        }

    }

    {
        // const char *a[5] = {"nihao", "hhh"}; // a是一个char指针数组，每个元素都是指针，因此需要二级指针指向a;
        // char **p = a;
        // int b = 5;
        // int const *pi = &b; // 不是常量指针，可以通过p来修改b的值
        // const int *p = &b; // 不是常量指针，可以通过p来修改b的值
        // int * const pp = &b; // pp 是常量指针，不能修改，只能指向b
    }
    int a = 0;
    {
        static int a = 10; // 这个静态变量仅在这个代码段内可见
        std::cout << a << std::endl; // 10
    }
    std::cout << a << std::endl; // 0


    {
        int a0 = 0; 
        int a1 = 1; 
        int *a = &a0, *b = &a1;
        int *p[2] = {a, b};
        int **pp = p;
        cout << " " << pp[0] << " " << pp[1] << endl;
        cout << " " << *pp[0] << " " << *pp[1] << endl;
    }

    return 0;
}

