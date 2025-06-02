#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
/*
动态绑定：运行时，虚函数，基类指针或引用调用函数
静态绑定：编译时，普通函数调用，函数重载
*/
// define abstract base class
class Shape{
    public:
        virtual void draw() const = 0;
        virtual ~Shape(){};
        virtual void printName() {
            cout << "Shape" << endl;}

};

class Circle final : public Shape{ // final终止继承
    public:
        virtual void draw() const override{
            cout << "drawing Circle." << endl;
        } 
        
};

class Rectangle final : public Shape{
    public:
        virtual void draw() const override{
            cout << "drawing Rectangle." << endl;
        }
};


int main(int argc, char* argv[]){
    Shape *shape = new Circle();
    Rectangle *rectangle = new Rectangle();
    shape->draw(); 
    rectangle->draw();
    shape = rectangle; //动态绑定只发生在使用指针或引用时
    shape->draw(); 

    delete shape;

    
}