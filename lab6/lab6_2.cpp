#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <map>
#include <vector>

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

#pragma region //init of static of Tex
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

class monom : public TeX_convertible {
private:
    std::map<std::string, unsigned int> var;
    int koef;
public:
    monom(char* c) {
        std::string str(c);
        int i;
        if (!isdigit(c[0])) {
            i = 1;
            koef = 0;
            while (!isalpha(c[i])) {
                koef += (c[i] - '0') * pow(10, (i)-1);  i++;
            }
            if (c[0] == '-') koef *= -1;
        }
        else {
            i = 0;
            koef = 0;
            while (!isalpha(c[i]))
                koef += (c[i] - '0') * pow(10, i);
        }
        while( i < str.size() - 1){
            int j = i;
            while (!isalpha(c[i]) && j< str.size() - 1) j++;
            var[str.substr(i, j)];
            i = j;
        }
    }

    monom(const monom& copy) : koef(copy.koef), var(copy.var){}

    ~monom() {  var.clear();    }

#pragma region //arithmetics operators
    void operator=(const monom& rightSummand){
        koef = rightSummand.koef;
        var = rightSummand.var;
    }

    monom& operator+(const monom& rightSummand) {
        return *this += rightSummand;
    }

    monom& operator+=(const monom& rightSummand) {
        for (auto& item : rightSummand.var)
        {
            if (auto it = var.find(item.first) != var.end())
                var[item.first] += rightSummand.var[item.first];
            else
                var[item.first] = rightSummand.var[item.first];
        }
        koef += rightSummand.koef;
        return *this;
    }

    monom& operator*(const monom& rightSummand) {
        return *this *= rightSummand;
    }

    monom& operator+=(const monom& rightSummand) {
        for (auto& item : rightSummand.var)
        {
            if (auto it = var.find(item.first) != var.end())
                var[item.first] *= rightSummand.var[item.first];
            else
                var[item.first] = rightSummand.var[item.first];
        }
        koef *= rightSummand.koef;
        return *this;
    }

#pragma endregion

    std::string convert() {
        std::string str;
        return str;
    }
};

class polynom : TeX_convertible, monom {
    private:
        std::vector <monom> poly;
    public:
        std::string convert() {
            std::string str;
            return str;
        }
};