#include<stdlib.h>
#include <stdio.h>
#include <iostream>
#include<string>
#include <memory>
#include <vector>

using namespace std;
class Base{
    public:
        string name_pub;
    
    protected:
        string name_pro;

    private:
        string name_priv;
};

class PubBase : public Base{
    void get_name(){
            cout << name_pub << name_pro;
        }
};

class ProBase : protected Base{
    void get_name(){
        cout << name_pub << name_pro;
    }
};

class PrivBase : private Base{
    void get_name(){
        cout << name_pub << name_pro;
    }
};
 
int main(int argc, char *argv[]){ 

    PubBase pub_base;
    ProBase pro_base;
    cout << pub_base.name_pub;// 只能访问 public 成员变量 << pub_base.name_pro; 不能访问
    // cout << pro_base.name_pub; 不能访问
    // cout << priv_base.name_pub; 不能访问
    const PubBase &hh = pub_base;

    std::shared_ptr<int> p = std::make_shared<int>(1);
    cout << &p << endl;
    cout << p.get() << endl;

    float f = 0.6;
    float left = -1.f, right = 1.f;
    float ans = 0.f;
    while(std::abs(ans * ans * ans - f) > 1e-5){
        if((ans * ans * ans - f) > 0)
            right = ans;
        else
            left = ans;           

        ans = (left + right) / 2;
    }
    cout << ans << endl;

    std::vector<int> a = {1, 2, 3}; // 0   3
    std::vector<int> b = {1, 6};  // 1   1

    



    
    return 0;
}