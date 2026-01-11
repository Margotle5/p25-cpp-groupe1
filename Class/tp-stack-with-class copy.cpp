#include <iostream>
#include <stdexcept>

struct tab 
{
    int size;
    int nb_Stack;
    int *tab;
    
};

struct Stack
{
    int size;
    int nb;
    int *tab;

    Stack(int s) : size(s), nb(0)
    {
        if (s <= 0)
        {
            throw std::length_error("Stack size must be positive");
        }
        tab = new int[size];
    }
    void push(int val)
    {
        tab[nb] = val;
        nb = nb + 1;
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

    int pop(int *tab, int &size, int &nb)
    {
        if (is_empty())
        {
            std::out_of_range(std::string("Nothing to pop"));
        }
        nb = nb - 1;
        return tab[nb];
    }

    // le ~NomClass indique une fonction qui sera appelé quand le l'objet de cette classe arrivera en fin de vie

    ~Stack()
    {
        delete[] tab;
    }
};

int main()
{
    { // Le stack est seulement défini dans ce bloc, sa fin de vie est la dernière accolade
        Stack stack(5);
        stack.push(1);
        stack.print();
        std::cout << &stack << std::endl;
    }
    return 0;
}