#include <iostream>
// à gauche d'un = ->zone mémoire (left value) chose qui peut être affecté
// à droite du = c'est les choses qu'on met dans la mémoire (right value)

int add(int a, int b)
{
    return a + b;
}

void swap(int* a, int* b) {
    int a_val = *a;
    int b_val = *b;
    *a=b_val;
    *b=a_val;

}

int main()
{
    int i = 5;                      // i -> acces à la valeur, &i -> acces à l'adresse de la case mémoire
    int j = i * 100;                // l'ordinateur prend la valeur de i
    i = 17;                         // modifie la valeur dans la case mémoire de i
    int *pi = &i;                   // le type d'une adresse mémoire d'un int est int* (ou char* pour un char)
    std::cout << &*pi << std::endl; //*adresse renvoie la valeur stocké dans l'adresse, &variable renvoie l'adresse dans la mémoire de &
    *pi = 15;                       // modifie la valuer dans la case de l'adresse pi, ie i=15

    int tab[2];
    tab[0] = 12;
    tab[1] = 1;
    // tab[2]=... fait une erreur
    int *ptab = tab; // ptab est l'adresse du première élement de tab
    // Attention: tab est aussi l'adresse de la première valeur de tab, tab + 1 c'est l'adresse de tab[1] etc
    // tab[0]= *tab
    // tab[1]= *(tab + 1)

    int k = add(i,j); 
    /*Que se passe t il dans la mémoire?
    b| 17 |
    a| 12 |  
    k|    | ordi défini k,  crée emplacement mémoire pour a,b, recopie valeur de i et j dans a et b
    j|_17_|
    i|_12_|
    */
    
    i = 12;
    j = 17;
    swap(&i,&j);
    std::cout << std::boolalpha << ((i==17) && (j==12))<<std::endl;
    return 0;
}