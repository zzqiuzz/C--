/*
@:brief: 装饰器模式（DecoratorPattern）允许向一个现有的对象添加新的功能，同时又不改变其结构
*/
#include <string>
#include <iostream>
using namespace std;

class Beverage{
    public:
        virtual ~Beverage(){};
        virtual string getDescription() const = 0;
        virtual double cost() const = 0;
};

class Coffe : public Beverage{
    public:
        string getDescription() const override{
            return "coffe.";
        } 
        double cost() const override{
            return 2.5;
        }
};

class Tea : public Beverage{
    public:
        string getDescription() const override{
            return "tea.";
        } 
        double cost() const override{
            return 5.;
        }
};
//对基类进行装饰
class Decorator : public Beverage{
    protected:
        Beverage* beverage;
    public:
        Decorator(Beverage* b) : beverage(b){}
        ~Decorator(){
            cout << "hhhhhhh" << endl;
            delete beverage;
        }
        string getDescription() const override{
            return beverage->getDescription();
        }

        double cost() const override{
            return beverage->cost();
        }

};

class Milk : public Decorator{
    public:
        Milk(Beverage* b) : Decorator(b){}
        string getDescription() const override{
            return beverage->getDescription() + ", Milk";//  这里的milk就是装饰的行为
        }
        double cost() const override{
            return beverage->cost() + 0.5;
        }
};

class Sugar : public Decorator{
    public:
        Sugar(Beverage* b) : Decorator(b){}
        string getDescription() const override{
            return beverage->getDescription() + ", Sugar";
        }
        double cost() const override{
            return beverage->cost() + 20.;
        }
};




int main(){
    // Coffe* coffe = new Coffe();
    // std::cout << coffe->cost() << std::endl;
    // Beverage* b_coffe = coffe;
    // std::cout << b_coffe->cost() << std::endl;

    // delete coffe;
    // delete b_coffe;
 
    Beverage* coffe = new Coffe();
    cout << coffe->getDescription() << endl;
    Beverage* milk_coffe = new Milk(coffe);
    cout << "Description: " << milk_coffe->getDescription() << endl;
    cout << "Cost" << milk_coffe->cost() << endl;
    Beverage* milk_sugar_coffe = new Sugar(milk_coffe);

    cout << "Description: " << milk_sugar_coffe->getDescription() << endl;
    cout << "Cost" << milk_sugar_coffe->cost() << endl;
 
    delete milk_sugar_coffe;

    return 0;
}