#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <map>

double fact(int N)
{
    if (N < 0)
        return 0;
    if (N == 0 || N == 1)
        return 1;
    else
        return N * fact(N - 1);
}
//const, exception, friend
 
class MatrixException
{
private:
    std::string m_error;
public:

    MatrixException(std::string error): m_error(error){}

    const std::string getError() {return m_error; }

};

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

class matrix_square : public TeX_convertible {
private:
    double** a;
    int dimension;
    static const double e;
public:

#pragma region//constructs
    matrix_square(int b = 2) : dimension(b) {
        a = new double* [dimension];

        for (int i = 0; i < dimension; i++)
            a[i] = new double[dimension];

        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                i == j ? a[i][j] = 1 : a[i][j] = 0;
    };

    matrix_square(double** a) : a(a), dimension(sizeof(a) / sizeof(double**)) {
    };
    matrix_square(double** a, int b) : a(a), dimension(b) {};
#pragma endregion

    int get_dimension() const
    {
        return dimension;
    }

    matrix_square(const matrix_square& other) 
    {
        a = new double* [other.dimension];
        dimension = other.dimension;
        for (int i = 0; i < dimension; i++){
            a[i] = new double[dimension];
            for (int j = 0; j < dimension; j++)
                a[i][j] = other.a[i][j];
        }
    }

    matrix_square(const matrix_square& other, int dim)
    {
        a = new double* [dimension];
        for (int i = 0; i < dimension; i++)
            a[i] = new double[dimension];

        for (int i = 0; i < dimension, i < other.dimension; i++)
            for (int j = 0; j < dimension, j < other.dimension; j++)
                a[i][j] = other.a[i][j];
    }

    matrix_square(const matrix_square& other, int dim, int it, int jt)
    {
            if(it>dim || jt>dim) throw MatrixException("Invalid index");
            dimension=dim;
            a = new double* [dim];
            for (int i = 0; i < dim; i++)
                a[i] = new double[dim];
            int g=0,h = 0;
            for (int i = 0; i < dimension+1; i++) {
                if (i == it) continue;
                for (int j = 0; j < dimension+1; j++)
                {
                    if (j == jt) continue;
                    a[g][h++] = other.a[i][j];
                }
                g++;
            }
    }
    ~matrix_square() {
        for (int i = 0; i < dimension; i++)
            delete[] a[i];
        delete a;
    }

#pragma region//overloading arithmetic operations
    matrix_square& operator+(const matrix_square& rightSummand)
    {
            if (dimension != rightSummand.dimension) throw MatrixException("Different dimensions of operands");
            else return (*this) += rightSummand;
    }
    matrix_square& operator+(double rightSummand)
    {
        matrix_square inter(dimension);
        return (*this) += (inter * rightSummand);
    }
    matrix_square& operator+=(const matrix_square& rightSummand)
    {
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                a[i][j] += rightSummand.a[i][j];
        return (*this);
    }
    matrix_square& operator-(const matrix_square& rightSummand)
    {
        return (*this) -= rightSummand;
    }
    matrix_square& operator-(const double rightSummand)
    {
        matrix_square inter(dimension);
        return (*this) -= (inter * rightSummand);
    }
    matrix_square& operator-=(const matrix_square& rightSummand)
    {
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                a[i][j] -= rightSummand.a[i][j];
        return (*this);
    }

    matrix_square& operator*=(const matrix_square& rightSummand)
    {
            if (dimension != rightSummand.dimension) throw MatrixException("Dimension error");
            matrix_square ret(dimension);
            for (int i = 0; i < dimension; i++){
                for (int j = 0; j < dimension; j++)
                {
                    ret.a[i][j] = 0;
                    for (int k = 0; k < dimension; k++)
                        ret.a[i][j] += (a[i][k] * rightSummand.a[k][j]);
                }
            }
            return (*this)=(ret);
    }
    matrix_square& operator*(const double rightSummand)//ToDO: double*matrix
    {
        return (*this) *= rightSummand;
    }
    matrix_square& operator*=(const double rightSummand)
    {
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                a[i][j] *= rightSummand;

        return *this;
    }
    matrix_square& operator/(const double rightSummand)
    {
        return (*this) *= pow(rightSummand,-1);
    }

    matrix_square& operator=(const matrix_square& rightSummand)
    {
        if (rightSummand.dimension != dimension) dimension = rightSummand.dimension;
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                a[i][j] = rightSummand.a[i][j];
        return *this;
    }
#pragma endregion
    bool const operator!=(const matrix_square& rightSummand)
    {
        return !((*this) == (rightSummand));
    }
    bool const operator==(const matrix_square& rightSummand)
    {
        bool flag = true;
        if (dimension != rightSummand.dimension) return !flag;
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                if (a[i][j] != rightSummand.a[i][j]) flag = false;
        return flag;
    }
    const double* operator[] (int i) {
            if (i > dimension || sizeof(a[i]) != sizeof(double)) throw MatrixException("going out of the array");
            return a[i];
    }
    friend std::ofstream& operator<<(std::ofstream& stream, matrix_square& obj)
    {
        stream << obj.dimension << std::endl;
        for (int i = 0; i < obj.dimension; i++) {
            for (int j = 0; j < obj.dimension; j++)
                stream << " " << obj.a[i][j];
            stream << std::endl;
        }
        return stream;
    }
    friend std::ifstream& operator>>(std::ifstream& stream, matrix_square& obj)
    {
        stream >> obj.dimension;
        for (int i = 0; i < obj.dimension; i++)
            for (int j = 0; j < obj.dimension; j++)
                stream >> obj.a[i][j];
        return stream;
    }

#pragma region  // Matrix operators
    friend double det(const matrix_square& obj)
    {
            matrix_square it(obj);
            double d = 1.0;
            int k = 1; //(-1) в степени i
            if (it.dimension < 1) throw MatrixException("Imposible to calculate determination");
            if (it.dimension == 1) {
                d = it.a[0][0];
                return(d);
            }
            if (it.dimension == 2) {
                d = (it.a[0][0] * it.a[1][1]) - (it.a[1][0] * it.a[0][1]);
                return(d);
            }
            if (it.dimension > 2) {
                for (int i = 0; i < it.dimension - 1; i++)// Step 1 go to triangle form 
                {
                    for (int j = i + 1; j < it.dimension; j++)
                    {
                        double koef = it.a[j][i] / it.a[i][i];
                        for (int k = i; k < it.dimension; k++)
                            it.a[j][k] -= it.a[i][k] * koef;
                    }
                }
                for (int i = 0; i < it.dimension; i++) //Step 2 Calcylate main... Diagonale
                    d *= it.a[i][i];

            }
            return (d);
    }

    friend matrix_square& reverse(const matrix_square& obj)//thru det //TODO:
    {
            matrix_square obr_matr;
            double ddet = det(obj);
            if (ddet != 0.0) {
                for (int i = 0; i < obj.dimension; i++) {
                    for (int j = 0; j < obj.dimension; j++) {
                        int m = obj.dimension - 1;
                        matrix_square interval(obj, m, i, j);
                        obr_matr.a[i][j] = pow(-1.0, i + j + 2) * det(interval) / ddet;
                    }
                }
                transpon(obr_matr);
                return obr_matr;
            }
            else throw MatrixException("Imposible to calculate reverse matrix bcs determinant of matrix=0");   
    }
    friend matrix_square& transpon(matrix_square& obj)
    {
        matrix_square it(obj.dimension);
        for (int i = 0; i < obj.dimension; i++)
            for (int j = 0; j < obj.dimension; j++)
                it.a[j][i] = obj.a[i][j];

        return it;
    }
    friend double trace(const matrix_square& obj)
    {
        double sum = 0.0;
        for (int i = 0; i < obj.dimension; i++)
            sum += obj.a[i][i];
        return sum;
    }
    friend void pow(matrix_square& obj, int j)
    {
        matrix_square piw = obj;
        for (int i = 1; i < j; i++)
            piw *= obj;
        obj= piw;
    }
    friend matrix_square exp(matrix_square& obj)
    {
        matrix_square sum(obj.dimension);
        matrix_square nextit(obj.dimension);
        int i = 1;
        while (det(nextit) > e) {
            sum += nextit;
            nextit = ( obj * pow(fact(i), -1));
            obj *= obj;
        }
        obj= sum;
        return sum;
    }
#pragma endregion

    std::string convert() const override {
        std::string str = "_{" + std::to_string(dimension) + ',' + std::to_string(dimension) + "} = \n"
            + beginmatrix_tex;
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                j == (dimension - 1) ? str += (std::to_string(a[i][j]) + " \\\\ \n") :
                str += (std::to_string(a[i][j]) + " & ");

        return str + endmatrix_tex;
    }
};

#pragma region//init of static field
const double matrix_square::e = 1e-6;

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

matrix_square& operator+(const double left, matrix_square matr){
    return matr+=left;
}

matrix_square& operator*(const double left, matrix_square matr){
    return matr*=left;
}

int main() {
    std::ifstream text("1.txt");       std::ofstream f("lab6_1.tex");
    matrix_square matrix;              TeX_convertible* super = &matrix;
    f << (*super).Begin_Tex();
    char c = ' '; char matr = ' '; 
    std::string matrix_oper = "";
    std::map <char, matrix_square> mp;
    std::map<char, matrix_square>::iterator it;
    while (text.get(c)) {
        if (c == ' ' || c == '\t') continue;
        if (c == '\n') {
            matr = ' ';
            matrix_oper = "";
            f << c;
        }
        if (isalpha(c)) {
            if (c >= 'A' && c <= 'Z') {
                it = mp.find(c);
                if (it == mp.end()) {
                    matrix_square ma; mp[c] = ma;
                    f << "Created a new matrix $" << c << "$" << std::endl;
                    f << "$" << c << mp[c].convert() << std::endl;
                }
                matr = c;
            }
            else {
                while (c != ' ') {
                    matrix_oper += c;
                    text.get(c);
                }
                text.get(c); matr = c;
                if (matrix_oper == "exp") {
                    try{
                        f << "Exponent of matrix $" << matr << "$=" << (mp[matr]).convert();
                        exp(mp[matr]);
                        f << "is matrix $Exp" <<(mp[matr]).convert() << std::endl;
                    }
                    catch(MatrixException ex){
                        std::cout<<ex.getError();
                    }
                }
                if (matrix_oper == "tranc") {
                    try{
                        
                        f << "Transponet of matrix $" << matr << "$ is matrix $T" <<
                            transpon(mp[matr]).convert() << std::endl;
                    }
                    catch(MatrixException ex){
                        std::cout<<ex.getError();
                    }
                }
                if (matrix_oper == "trace") {
                    f << "Trace of matrix $" << matr << "$ is $" << trace(mp[matr]) << "$" << std::endl;
                }
                if (matrix_oper == "det") {
                    try{
                        f << "Determinant of matrix $" << matr << "$ = $" << 
                        (mp[matr]).convert() << "$" << "$ is $"<< det(mp[matr]) << "$"<< std::endl;
                    }
                    catch(MatrixException ex){
                        std::cout<<ex.getError();
                    }
                }
                if (matrix_oper == "reverse") {
                    matrix_square it(mp[matr]);
                    try{
                        f << "Reverse matrix of matrix $" << matr << "$ is matrix $Reverse" 
                            << reverse(mp[matr]).convert() << std::endl;
                        it *= mp[matr];
                        f << "Check" << (it).convert()<< std::endl;
                    }
                    catch(MatrixException ex){
                        std::cout<<ex.getError();
                    }
                }
            }
        }
        if (c == '+') {
            text.get(c);
            if (isalpha(c))
                try{
                    f << "Sum of $" << matr << "$ and $" << c << "$is $Sum" 
                        << (mp[matr] + mp[c]).convert() << std::endl;
                }
                catch(MatrixException ex){
                    std::cout<<ex.getError();
                }
            else
                f << "Sum of $" << matr << "$ and $" << c << "$is $Sum" 
                << (mp[matr] + ((c - '0') * 1.0)).convert() << std::endl;
        }
        if (c == '-') {
            text.get(c);
            if (isalpha(c))
                try{
                    f << "Sum of $" << matr << "$ and $-" << c << "$is $NotSum" <<
                        (mp[matr] - mp[c]).convert() << std::endl;
                    }
                catch(MatrixException ex){
                        std::cout<<ex.getError();
                    }
            else
                try{
                     f << "Sum of $" << matr << "$ and $-" << c << "$is $NotSum" <<
                        (mp[matr] - ((c - '0') * 1.0)).convert() << std::endl;
                }
                catch(MatrixException ex){
                    std::cout<<ex.getError();
                }
        }
        if (c == '=') {
            text.get(c);
            if (c == '=') {
                    f << "$" << matr << "==" << c << std::endl << "is";
                    f << (mp[matr] == mp[c]) << "$" << std::endl;
            }
            if (c == '!') {
                text.get(c);
                if (c == '=') {
                    text.get(c);
                    f << "$" << matr << "!=" << c << std::endl << "is";
                    f << (mp[matr] != mp[c]) << "$" << std::endl;
                }
            }
            else {
                text >> mp[matr];
                f << "$" << matr << mp[matr].convert();
            }
        }
        if (c == '*') {
            text.get(c);
            if (isalpha(c)) {
                try{
                    mp[matr] *= mp[c];
                    f << "Сomposition of $" << matr << "$ and $" << c 
                        << "$is $ Сomposition" << (mp[matr]).convert() << std::endl;
                }
                catch(MatrixException ex){
                    std::cout<<ex.getError();
                }

            }
            else f << 'С'+"omposition of $" << matr << "$ and $" << c <<
                "$is $ Сomposition" << (mp[matr] * ((c - '0') * 1.0)).convert() << std::endl;
        }
    }
    f << (*super).End_Tex();
    text.close();                      f.close();
    return 0;
}
