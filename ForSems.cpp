#include <iostream>

using namespace std;

namespace NEW{
using namespace std;

}

class complex{
    private:
        double _a,_b; // 
    public:
        // complex(double _a, double _b = 0 // если не обьявлен неявно обьявляется, при этом после него все также должен быть по умолчанию){
        //     this->_a=_a;
        //     this->_b=_b;
        // }
        //побитовая быстрая инициализация (конструктор со списком инициализации)
        complex(double _a, double _b) : _a(_a), _b(_b){};
        ~complex(){;}
        double get_A(){return _a;}
        double get_B(){return _b;}
};

int main(){
    complex it( 1.0 , 2.0 );
    cout<< it.get_A()<<endl;
    cout<<it.get_B();
    return 0;
}