#include <iostream>
#include <string>
#include <vector>

typedef struct List{
    Ticket *value;
    List *next = nullptr;
    List* prev = nullptr;
} List;

List* init_list() // �- �������� ������� ����
{
    List* lst;
    // ��������� ������ ��� ������ ������
    lst = (List*)malloc(sizeof(List));
    lst->next = nullptr;
    lst->prev = nullptr;
    return(lst);
}


List* push(List* lst, _Ticket* a)  // �- �������� ������� ����
{
    lst -> next = (List*)malloc(sizeof(List));
    lst -> next -> value = a;
    lst -> next -> prev = lst;
    lst = lst->next;
    return(lst);
}

/**
 * ������ ��������� ������� ��������� ��������� ������ ����� ������� ���������.
 * ��� �������� �������� ������ ������������� ���� ���������.
 */
class _First_Field {
public:
    virtual ~_First_Field() {};
    virtual void Fill_First_Field () const = 0;
};

/**
 * ���������� �������� ��������� ���������������� ����������� ���������.
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
 * ������� ��������� ������� ��������. ��� �������� ����� ����������������� ����
 * � ������, �� ���������� �������������� �������� ������ ����� ���������� �����
 * � ��� �� ���������� ��������.
 */
class _Ticket {
    /* ������� B �������� �������� ��������������...*/
public:
    virtual ~_Ticket() {};
    virtual void UsefulFunctionB() const = 0;
    /*
     * � ����� ����������������� � ���������� A ��� �� ��������.
     *
     * ����������� ������� �����������, ��� ��� ��������, ������� ��� �������,
     * ����� ���������� �������� �, �������������, ����������.
     */
    virtual void AnotherUsefulFunctionB(const _First_Field& collaborator) const = 0;
};


/* ���������� �������� ��������� ���������������� ����������� ���������.*/
class Ticket : public _Ticket {
public:
    void UsefulFunctionB() const override {
        for (int i = 0; i < 3; i++)
            for (int j = 0;j < 5; j++)
                    ;
    }
    /* ������� B1 ����� ��������� �������� ������ � ��������� A1. ��� �� �����, ��
     * ��������� ����� ��������� ������������ �������� � � �������� ���������.
     */
    void AnotherUsefulFunctionB(const _First_Field& collaborator) const override {}
};

/**
 * ��������� ����������� ������� ��������� ����� �������, ������� ����������
 * ��������� ����������� ��������. ��� �������� ���������� ���������� � �������
 * ����� ��� ���������� �������� ������. �������� ������ ��������� ������ �����
 * ����������������� ����� �����. ��������� ��������� ����� ����� ���������
 * ��������, �� �������� ����� �������� ������������ � ���������� ������.
 */
class AbstractFactory {
public:
    virtual Filling_first_field* CreateProductA() const = 0;
    virtual Tour_Ticket* CreateProductB() const = 0;
};

/*
 * ���������� ������� ���������� ��������� ��������� ����� ��������. �������
 * ����������� ������������� ���������� ���������. �������� ��������, ���
 * ��������� ������� ���������� ������� ���������� ����������� �������, � ��
 * ����� ��� ������ ������ ��������� ��������� ����������� ��������.
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
 * ���������� ��� �������� � ��������� � ���������� ������ ����� �����������
 * ����: ����������� ������� � ����������� �������. ��� ��������� ����������
 * ����� �������� ������� ��� �������� ����������� ����, �� ������� ���.
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