#include<stdlib.h>
#include <stdio.h>
#include <iostream>
#include<string>
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


    return 0;
}