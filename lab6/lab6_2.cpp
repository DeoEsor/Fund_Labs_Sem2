#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <map>
#include <list>
#include <iterator>

#pragma region Error classes
class Monom_Exception
{
private:
    std::string m_error;
    monom* ptr=nullptr;
public:

    Monom_Exception(std::string error) : m_error(error) {}

    Monom_Exception(std::string error, monom* prt) : m_error(error), ptr(ptr) {}

    const std::string getError() { return m_error; }

    const monom* getPtr() { return ptr; }

};

class Polynom_Exception
{
private:
    std::string m_error;
public:

    Polynom_Exception(std::string error) : m_error(error) {}

    const std::string getError() { return m_error; }

};
#pragma endregion

class TeX_convertible {
protected:
    static const std::string mathpakage_tex;
    static const std::string doc_tex;
    static const std::string title_tex;
    static const std::string date_tex;
    static const std::string begin_tex;
    static const std::string end_tex;
    static const std::string iota_tex;
    static const std::string beginmatrix_tex;
    static const std::string endmatrix_tex;
public:
    static std::string Begin_Tex() {
        return  doc_tex + mathpakage_tex + title_tex + date_tex + begin_tex;
    }
    static std::string End_Tex() {
        return   end_tex;
    }
    //функция не может изменять члены-переменные того объекта,
    // к которому она принадлежит. Более того, из этой функции можно вызывать только такие же константные функции.
    virtual std::string convert() const = 0; //pure virtual (should be redefined)
};

#pragma region init of static of Tex
const std::string TeX_convertible::mathpakage_tex = "\\usepackage{amsmath}\n";
const std::string TeX_convertible::doc_tex = "\\documentclass{article}\n";
const std::string TeX_convertible::title_tex = "\\title{new}\n";
const std::string TeX_convertible::date_tex = "\\date{February 2021}\n";
const std::string TeX_convertible::begin_tex = "\\begin{document}\n\n";
const std::string TeX_convertible::end_tex = "\\end{document}";
const std::string TeX_convertible::iota_tex = "\\iota";
const std::string TeX_convertible::beginmatrix_tex = "\\begin{pmatrix}\n";
const std::string TeX_convertible::endmatrix_tex = "\\end{pmatrix}$\n";
#pragma endregion

#pragma region Monom
class monom : public TeX_convertible {
private:
    std::map<char, unsigned int> var;
    int koef;
public:
    monom(char* c)  //OLD:: -7*153^2*44^15 // str.c_str() string to char*
                    //NEW:: -7*a^2*b^3*c*
    {
        std::string str(c);
        int i;
        if (!isdigit(c[0])) {
            i = 1;
            koef = 0;
            while (str[i]!='*') {
                koef += (str[i] - '0') * pow(10, (i)-1);  i++;
                //koef += (c[i++] - '0') * pow(10, (i)-1);
            }
            if (str[0] == '-') koef *= -1;

        }
        else {
            i = 0;
            koef = 0;
            while (str[i] != '*')
                koef += (str[i] - '0') * pow(10, i);
        }
        i++;
        while( i < str.size()){ 
            int j = i+2; 
            while ( (str[j] != '*' || str[j] != '^') && j<str.size()) j++;
            int value;
            i+2   >= j-1? value=-1:value=std::stoi(str.substr(i + 2, j - 1));
            value == -1 ? value=1 : value;
            var[i] = value;
            i = ++j;
            
        }
    }

    monom(const monom& copy) : koef(copy.koef), var(copy.var){}

    ~monom() { var.clear(); }

#pragma region arithmetics operators
    void operator=(const monom& rightSummand){
        koef = rightSummand.koef;
        var = rightSummand.var;
    }

    monom const operator+(const monom& rightSummand) {
        
        return *this += rightSummand;
    }

    monom& operator+=(const monom& rightSummand) {
        if (var != rightSummand.var)  throw Monom_Exception("Different base of monoms",this);
        koef += rightSummand.koef;
        return *this;
    }

    monom const operator-(const monom& rightSummand) {

        return *this -= rightSummand;
    }

    monom& operator-=(const monom& rightSummand) {
        if (var != rightSummand.var)  throw Monom_Exception("Different base of monoms", this);
        koef -= rightSummand.koef;
        return *this;
    }

    monom operator*(const monom& rightSummand) {
        return *this *= rightSummand;
    }

    monom& operator*=(const monom& rightSummand) {
        for (auto& item : rightSummand.var)
        {
            if (auto it = var.find(item.first) != var.end())
                var[item.first] += item.second;
            else
                var[item.first] = item.second;
        }
        koef *= rightSummand.koef;
        return *this;
    }

    monom& operator*=(const int rightSummand) {
        koef *= rightSummand;
        return *this;
    }

    monom& operator/(const char c) {
        return *this /= c;
    }

    monom& operator/=(const char c)
    {
            for (auto& item : var)
                if (item.first == c)
                {
                    if (item.second == 1) var.erase(c);
                    else if (item.second = 0) continue;
                    else koef *= item.second--;
                    return *this;
                }

            var.clear();
            koef = 0;
            return *this;
    }

#pragma endregion

    bool operator!=(const monom& rightSummand) {
        return !(*this == rightSummand);
    }

    bool operator==(const monom& rightSummand) {
        if (koef != rightSummand.koef) return false;

        if (var != rightSummand.var) return false;

        for (auto& item : rightSummand.var)
            if (var[item.first] != item.second) return false;
        
        return true;
    }

    friend bool equal(const monom& it,const monom& rightSummand) {
        if (it.var != rightSummand.var) return false;
        return true;
    }

    int find_max_degree() {
        int result = 0;
        for (auto& it : var)
            result>it.second ? result :result= it.second;
        return result;
    }

    int find_full_degree() {
        int result = 0;
        for (auto& it : var)
            result += it.second;
        return result;
    }

    friend std::ofstream& operator<<(std::ofstream& stream,const  monom& obj)
    {
        stream << std::to_string(obj.koef) << std::endl;
        for (auto& el : obj.var) {
            stream << " * " << el.first;
        }
        stream << std::endl;
        for (auto& el : obj.var) {
            stream << el.first << " = " << std::to_string(el.second) << std::endl;
        }
        return stream;
    }

    std::map<char, unsigned int> getMap() {
        return var;
    }

    friend void operator>>(std::ifstream& stream, monom& obj)
    {
        std::string str;
        stream >> str;
        monom it((char*)str.c_str());
        obj=it;
    }

    std::string convert() const override{
        std::string str="";
        str += std::to_string(koef); 
        for (auto& el : var) {
            str += " * "; str += el.first; 
        } str += '\n';
        for (auto& el : var){
            str += el.first; str += " = "; str += std::to_string(el.second); str += '\n';}
        return str;
    }
};
#pragma endregion

#pragma region Polynom
class polynom : public TeX_convertible  {
    friend class monom;
    private:
        std::list <monom> poly;
    public:
        polynom(char* st) {
            std::string str(st);
            int i=0;
            while(i<str.size()){
                int j = i;
                for (;; i++)    if (str[i] == '+' || i==str.size()) break;
                monom el((char*)(str.substr(j, i - 1)).c_str());
                i++;
                poly.push_front(el);
            }
        }

        polynom(polynom& copy) {    poly=copy.poly; }

        polynom() {  }

        ~polynom() {    poly.clear();   }

        void operator=(const polynom& rightSummand) {
            poly = rightSummand.poly;
        }

        bool operator!=(const polynom& rightSummand) {
            return !(*this == rightSummand);
        }

        bool operator==(const polynom& rightSummand) {
            if(poly!=rightSummand.poly) return false;

            return true;
        }

        polynom& operator/=(const char c) {
            for (auto& it : poly)
                it /= c;
                
            return *this;
        }

        polynom operator/(const char c) {
            return *this/=c;
        }

        polynom& operator/=(const char *c)// предполагается, что буквы разделены разделителем 
        {
            std::string str(c);
            int i = 0;
            while (i < str.size()) {
                for (auto& it : poly)
                    it /= str[i];
                i += 2;
            }
            return *this;
        }

        polynom operator/(const char *c)// предполагается, что буквы разделены разделителем 
        {
            return *this /= c;
        }

        polynom& operator+=(const polynom& rightSummand) {
            try {
                for (auto& right : rightSummand.poly){
                    bool change=false;
                    for(auto& it : poly)
                        if (equal(it, right)) {
                            it += right; change = true;
                        }
                    if (!change)
                        poly.push_back(right);
                }
            }
            catch(Monom_Exception a){
                poly.push_back(*a.getPtr());
            }
            return *this;
        }

        polynom& operator+=(const monom& rightSummand) {
        
            for (auto& it : poly)
                if (equal(it, rightSummand)) {
                    it += rightSummand; return *this;
                }
            poly.push_back(rightSummand);
            return *this;
        }

        polynom operator+(const polynom& rightSummand) {
            return *this += rightSummand;
        }

        polynom& operator-=(const polynom& rightSummand) {
            try {
                for (auto& right : rightSummand.poly) {
                    bool change = false;
                    for (auto& it : poly)
                        if (equal(it, right)) {
                            it -= right; change = true;
                        }
                    if (!change){
                        monom reverse(right);
                        reverse *= (-1);
                        poly.push_back(reverse);
                    }
                }
            }
            catch (Monom_Exception a) {
                monom reverse(*a.getPtr());
                reverse *= (-1);
                poly.push_back(reverse);
            }
            return *this;
        }

        polynom operator-(const polynom& rightSummand) {
            return *this -= rightSummand;
        }

        polynom& operator*=(const polynom& rightSummand) {
            polynom result;
                for (auto& it : poly) {
                    for (auto& right : rightSummand.poly)
                        result += it*right;
                }

                *this = result;

            return *this;
        }

        polynom operator*(const polynom& rightSummand) {
            return *this *= rightSummand;
        }

        bool uniformity() {
            int i= 0;
            i = poly.front().find_full_degree();
            for (auto& it : poly)
                if(i!=it.find_full_degree()) return false;
            return true;
        }

        bool harmony()//В математике (общей алгебре) многочлен от нескольких переменных над полем называется гармоническим, если лапласиан этого многочлена равен нулю.
        // f=18*a*v*c + 19 *a*b +15 *a*a*f
        //d^2 (18*a*v*c)/da^2 + 18*a*v*c /dv^2 +18*a*v*c /dc^2 + 
        //df/da
        //df/dx
        //d^2f/dx^2
        //d^2f/dx^2 = d^2f/dx^2 + 
        // 
        {
            int result = 0;
            std::string allsym = "";
            for (auto& it : poly)
                for (auto& sym : it.getMap())
                    allsym += sym.first+ ' ';
            polynom res;
            res = *this / allsym.c_str();
            res/= allsym.c_str();
            if (poly.empty()) return true;
            return false;
        }

        friend std::ofstream& operator<<(std::ofstream& stream, polynom& obj)
        {
            for (std::list<monom>::iterator it = obj.poly.begin(); it != obj.poly.end(); ++it){
                stream << " + ";stream<< *it;
            }
            return stream;
        }

        friend void operator>>(std::ifstream& stream, polynom& obj)
        {
            std::string str="";
            stream >> str; 
            int i = 0;
            while (i<str.size()){
                monom it(   (char*)  str.substr(i,str.find('+')-1).c_str()  );
                obj.poly.push_front(it);
                i = str.find('+')+1;
            }
        }

        std::string convert() const override{
            std::string str;
            for (std::list<monom>::const_iterator it = poly.begin(); it != poly.end(); ++it)
                std::cout << " + " << (*it).convert();
            return str;
        }
};
#pragma endregion

#pragma region Client Code
int main() {
    char* str =(char*)"-7*153^2*44^15";

    monom A(str);

    monom B(str);

    std::cout << (A).convert();

    std::cout << (A + A).convert();

    std::cout << (A * A).convert();

    std::cout << (A / 'o').convert();

    return 0;
}
#pragma endregion