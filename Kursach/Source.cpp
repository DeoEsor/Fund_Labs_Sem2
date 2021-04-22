#include <iostream>
#include <string>
#include <vector>

typedef struct List{
    Ticket *value;
    List *next = nullptr;
    List* prev = nullptr;
} List;

List* init_list() // а- значение первого узла
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
    lst -> next = (List*)malloc(sizeof(List));
    lst -> next -> value = a;
    lst -> next -> prev = lst;
    lst = lst->next;
    return(lst);
}

/**
 * Каждый отдельный продукт семейства продуктов должен иметь базовый интерфейс.
 * Все вариации продукта должны реализовывать этот интерфейс.
 */
class _First_Field {
public:
    virtual ~_First_Field() {};
    virtual void Fill_First_Field () const = 0;
};

/**
 * Конкретные продукты создаются соответствующими Конкретными Фабриками.
 */
class First_Field : public _First_Field {
public:
    void Fill_First_Field() const override {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++)
                //ticket->first_field[i][j] =(int) (rand() % 90)
                ;
    }
};

/**
 * Базовый интерфейс другого продукта. Все продукты могут взаимодействовать друг
 * с другом, но правильное взаимодействие возможно только между продуктами одной
 * и той же конкретной вариации.
 */
class _Ticket {
    /* Продукт B способен работать самостоятельно...*/
public:
    virtual ~_Ticket() {};
    virtual void UsefulFunctionB() const = 0;
    /*
     * А также взаимодействовать с Продуктами A той же вариации.
     *
     * Абстрактная Фабрика гарантирует, что все продукты, которые она создает,
     * имеют одинаковую вариацию и, следовательно, совместимы.
     */
    virtual void AnotherUsefulFunctionB(const _First_Field& collaborator) const = 0;
};


/* Конкретные Продукты создаются соответствующими Конкретными Фабриками.*/
class Ticket : public _Ticket {
public:
    void UsefulFunctionB() const override {
        for (int i = 0; i < 3; i++)
            for (int j = 0;j < 5; j++)
                    ;
    }
    /* Продукт B1 может корректно работать только с Продуктом A1. Тем не менее, он
     * принимает любой экземпляр Абстрактного Продукта А в качестве аргумента.
     */
    void AnotherUsefulFunctionB(const _First_Field& collaborator) const override {}
};

/**
 * Интерфейс Абстрактной Фабрики объявляет набор методов, которые возвращают
 * различные абстрактные продукты. Эти продукты называются семейством и связаны
 * темой или концепцией высокого уровня. Продукты одного семейства обычно могут
 * взаимодействовать между собой. Семейство продуктов может иметь несколько
 * вариаций, но продукты одной вариации несовместимы с продуктами другой.
 */
class AbstractFactory {
public:
    virtual Filling_first_field* CreateProductA() const = 0;
    virtual Tour_Ticket* CreateProductB() const = 0;
};

/*
 * Конкретная Фабрика производит семейство продуктов одной вариации. Фабрика
 * гарантирует совместимость полученных продуктов. Обратите внимание, что
 * сигнатуры методов Конкретной Фабрики возвращают абстрактный продукт, в то
 * время как внутри метода создается экземпляр конкретного продукта.
 */
class FirstTour_fabric : public AbstractFactory {
public:
    Filling_first_field* CreateProductA() const override {
        return new Filling_first_field_tour1();
    }
    Tour_Ticket* CreateProductB() const override {
        return new Firsttour_Ticket();
    }
};

/*
 * Клиентский код работает с фабриками и продуктами только через абстрактные
 * типы: Абстрактная Фабрика и Абстрактный Продукт. Это позволяет передавать
 * любой подкласс фабрики или продукта клиентскому коду, не нарушая его.
 */
Info* Create_ticket(const AbstractFactory& factory,const int number) {
    Info *ticket=init_tick();
    ticket->number = number;
    const Filling_first_field* product_a = factory.CreateProductA();
    const Tour_Ticket* product_b = factory.CreateProductB();
    product_b->UsefulFunctionB(ticket);
    product_b->AnotherUsefulFunctionB(*product_a);
    delete product_a;
    delete product_b;
    return ticket;
}

int static LoteryLogic(int col){
    FirstTour_fabric* f1 = new FirstTour_fabric();
    static List* list=init_list(); 
    static std::vector<Info> collection;
    List* head=list;
    for(int i=0;i<col;i++){
        Info* tick = Create_ticket(*f1,i);
        std::cout << tick->number                << " " << 
                     tick->first_field[0][0]     << " " << 
                     tick->second_field[0][0]    <<std::endl;
        list=push(list,*tick);
        collection.push_back(*tick);
    }
    for (Info n : collection) {
        std::cout << n.first_field[0][0] << ", " << n.second_field[0][0] << std::endl;
    }
    delete f1;
    return 0;
}

int main() {
    int col;
    std::cout << "Input count of tickets in lotery : ";
    std::cin >> col; std::cout<< std::endl;
    LoteryLogic(col);
    return 0;
}