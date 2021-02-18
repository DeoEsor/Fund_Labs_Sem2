#include <iostream>
#include <string>
#include <sstream>

class TeX_convertible{
    protected:
        const std::string doc_tex='\\'+"documentclass{article}\n";
            const std::string title_tex='\\'+"title{new}";
            const std::string date_tex='\\'+"date{February 2021}";
            const std::string begin_tex='\\'+"begin{document}";
        const std::string end_tex='\\'+"end{document}";
        const std::string iota_tex='\\'+"iota";
    public:
        std::string convert() const;//функция не может изменять члены-переменные того объекта,
        // к которому она принадлежит. Более того, из этой функции можно вызывать только такие же константные функции.

        //~TeX_convertible(){;}  Вопрос, а нужны ли абстракциям деструкторы тип.... это же тип данных который условно копируется 
        //в наследуемый..... хотя... к нему можно обращаться по виртуалке и след. ссылаться.....
        virtual std::string convert() = 0; 
};

class complex : TeX_convertible{
    private:
        double _a,_b;//a+bi
    public:
        complex(double _a=0.0, double _b=0.0) : _a(_a), _b(_b){};
    
        double getA() const
    	{
    		return _a;
	    }

    	double getB() const
    	{
		    return _b;
	    }
        std::string convert(){
        return doc_tex+title_tex+date_tex+begin_tex +std::to_string(_a) +" "+std::to_string(_b)+ iota_tex +end_tex;
        }
        friend std::ostream& operator<<(std::ostream& stream, const complex& obj)//move to TeX_convertible.convert
	    {
	    	return ;
    	}

};

int main(){
    TeX_convertible *p;
    complex comp(0.01,5.0);
    //p=&comp;
    comp.convert();
    return 0;
}