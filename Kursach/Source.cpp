#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#pragma region List class realization + iterator
template<class T>
class List {
    T value;
    List* next = nullptr;
    List* prev = nullptr;


    List* List() // а- значение первого узла
    {
        List* lst;
        // выделение памяти под корень списка
        lst = (List*)malloc(sizeof(List));
        lst->next = nullptr;
        lst->prev = nullptr;
        return(lst);
    }


    List* push(List* lst, _Ticket* a)  // а- значение первого узла
    {
        lst->next = (List*)malloc(sizeof(List));
        lst->next->value = a;
        lst->next->prev = lst;
        lst = lst->next;
        return(lst);
    }
};

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
    friend class List;
private:
    OwnIterator(ValueType* p);
    ValueType* p;
public:
    OwnIterator(const OwnIterator& it);

    bool operator!=(OwnIterator const& other) const;
    bool operator==(OwnIterator const& other) const; //need for BOOST_FOREACH
    typename OwnIterator::reference operator*() const;
    OwnIterator& operator++();

    template<typename ValueType>
    OwnIterator<ValueType>::OwnIterator(ValueType* p) :
        p(p)
    {

    }

    template<typename ValueType>
    OwnIterator<ValueType>::OwnIterator(const OwnIterator& it) :
        p(it.p)
    {

    }

    template<typename ValueType>
    bool OwnIterator<ValueType>::operator!=(OwnIterator const& other) const
    {
        return p != other.p;
    }

    template<typename ValueType>
    bool OwnIterator<ValueType>::operator==(OwnIterator const& other) const
    {
        return p == other.p;
    }

    template<typename ValueType>
    typename OwnIterator<ValueType>::reference OwnIterator<ValueType>::operator*() const
    {
        return *p;
    }
    template<typename ValueType>
    OwnIterator<ValueType>& OwnIterator<ValueType>::operator++()
    {
        ++p;
        return *this;
    }
};

#pragma endregion

#pragma region Abstract Factory
/**
  Каждый отдельный продукт семейства продуктов должен иметь базовый интерфейс.
  Все вариации продукта должны реализовывать этот интерфейс.
 */
class Ticket {
public:
    virtual ~Ticket() {};
    virtual void Fill_Ticket() = 0;
    virtual std::string Operation() const =0;
};

/**
  Конкретные продукты создаются соответствующими Конкретными Фабриками.
 */
class Loto_Ticket : public Ticket {
private:
    int first_field[3][5];
    int second_field[3][5];
public:
    void Fill_Ticket() override {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++)
            {
                first_field[i][j] = rand()  % 90;
                second_field[i][j] = rand() % 90;
            }
    }

    std::string Operation() const override{
        std::string output="";
        return output;
    }
};

/**
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
    virtual Ticket* CreateProductA() const = 0;
    virtual Lotery_Machine* CreateProductB() const = 0;
    virtual void Create_Lotery(const int number) = 0;
};

/*
  Конкретная Фабрика производит семейство продуктов одной вариации. Фабрика
  гарантирует совместимость полученных продуктов. Обратите внимание, что
  сигнатуры методов Конкретной Фабрики возвращают абстрактный продукт, в то
  время как внутри метода создается экземпляр конкретного продукта.
 */
class Loto_Fabrick : public AbstractFactory {
public:
    Ticket* CreateProductA() const override {
        return new Loto_Ticket();
    }
    Lotery_Machine* CreateProductB() const override {
        return new Loto_Machine();
    }
    
    void Create_Lotery(const int number)//should return collection of tickets (by decorator vector or list) and lotety machine
    {
        Lotery_Machine* product_b = CreateProductB();
        for (int i = 0; i < number; i++)
            Ticket* product_a = CreateProductA();

    }
};
#pragma endregion

#pragma region Decorator
template<class T>
class Decorator : public Ticket {
protected:
    T* component_;

public:
    Decorator(T* component) : component_(component) {
    }
    /**
      Декоратор делегирует всю работу обёрнутому компоненту.
     */
    std::string Output() const override {
        return this->component_->Operation();
    }
};
/**
  Конкретные Декораторы вызывают обёрнутый объект и изменяют его результат
  некоторым образом.
 */
template<class T>
class TicketDecorator : public Decorator {
    /**
      Декораторы могут вызывать родительскую реализацию операции, вместо того,
      чтобы вызвать обёрнутый объект напрямую. Такой подход упрощает расширение
      классов декораторов.
     */
public:
    TicketDecorator(T* component) : Decorator(component) {
    }
    std::string Output() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }
};
#pragma endregion

#pragma region Client Code
/*
  Клиентский код работает с фабриками и продуктами только через абстрактные
  типы: Абстрактная Фабрика и Абстрактный Продукт. Это позволяет передавать
  любой подкласс фабрики или продукта клиентскому коду, не нарушая его.
 */
int  Lotery_Logic(int col, std::vector<Ticket>& vectorof_ticket, List<Ticket>& listof_ticket) {
    Loto_Fabrick* f1 = new Loto_Fabrick();
    
    
    int countofsold; std::cin >> countofsold;
    delete f1;
    return 0;
}

/*Сохраняйте информацию о проведенных тиражах для обеспечения поиска
данных в будущем. Реализуйте функционал обработки данных таким образом,
чтобы тип коллекции, в которой будут храниться ваши данные, являлся
параметром*/
template<class T>
int Save_Data(T& el, std::string filepath) {
    T::iterator it=el;
    TicketDecorator decor();
    ofstream outputfile;             
    outputfile.open(filepath);
    while (it != el.end()) {
        decor(it);
        outputfile << decor.Output();
    }
    outputfile.close();
    return 0;
}

int main() {
    int col;
    std::cout << "Input count of tickets in lotery : ";
    std::cin >> col; std::cout<< std::endl;

    std::vector<Ticket> vectorof_ticket;
    List<Ticket> listof_ticket;

    Lotery_Logic(col, vectorof_ticket, listof_ticket);

    Save_Data(vectorof_ticket,(std::string)"Vector.out");
    Save_Data(listof_ticket, (std::string)"List.out");

    return 0;
}
#pragma endregion