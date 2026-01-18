#include <iostream>
#include <stdexcept>

class tableau 
{
    friend class Stack;

    int size;
    int nb_stack; //le nombre de Stack pointant vers ce tableau
    int nb; //la position du dernier élement ajouter dans le tableau
    int *tab;

    tableau(int size): size(size), nb_stack(1), nb(0) 
    {
        if (size <= 0)
        {
            throw std::length_error("Stack size must be positive");
        }
        tab = new int[size];
    }

    tableau(const tableau& tableau) : size(tableau.size), nb_stack(1), nb(tableau.nb), tab(tableau.tab) {
    }

    //Fonction pour incrémenter et décrémenter le compter de stack
    void incr() {
        std::cout << "[" << nb_stack << "]" << std::endl; //pour debuger
        nb_stack= nb_stack + 1;
    }

    void decr() {
        std::cout << "[" << nb_stack << "]" << std::endl; //pour debuger
        nb_stack = nb_stack -1;
    }

    int get_nb_stack () {
        return nb_stack;
    }

    void push(int val) 
    {
        tab[nb] = val;
        nb= nb + 1;
    }

    void print()
    {
        std::cout << "[ ";
        for (int i = nb - 1; i >= 0; i--)
        {
            std::cout << tab[i] << " ";
        }
        std::cout << "[" << std::endl;
    }

        bool is_empty()
    {
        if (nb == 0)
        {
            return true;
        }
        return false;
    }

    bool is_full()
    {
        if (nb < size)
        {
            return false;
        }
        return true;
    }

    int top()
    {
        if (is_empty())
        {
            throw std::length_error("Erreur: tab doesn't have enough space to add value");
        }
        return tab[nb - 1];
    }

    int pop()
    {
        if (is_empty())
        {
            std::out_of_range(std::string("Nothing to pop"));
        }
        nb = nb - 1;
        return tab[nb];
    }

    ~tableau(){
        delete[] tab;
    }

};

class Stack
{

    tableau *tab;
public:
    Stack(int size)
    {
        tab= new tableau(size);
    }

    Stack& operator=(const Stack& stack) {
        if (this != &stack) {
            tab = new tableau((stack.tab)->size);
            stack.tab->incr();
        }
        return *this;
    }
    
    Stack(const Stack& stack) : tab(stack.tab) {
        tab->incr();
    }

    void push(int val)
    {
        tab->push(val);
    }

    void print()
    {
        std::cout << "{" << tab->get_nb_stack() << "}" << std::endl;
        tab->print();
    }

    bool is_empty()
    {
        return tab->is_empty();
    }

    bool is_full()
    {
        return tab->is_full();
    }

    int top()
    {
        return tab->top();
    }

    int pop()
    {
       return tab->pop();
    }

    ~Stack()
    {
        if (tab->get_nb_stack()<=1){
            delete tab;
        }
        else {
            tab->decr();
        }
    }
};

int main()
{
    Stack stack(5);
    stack.push(1);
    stack.print();
    Stack stack2(stack);
    stack2.push(2);
    stack.print();
    stack2.print();
    return 0;
}