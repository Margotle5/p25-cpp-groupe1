#include <iostream>

void swap(int& a, int& b) // modifier les réferences dans fonctions modifira directement la valeur dans la mémoire
{
    int aux= a;
    a=b;
    b=aux; 
}

int main()
{
    int i = 12;
    int* pi= &i;
    *pi=*pi*10;

    int& ri = i; //référence, comme un pointeur qui automatiquement va dans la case mémoire de i
    ri = ri*10;

    std::cout << ri << " " <<i<< std::endl;
    return 0;


}