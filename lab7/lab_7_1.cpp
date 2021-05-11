#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <map>
#include <list>
#include <iterator>

/*Опишите абстрактный шаблонный класс binary_tree<T>,
представляющий собой абстракцию дерева поиска (тип элементов
указывается в единственном параметре шаблона). Класс должен
содержать три чистых виртуальных функции: добавления элемента в
дерево, удаления элемента из дерева, поиска элемента в дереве по
значению. Конструктор класса должен принимать в качестве
параметра шаблонный компаратор (правило вычисления отношения
порядка между данными в узлах дерева), реализованный в виде
объекта стратегии (см. паттерн “Стратегия”).
*/
#pragma region Binary_Tree<T> + Strategy Comparator
template <class T>
class Strategy {
public:
    virtual ~Strategy() {}
    virtual bool CMP(T &left, T& right) const = 0;
};

template <class T>
class Comparator1 : public Strategy<T> {
public:
    bool CMP(T& left, T& right) const override {
        if (left->data > right->data) return true;
        return false;
    }
};

template <class T>
class Comparator2 : public Strategy<T> {
public:
    bool CMP(T& left, T& right) const override {
        if (left->key > right->key) return true;
        return false;
    }
};

template<class T>
class binary_tree 
    /*Класс должен
содержать три чистых виртуальных функции: добавления элемента в
дерево, удаления элемента из дерева, поиска элемента в дереве по
значению.*/
{
public:
    virtual void Add(const T ) = 0;
    virtual void Erase(const T& ) = 0;
    virtual void* Find(T&) = 0;
};
#pragma endregion

#pragma region Red Black Tree
typedef enum { BLACK, RED } nodeColor;

template<class T>
struct Node {
    struct Node_* left;         /* left child */
    struct Node_* right;        /* right child */
    struct Node_* parent;       /* parent */
    nodeColor color;            /* node color (BLACK, RED) */
    T data;                     /* data stored in node */
};

template<class T>
class RedBlackTree : public binary_tree<T> {
private:
    Strategy<T>* cmp=nullptr;
    T* root;
public:
    RedBlackTree(Strategy<T>* cmp): cmp(cmp) {}

    void rotateLeft(T* x)  {

        /**************************
         *  rotate node x to left *
         **************************/

        Node* y = x->right;

        /* establish x->right link */
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;

        /* establish y->parent link */
        if (y != nullptr) y->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
        }
        else {
            root = y;
        }

        /* link x and y */
        y->left = x;
        if (x != nullptr) x->parent = y;
    }

    void rotateRight(T* x)  {

        /****************************
         *  rotate node x to right  *
         ****************************/

        Node* y = x->left;

        /* establish x->left link */
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;

        /* establish y->parent link */
        if (y != nullptr) y->parent = x->parent;
        if (x->parent) {
            if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
        }
        else {
            root = y;
        }

        /* link x and y */
        y->right = x;
        if (x != nullptr) x->parent = y;
    }

    void insertFixup(T* x)  {

        /*************************************
         *  maintain Red-Black tree balance  *
         *  after inserting node x           *
         *************************************/

         /* check Red-Black properties */
        while (x != root && x->parent->color == RED) {
            /* we have a violation */
            if (x->parent == x->parent->parent->left) {
                Node* y = x->parent->parent->right;
                if (y->color == RED) {

                    /* uncle is RED */
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else {

                    /* uncle is BLACK */
                    if (x == x->parent->right) {
                        /* make x a left child */
                        x = x->parent;
                        rotateLeft(x);
                    }

                    /* recolor and rotate */
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rotateRight(x->parent->parent);
                }
            }
            else {

                /* mirror image of above code */
                Node* y = x->parent->parent->left;
                if (y->color == RED) {

                    /* uncle is RED */
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else {

                    /* uncle is BLACK */
                    if (x == x->parent->left) {
                        x = x->parent;
                        rotateRight(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rotateLeft(x->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void Add(const T item) override {
        Node* current, * parent, * x;

        /***********************************************
         *  allocate node for data and insert in tree  *
         ***********************************************/

         /* find where node belongs */
        current = root;
        parent = 0;
        while (current != nullptr) {
            if (*cmp->CMP(item, current->data)) return (current);
            parent = current;
            current = !*cmp->CMP(item, current->data) ?
                current->left : current->right;
        }

        /* setup new node */
        if ((x =(Node*) malloc(sizeof(*x))) == 0) {
            printf("insufficient memory (insertNode)\n");
            exit(1);
        }
        x->data = item;
        x->parent = parent;
        x->left = nullptr;
        x->right = nullptr;
        x->color = RED;

        /* insert node in tree */
        if (parent) {
            if (compLT(item, parent->data))
                parent->left = x;
            else
                parent->right = x;
        }
        else {
            root = x;
        }

        insertFixup(x);
        return(x);
    }

    void deleteFixup(T* x) {

        /*************************************
         *  maintain Red-Black tree balance  *
         *  after deleting node x            *
         *************************************/

        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void Erase(const T& item) override {
        Node* x, * y;

        /*****************************
         *  delete node z from tree  *
         *****************************/

        if (!item || item == nullptr) return;


        if (item->left == nullptr || item->right == nullptr) {
            /* y has a nullptr node as a child */
            y = item;
        }
        else {
            /* find tree successor with a nullptr node as a child */
            y = item->right;
            while (y->left != nullptr) y = y->left;
        }

        /* x is y's only child */
        if (y->left != nullptr)
            x = y->left;
        else
            x = y->right;

        /* Erase y from the parent chain */
        x->parent = y->parent;
        if (y->parent)
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        else
            root = x;

        if (y != item) item->data = y->data;


        if (y->color == BLACK)
            deleteFixup(x);

        free(y);
    }

    Node* Find(const T& data) override {

        /*******************************
         *  find node containing data  *
         *******************************/

        Node* current = root;
        while (current != nullptr)
            if (*cmp->CMP(data, current->data))
                return (current);
            else
                current = compLT(data, current->data) ?
                current->left : current->right;
        return(0);
    }
};

#pragma endregion

#pragma region AVL Tree
template<class T>
struct node // структура для представления узлов дерева
{
    T key;
    unsigned char height;
    node* left;
    node* right;
    node(T k) { key = k; left = right = 0; height = 1; }
};

template<class T>
class AVLTree : public binary_tree<T> {
private: 
    Strategy* cmp = nullptr;
    T* root;
public:
    AVLTree(Strategy *cmp):cmp(cmp){}

    unsigned char height(node* p)
    {
        return p ? p->height : 0;
    }

    int bfactor(node* p)
    {
        return height(p->right) - height(p->left);
    }

    void fixheight(node* p)
    {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }

    node* rotateright(node* p) // правый поворот вокруг p
    {
        node* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    node* rotateleft(node* q) // левый поворот вокруг q
    {
        node* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    node* balance(node* p) // балансировка узла p
    {
        fixheight(p);
        if (bfactor(p) == 2)
        {
            if (bfactor(p->right) < 0)
                p->right = rotateright(p->right);
            return rotateleft(p);
        }
        if (bfactor(p) == -2)
        {
            if (bfactor(p->left) > 0)
                p->left = rotateleft(p->left);
            return rotateright(p);
        }
        return p; // балансировка не нужна
    }

    void Add(const T k) override // вставка ключа k в дерево с корнем p
    {
        node* p = root;
        if (!p) return new node(k);
        if (*cmp->CMP(k , p->key))
            p->left = insert(p->left, k);
        else
            p->right = insert(p->right, k);
        balance(p);
    }

    void insert(node* p,const T k) // вставка ключа k в дерево с корнем p
    {
        if (!p) return new node(k);
        if (*cmp->CMP(k, p->key))
            p->left = insert(p->left, k);
        else
            p->right = insert(p->right, k);
        balance(p);
    }

    node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
    {
        return p->left ? findmin(p->left) : p;
    }

    node* Find( node* p, T k) {
        if (p != NULL)
        {
            if (p->key == k) return p;
            if (*cmp->CMP(p->key, k)) return Find(p->left, k);
            else return Find(p->right, k);
        }
        
    }

    node* Find(T& k) override{
        if (p != NULL)
        {
            if (p->key == k) return p;
            if (p->key > k) return Find(p->left, k);
            else return Find(p->right, k);
        }
    }

    node* Erasemin(node* p) // удаление узла с минимальным ключом из дерева p
    {
        if (p->left == 0)
            return p->right;
        p->left = Erasemin(p->left);
        return balance(p);
    }

    node* Erase(const T& T k) override // удаление ключа k из дерева p
    {
        node *p = root;
        if (!p) return 0;
        if (k < p->key)
            p->left = Erase(p->left, k);
        else if (k > p->key)
            p->right = Erase(p->right, k);
        else //  k == p->key 
        {
            node* q = p->left;
            node* r = p->right;
            delete p;
            if (!r) return q;
            node* min = findmin(r);
            min->right = Erasemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }

    node* Erase(Node* p,const T& T k) // удаление ключа k из дерева p
    {
        if (!p) return 0;
        if (k < p->key)
            p->left = Erase(p->left, k);
        else if (k > p->key)
            p->right = Erase(p->right, k);
        else //  k == p->key 
        {
            node* q = p->left;
            node* r = p->right;
            delete p;
            if (!r) return q;
            node* min = findmin(r);
            min->right = Erasemin(r);
            min->left = q;
            return balance(min);
        }
        return balance(p);
    }
};
#pragma endregion
#pragma region Client Code

#pragma endregion