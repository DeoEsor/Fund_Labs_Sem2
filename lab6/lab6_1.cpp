#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

const double e = 1e-6;

class TeX_convertible {
protected:
    const std::string mathpakage_tex = "\\usepackage{amsmath}\n";
    const std::string doc_tex = "\\documentclass{article}\n";
    const std::string title_tex = "\\title{new}\n";
    const std::string date_tex = "\\date{February 2021}\n";
    const std::string begin_tex = "\\begin{document}\n";
    const std::string end_tex = "\\end{document}";
    const std::string iota_tex = "\\iota";
    const std::string beginmatrix_tex = "\\begin{pmatrix}\n";
    const std::string endmatrix_tex = "\\end{pmatrix}\n";
public:
    //функция не может изменять члены-переменные того объекта,
    // к которому она принадлежит. Более того, из этой функции можно вызывать только такие же константные функции.

    //~TeX_convertible(){;}  Вопрос, а нужны ли абстракциям деструкторы тип.... это же тип данных который условно копируется 
    //в наследуемый..... хотя... к нему можно обращаться по виртуалке и след. ссылаться.....
    virtual std::string convert() const = 0; //pure virtual (should be redefined)
};

class matrix_square : public TeX_convertible {
private:
    double** a;
    unsigned int dimension;
public:

#pragma region//constructs
    matrix_square(int b = 3) : dimension(b) {
        a = new double* [dimension];

        for (int i = 0; i < dimension; ++i)
            a[i] = new double[dimension];

        for (int i = 0; i < dimension; ++i)
            for (int j = 0; j < dimension; ++j)
                a[i][j] = 0;
    };

    matrix_square(double** a) : a(a) {
        for (int i = 0; i < 10; ++i)
            if (sizeof(a[i]) != sizeof(double)) {
                dimension = i + 1;
                break;
            }
    };
    matrix_square(double** a, int b) : a(a), dimension(b) {};
#pragma endregion

    int set_pointer(double** a_) {
        a = a_;
        return 0;
    }
    int set_dimension(int b) {
        dimension = b;
        return 0;
    }

    int get_dimension() const
    {
        return dimension;
    }
    double** get_pointer() const
    {
        return a;
    }

    matrix_square(const matrix_square& other)
    {
        set_pointer(other.get_pointer());
        set_dimension(other.get_dimension());
    }
    matrix_square(const matrix_square& other, int dimension)
    {
        set_pointer(other.get_pointer());
        set_dimension(dimension);
    }
    ~matrix_square() {
        for (int i = 0; i < dimension; i++)
            delete[] a[i];
        delete[] a;
    }

#pragma region//overloading arithmetic operations
    matrix_square& operator+(const matrix_square& rightSummand)
    {
        try {
            if (dimension > rightSummand.dimension)
                return (*this) += rightSummand;
        }
        catch (int a) {
            perror("Different dimensions of operands");
        }
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
    matrix_square& operator-=(const matrix_square& rightSummand)
    {
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                a[i][j] -= rightSummand.a[i][j];
        return (*this);
    }

    matrix_square& operator*(const matrix_square& rightSummand)
    {
        return (*this) *= rightSummand;
    }
    matrix_square& operator*=(const matrix_square& rightSummand)
    {
        matrix_square ret(get_dimension());
        for (int i = 0; i < get_dimension(); i++)
            for (int j = 0; j < get_dimension(); j++)
            {
                ret.a[i][j] = 0;
                for (int k = 0; k <= get_dimension(); k++)
                    ret.a[i][j] += (a[i][k] * rightSummand.a[k][j]);
            }
        return ret;
    }
    matrix_square& operator*(const double rightSummand)
    {
        return (*this) *= rightSummand;
    }
    matrix_square& operator*=(const double rightSummand)
    {
        for (int i = 0; i < get_dimension(); i++)
            for (int j = 0; j < get_dimension(); j++)
                a[i][j] *= rightSummand;

        return *this;
    }

    matrix_square& operator=(const matrix_square& rightSummand)
    {
        set_pointer(rightSummand.get_pointer());
        set_dimension(rightSummand.get_dimension());
        return *this;
    }
#pragma endregion
    bool operator==(const matrix_square& rightSummand)
    {
        bool flag = true;
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                if (a[i][j] != rightSummand.a[i][j]) flag = false;
        return flag;
    }
    double* operator[] (int i) {
        try {
            if (i > dimension || sizeof(a[i]) != sizeof(double)) throw - 1;
            return a[i];
        }
        catch (int a) {
            perror("going out of the array");
        }
    }
    friend std::ostream& operator<<(std::ostream& stream, const matrix_square& obj)
    {
        stream << obj.dimension << std::endl;
        for (int i = 0; i < obj.get_dimension(); i++) {
            for (int j = 0; j < obj.get_dimension(); j++)
                stream << " " << obj.a[i][j];
            stream << std::endl;
        }
        return stream;
    }
    friend std::istream& operator>>(std::istream& stream, matrix_square& obj)
    {
        stream >> obj.dimension;
        for (int i = 0; i < obj.get_dimension(); i++)
            for (int j = 0; j < obj.get_dimension(); j++)
                stream >> obj.a[i][j];
        return stream;
    }
#pragma region  // Matrix operators
    friend double det(const matrix_square& obj)
    {
        try {
            double d;
            int k = 1; //(-1) в степени i
            if (obj.get_dimension() < 1) throw - 1;
            if (obj.get_dimension() == 1) {
                d = obj.a[0][0];
                return(d);
            }
            if (obj.get_dimension() == 2) {
                d = (obj.a[0][0] * obj.a[1][1]) - (obj.a[1][0] * obj.a[0][1]);
                return(d);
            }
            if (obj.get_dimension() > 2) {
                for (int i = 0; i < obj.dimension - 1; i++)
                {
                    for(int j = i + 1; j < obj.dimension; j++)
                    {
                    double koef = obj.a[j][i] / obj.a[i][i];
                    for (int k = i; k < obj.dimension; k++)
                        obj.a[j][k] -= obj.a[i][k] * koef;
                    }
                }
                for (int i = 0; i < obj.get_dimension(); i++) {
                    d*=obj.a[i][i];
                }
            }
            return(d);
        }
        catch (int a) {
            perror("Imposible to calculate determination");
            return -1;
        }
    }

    matrix_square& reverse(matrix_square& obj)//thru det //TODO:
    {
        try{
            if( det(obj) != 0.0) {
                for(int i = 0; i < dimension; i++){
                    for(int j = 0; j < dimension; j++){
                        int m = dimension - 1;
                        int **temp_matr = new int * [m];
                            for(int k = 0; k < m; k++)
                                ;
                    }
                }
            }
            else throw -1;
        }
        catch(int a){
            perror("Imposible to calculate reverse matrix bcs determinant of matrix=0");
        }
    }
    matrix_square& Transpon(const matrix_square& obj)
    {
        for (int i = 0; i < get_dimension(); i++)
            for (int j = 0; j < get_dimension(); j++)
                a[j][i] = obj.a[i][j];

        return(*this);
    }
    friend double exp(const matrix_square& obj)
    {

    }
#pragma endregion

    std::string convert() const {
        std::string str = mathpakage_tex + doc_tex + title_tex + date_tex + begin_tex + '\n' + "A_{" + std::to_string(dimension)
            + ',' + std::to_string(dimension) + "}=\n" + beginmatrix_tex;
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                j == dimension - 1 ? str += (std::to_string(a[i][j]) + " \\\\ \n") :
                str += (std::to_string(a[i][j]) + " & ");

        return str + endmatrix_tex + end_tex;
    }
};

int main() {
    std::ofstream f("lab6_1.tex");
    matrix_square matrix;
    TeX_convertible* it = &matrix;
    std::cin >> matrix;
    std::cout << matrix;
    f << matrix.convert();
    f.close();
    return 0;
}