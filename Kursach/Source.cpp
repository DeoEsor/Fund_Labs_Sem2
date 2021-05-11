#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

#pragma region List class realization + iterator
template<class T>
class Node {
public:
    T* value = nullptr;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(T& val): value(val) {
    }
};
template<class T>
class List {
private:
    Node<T>* begin = nullptr;
    Node<T>* end = nullptr;
public:
    Node<T>* current = nullptr;
    List() {
        begin = (Node<T>*) malloc(sizeof(Node<T>));
        current = end = begin;
    }

    List( T* val)
    {
        begin = (Node<T>*) malloc(sizeof(Node<T>));
        begin->value = val;
        current= end = begin;
    }

    List* push_back(T* a) 
    {
        end->next = (Node<T>*)malloc(sizeof(Node<T>));
        end->next->value = a;
        end->next->prev = end;
        end = end->next;
        return(this);
    }

    List* push_front(T* a)  
    {
        begin->prev = (Node<T>*)malloc(sizeof(Node<T>));
        begin->prev->value = a;
        begin->prev->next = begin;
        begin = begin->prev;
        return(this);
    }

    T pop_back()  
    {
        T val = end->value;
        delete end->value;
        end = end->prev;
        end->next->prev = nullptr;
        free(end->next);
        end->next = nullptr;
        return(val);
    }

    T pop_front() 
    {
        T val = begin->value;
        delete begin->value;
        begin = begin->next;
        begin->prev->next = nullptr;
        free(begin->prev);
        begin->prev = nullptr;
        return(val);
    }

    int del(const int i) {
        Node<T> it = begin;
        for (int h = 0; h < i, it!=end; h++)
            it = it->next;
        if (it==end) return -1;

        return 0;
    }

    int del(Node<T> it) {
        Node<T> it = begin;
        for (int h = 0; it != end; h++)
            if (it == end) return -1;
        

        return 0;
    }

    Node<T>* began() {
        return begin;
    }

    Node<T>* enda() {
        return end;
    }
};
/*
struct Position {
    int* p;
    Position(int* p) : p(p) {}

    int& dereference() const; // Получение текущего элемента.
    bool equal(const Position& other) const; // Проверка на равенство.
    void increment(); // Перемещение вперед.
    void decrement(); // Перемещение назад.
    void advance(std::ptrdiff_t n);  // Перемещение на "n" элементов.
    std::ptrdiff_t distance_to(const Position& other) const; // Расстояние до другой позиции.
};
template<class T>
struct iterator : std::iterator<std::random_access_iterator_tag, T> {
    // Вложенный объект Position, и конструктор для него.
    Position pos;
    iterator(Position pos) : pos(pos) {}

    // Операции, необходимые для всех категорий итераторов.
    iterator() = default;
    iterator(const iterator&) = default;
    iterator& operator=(const iterator&) = default;
    ~iterator() = default;
    reference operator*() const { return pos.dereference(); }
    iterator& operator++() { pos.increment(); return *this; }
    iterator operator++(int) { auto old = *this; ++(*this); return old; }

    // Операции, необходимые для InputIterator.
    pointer operator->() const;

    // Операции, необходимые для BidirectionalIterator.
    iterator& operator--() { pos.decrement(); return *this; }
    iterator operator--(int) { auto old = *this; --(*this); return old; }

    // Операции, необходимые для RandomAccessIterator.
    reference operator[](difference_type n) const { auto tmp = *this; tmp += n; return *tmp; }
    iterator& operator+=(difference_type n) { pos.advance(n); return *this; }
    iterator& operator-=(difference_type n) { return *this += -n; }


// Операции, необходимые для всех категорий итераторов.
void swap(iterator& a, iterator& b) { std::swap(a.pos, b.pos); }

// Операции, необходимые для InputIterator.
bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.pos.equal(rhs.pos); }
bool operator!=(const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }

// Операции, необходимые для RandomAccessIterator.
bool operator<(const iterator& lhs, const iterator& rhs) { return lhs.pos.distance_to(rhs.pos) > 0; }
bool operator>(const iterator& lhs, const iterator& rhs) { return rhs < lhs; }
bool operator<=(const iterator& lhs, const iterator& rhs) { return !(rhs > lhs); }
bool operator>=(const iterator& lhs, const iterator& rhs) { return !(lhs < rhs); }
iterator operator+(iterator it, iterator::difference_type n) { it += n; return it; }
iterator operator+(iterator::difference_type n, iterator it) { return it + n; }
iterator operator-(iterator it, iterator::difference_type n) { it -= n; return it; }
iterator::difference_type operator-(const iterator& lhs, const iterator& rhs) { return rhs.pos.distance_to(lhs.pos); }
};
//----------------------------------------------------------------------------------------

int& Position::dereference() const { return *p; }
bool Position::equal(const Position& other) const { return p == other.p; }
void Position::increment() { ++p; }
void Position::decrement() { --p; }
void Position::advance(std::ptrdiff_t n) { p += n; }
std::ptrdiff_t Position::distance_to(const Position& other) const { return other.p - p; }

*/
#pragma endregion

#pragma region Abstract Factory
/**
  Каждый отдельный продукт семейства продуктов должен иметь базовый интерфейс.
  Все вариации продукта должны реализовывать этот интерфейс.
 */
class Ticket {
protected:
    virtual void Fill_Ticket() = 0;
public:
    virtual ~Ticket() {};
    virtual std::string Write() const =0;
};

/**
  Конкретные продукты создаются соответствующими Конкретными Фабриками.
 */
class Loto_Ticket : public Ticket {
private:
    int number;
    int score;
    int first_field[3][5];
    int second_field[3][5];

    void Fill_Ticket() override {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++)
            {
                first_field[i][j] = rand() % 90;
                second_field[i][j] = rand() % 90;
            }
    }
public:
    Loto_Ticket() {
        this->Fill_Ticket();
    }

    std::string Write() const override{
        std::string output = '\n'+'"' + "number" + '"' + ':' + number + ',' + '\n';
        output += '"' +"score" + '"' + ':' + score+ ',' + '\n';

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++){
                output += '"' + "first_field" + '"' + ':' + first_field[i][j] + ',' + '\n';
                output += '"' + "second_field" + '"' + ':' + second_field[i][j] + ',' + '\n';
            }
        return output;
    }

    /*предоставьте возможность
    поиска билетов по заданным критериям: номеру билета, величине выигрыша, и
    т. д..
    template<class T>
    friend Loto_Ticket Find(const T& el,const int number) {
        T::iterator it = el.begin();
        while (it != el.end()) {
            if(it->number==number)
                return *it
        }
    }

    template<class T>
    friend T* Find(const T& el, const int score) {
        T::iterator it = el.begin();
        while (it != el.end()) {
            if (it->score == score)
                it;
        }
    }*/
};

/*
  Базовый интерфейс другого продукта. Все продукты могут взаимодействовать друг
  с другом, но правильное взаимодействие возможно только между продуктами одной
  и той же конкретной вариации.
 */
class Lotery_Machine {
    /* Продукт B способен работать самостоятельно...*/
public:
    virtual ~Lotery_Machine() {};
    virtual void UsefulFunctionB() const = 0;
    /*
      А также взаимодействовать с Продуктами A той же вариации.
     
      Абстрактная Фабрика гарантирует, что все продукты, которые она создает,
      имеют одинаковую вариацию и, следовательно, совместимы.
     */
    virtual void AnotherUsefulFunctionB(const Ticket& collaborator) const = 0;
};

/* Конкретные Продукты создаются соответствующими Конкретными Фабриками.*/
class Loto_Machine : public Lotery_Machine {
public:
    void UsefulFunctionB() const override {
        for (int i = 0; i < 3; i++)
            for (int j = 0;j < 5; j++)
                    ;
    }
    /* Продукт B1 может корректно работать только с Продуктом A1. Тем не менее, он
       принимает любой экземпляр Абстрактного Продукта А в качестве аргумента.
     */
    void AnotherUsefulFunctionB(const Ticket& collaborator) const override {
        
    }
};

/**
  Интерфейс Абстрактной Фабрики объявляет набор методов, которые возвращают
  различные абстрактные продукты. Эти продукты называются семейством и связаны
  темой или концепцией высокого уровня. Продукты одного семейства обычно могут
  взаимодействовать между собой. Семейство продуктов может иметь несколько
  вариаций, но продукты одной вариации несовместимы с продуктами другой.
 */
class AbstractFactory {
public:
    virtual Ticket* CreateTicket() const = 0;
    virtual Lotery_Machine* CreateMachine() const = 0;
};

/*
  Конкретная Фабрика производит семейство продуктов одной вариации. Фабрика
  гарантирует совместимость полученных продуктов. Обратите внимание, что
  сигнатуры методов Конкретной Фабрики возвращают абстрактный продукт, в то
  время как внутри метода создается экземпляр конкретного продукта.
 */
class Loto_Fabrick : public AbstractFactory {
public:
    Ticket* CreateTicket() const override {
        return new Loto_Ticket();
    }
    Lotery_Machine* CreateMachine() const override {
        return new Loto_Machine();
    }
    
};
#pragma endregion

#pragma region Decorator

class Decorator : public Ticket {
protected:
    Ticket* component_;
    void Fill_Ticket()  override {}
public:
    Decorator(Ticket* component) : component_(component) {
    }
   
    /**
      Декоратор делегирует всю работу обёрнутому компоненту.
     */
    std::string Write() const override {
        return this->component_->Write();
    }
};
/**
  Конкретные Декораторы вызывают обёрнутый объект и изменяют его результат
  некоторым образом.
 */
class TicketDecorator : public Decorator {
    /**
      Декораторы могут вызывать родительскую реализацию операции, вместо того,
      чтобы вызвать обёрнутый объект напрямую. Такой подход упрощает расширение
      классов декораторов.
     */
public:
    TicketDecorator(Ticket* component) : Decorator(component) {
    }
    std::string Write() const override {
        return "ticket :{" + Decorator::Write() +"}";
    }
};
#pragma endregion

#pragma region Client Code
/*
  Клиентский код работает с фабриками и продуктами только через абстрактные
  типы: Абстрактная Фабрика и Абстрактный Продукт. Это позволяет передавать
  любой подкласс фабрики или продукта клиентскому коду, не нарушая его.
 */
int  Lotery_Logic(AbstractFactory& factory,int col, std::vector<Loto_Ticket>& vectorof_ticket, List<Loto_Ticket>& listof_ticket) {
    
    Lotery_Machine* generator = factory.CreateMachine();
    
    for(int i=0;i<col;i++){
        //vectorof_ticket.push_back(factory.CreateTicket());
        listof_ticket.push_back( (Loto_Ticket *) factory.CreateTicket());
    }
    int countofsold; std::cin >> countofsold; 
    delete generator;
    return 0;
}

/*Сохраняйте информацию о проведенных тиражах для обеспечения поиска
данных в будущем. Реализуйте функционал обработки данных таким образом,
чтобы тип коллекции, в которой будут храниться ваши данные, являлся
параметром*/
int Save_Data(List<Loto_Ticket> &el, const std::string filepath) {
    std::ofstream outputfile;
    outputfile.open(filepath);
    /*T::iterator it=el;
    TicketDecorator decor();!!wrong
    
    while (it != el.end()) {
        decor(it);
        outputfile << decor.Output();
    }
    */
    for (Node<Loto_Ticket>* i = el.began(); i != nullptr; i = i->next){
        Ticket* decor = new TicketDecorator(i->value);
        outputfile << decor->Write();
        std::cout<< decor->Write();
        delete decor;
    }

        outputfile.close();
    return 0;
}


int main() {
    int col;
    std::cout << "Input count of tickets in lotery : ";
    std::cin >> col; std::cout<< std::endl;

    Loto_Fabrick* factory = new Loto_Fabrick();

    std::vector<Loto_Ticket> vectorof_ticket = *new std::vector<Loto_Ticket>();
    List<Loto_Ticket> listof_ticket = *new List<Loto_Ticket>();

    Lotery_Logic(*factory, col, vectorof_ticket, listof_ticket);

    //Save_Data(vectorof_ticket,(std::string)"Vector.json");
    
        Save_Data(listof_ticket,(std::string)"List.json");
    delete factory;
    return 0;
}
#pragma endregion