#include <iostream>
struct rational // définition d'une nouvelle classe
{
    int num;
    int denom = 1;
    rational (int n, int d) :num(n) , denom(d)
    {
        //corps du construcuteur, automatiquement num= n et denom=d
    }
    void print() { //print avec des méthodes
        std::cout <<num << "/" << denom<<std::endl;
    }

};

void affichage_rational (rational r)
{
    std::cout <<r.num << "/" << r.denom<<std::endl;    
}

void affichage_rational_2 (rational* r) // affichage avec l'adresse
 { 
    std::cout <<r->num << "/" << r->denom<<std::endl; 
}

void affichage_rational_3 (rational& r) // affichage avec la référence, meilleur méthode
{ 
    std::cout <<r.num << "/" << r.denom<<std::endl; 
}
struct Intstack {
    int size;
    int nb;
    int* tab;
    
};

int main()
{
    rational r(1,2);
    affichage_rational(r); // Pas bien car l'ordi copie valeur par valeur r, si r composé de trop d'objet, ça prend trop de temps
    affichage_rational_2(&r); 
    affichage_rational_3(r); 
    r.print(); //utilise des méthodes
    r.num=3;
    r.print();
    return 0;

}