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
        int size = s4.size(); // 实际返回的类型是string::size_type, 无符号，可以放下任何string对象的大小
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
        {
            string hh = "nishishei?";
            for(char &c : hh){ // 这里必须是引用!!!! 或者用auto也行 string里每一个字符都是char类型
                c = 'X';
            }
            cout << hh;
        }
        
    }
    //vector 圆括号是用提供的值来构造vector对象，花括号是想用列表表达式来初始化vector对象
    {
        // 创建指定数量的元素
        vector<int> v1(10); // 有十个元素，每个值默认初始化为0
        vector<int> v3(10, 1); // 有十个元素，每个值初始化为1
        // 列表初始化
        vector<int> v2{10}; // 有一个元素，值是10
        vector<int> v4{10, 1}; // 有两个元素，10和1
        vector<int> v5 = {1,2}; // 只有花括号里的值必须与元素类型相同才能执行列表初始化
        vector<string> s{10}; // 这里花括号里的10不是string类型，编译器使用默认值初始化对象，初始化成10个元素
        vector<int> v6 = v3;
        vector<vector<int>> matrix(3, vector<int>(5, 0));//声明一个三行五列的matrix
    }

    {//使用迭代器实现二分查找
        vector<int> num{1,3, 4, 5, 6, 7, 8, 9};
        for(vector<int>::iterator it = num.begin(); it != num.end(); it++)
            cout << *it << " ";
        int target_num = 3;
        auto start = num.begin(), end = num.end(); // 这里的end指向尾元素的下一位置 
        cout << (start < end) << endl;
        vector<int>::iterator mid = start + (end - start) / 2;
        while(start < end){
            cout << " mid num is  " << *mid << endl;
            if(*mid == target_num){
                cout << "find! " << *mid << endl;
                break;
            }
            else if(*mid < target_num){
                start = mid + 1;
            }
            else{
                end = mid - 1;
            }
            mid = start + (end - start) / 2;
        }

    }
    //array
    { 
        int a[10] = {0};
        int *p[10]; // 存放10个int类型指针数组
        // int &p[10] = ; 不存在引用的数组, 数组要求元素是对象，而引用不是对象
        int (*b)[10] = &a; // b 指向一个含有10个元素的数组 a 为什么不能用int *b = &a; 因为 int *b是指向一个整数啊，很显然啊
        int (&ref)[10] = a;// ref引用一个含有10个元素的数组 a 
        std::cout << a << " " << &a << " " << b <<std::endl;
        int aa[8-6] = {0}; //正确
        auto c(a); // c这里是一个int* 相当于c(&a[0])                
        decltype(a) d = {4,5,6,7,8,} ;//这里d是一个含有10个整型的数组 注意与auto区别
        d[5] = 5;
        int *p = &d[2]; // 6
        // p[1]即7  p[-2]即4
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
    {//多维数组其实就是数组的数组，即数组中的每个元素也是数组
        int arr[3][4] = { // {0, 1,2，3} 也可以只塞满了第一行，剩下的默认初始化为0
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        };
        /*一维数组作为函数的参数时，数组名就转换为数组首元素的地址。二维数组作为函数的参数时，数组名同样转换为数组首元素的地址&arr[0],
        只不过这个首元素是一个int[4]类型的数组*/
        // 定义一个指向一维数组的指针
        int (*ptr)[4] = arr; // 
        std::cout << ptr << " " <<  arr  << " " << arr[0] <<  " " << arr+1 << " " << *(arr + 1) << " " << arr[1] << " " << arr[1]+1 << std::endl;
        std::cout << arr+1 << " " <<  &arr[1]  << " " << &arr[1][0] <<  " " << *(arr+1) << std::endl; // the same
        // 使用索引访问二维数组元素
        std::cout << "二维数组内容: " << std::endl;
        /*
            ptr是一个指向含有四个整数的指针，被赋值为arr，而arr是一个3行4列的二维数组，所以ptr指向的是arr第一行的首元素的地址
            此时ptr+i存放的是arr第i行的数组首元素的地址即*(ptr+i),那么显然，*(ptr+i)+j则指向第i行的第j个元素的地址 
            假如arr的元素地址如下:
            0x000, 0x004, 0x008, 0x00C,
            0x010, 0x014, 0x018, 0x01C,  
            ...
            ptr是一个地址是一个地址是一个地址是一个地址是一个地址是一个地址是一个地址是一个地址
            e.g ptr的地址是 
            0x200[存放的是0x000即arr的首元素的地址]， 
            0x204[存放的是0x010即arr第二元素的地址]，
            0x208[存放的是0x020即arr第三元素的地址]，
            所以ptr+1即0x204   *(ptr+1)是0x010 *(ptr+1) +2 即0x018 懂了吗!!!! niubility
        */
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                std::cout << *(*(ptr + i) + j) << " "; 
            }
            std::cout << std::endl;
        }
        //
        for(auto row = arr; row != arr + 3; ++row){ // row 是一个地址 指向含有四个元素的数组即每一行
            for(auto col = *row; col != *row + 4; ++col) // col是一个地址指向每行的第一个元素
                cout << *col << " ";
        }

    }

    {
        // const char *a[5] = {"nihao", "hhh"}; // a是一个char指针数组，每个元素都是指针，因此需要二级指针指向a;
        // char **p = a;
        // int b = 5;
        // int const *pi = &b; // 不是常量指针，不可以通过p来修改b的值
        // const int *p = &b; // 不是常量指针，不可以通过p来修改b的值  首先看p，就近原则， 左边是一个*,说明是一个指针，这个指针指向一个const int
        // int * const pp = &b; // pp 是常量指针，只能指向b, 但是可以修改b的值
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

