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

void print_array(int *array, int size){
    cout << "--------------------print array case 1--------------------" << endl;
    for(int i = 0; i < size; i++)
        cout << array[i] << ",";
    cout << endl;
}

void print_array_(int (*array)[10], int size){
    cout << "--------------------print array case 2--------------------" << endl;
    for(int i = 0; i < size; i++)
        cout << (*array)[i] << ",";
    cout << endl;
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
    //1-d array https://blog.csdn.net/zzy979481894/article/details/124678972
    { 
        int a[10] = {1, 2 ,3,4,5,6}; // 后续未显式初始化的元素默认初始化为0
        // 用指针指向
        // 方法一 指向数组的指针 多用来二维数组
        int (*p_a)[10] = &a; // p_a 是一个指向a这个数组的指针
        print_array((int*)p_a, 5); // 必须要执行转换
        print_array_(p_a, 5);  
        // 方法二 推荐 指向数组元素的指针
        int *b = a; // b 是指向数组a的指针，a是一个一级指针，指向a[0], 即b也指向a[0], b = &a[0]
        print_array(b, 5); 

        int *p[10]; // 存放10个int类型指针数组
        // int &p[10]; 不存在引用的数组, 数组要求元素是对象，而引用不是对象
        int (&ref)[10] = a;// ref引用一个含有10个元素的数组 a  
        int aa[8-6] = {0}; //正确 数组里面的维度必须是常量或者是常量表达式
        auto c(a); // c这里是一个int* 相当于c(&a[0])                
        decltype(a) d = {4,5,6,7,8,} ;//这里d是一个含有10个整型的数组 注意与auto区别
        d[5] = 5;
        int *pp = &d[2]; // 6
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
    {   // 2d array
        //多维数组其实就是数组的数组，即数组中的每个元素也是数组
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
            arr二维数组看成有三个元素的数组分别是 arr[0] arr[1] arr[2] 每个元素又都是一个四维数组 arr[0] 是arr[0][0] arr[0][1] arr[0][2] arr[0][3] 这个数组的首元素地址
            这个时候arr+1 指向arr[1] 即 ptr+1 = &arr[1] 
            那么*(arr+1)代表的是arr[1] 这个元素(行)的首地址，那么*(arr+1) + 1就是这一行当中的第二个元素的地址，那么*(*(arr+1) + 1)就是取元素
            int (*ptr)[4] = arr; 这个声明，意思是ptr这个指针指向的是arr这个包含三个元素arr[0] arr[1] arr[2] 中arr[0]这个首元素，即ptr = &arr[0]
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

