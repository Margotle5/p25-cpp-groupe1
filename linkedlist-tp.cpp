
// Nous voulons implémenter un type de donné qui a la structure de liste chaînée
// et qui stocke, par exemple, des entiers.

// Une liste est composée de cellules reliées entre elles.

// Dans une liste simplement chaînée:
//   - chaque cellule pointe vers sa cellule suivante
//   - la dernière cellule n'a pas de cellule suivante

// Par exemple, la liste chaînée suivante contient les entiers 42, 12 et 45.
// 42 -> 12 -> 45 -> null

// Une cellule contient donc deux choses: une valeur et un pointeur vers sa cellule suivante
//   qui est l'adresse mémoire de la cellule suivante.

// Une liste pointe vers sa première cellule (la tête de liste) ou vers null si la liste est vide.

// Donc vous avez besoin de deux structures...

// La liste est une structure de données qui a beaucoup de défauts
// mais qui est un cas d'école sympa à implémenter en c++ et sans IA générative bien sûr -

// Il existe d'autres types de listes chaînées.
// La liste doublement chaînées où:
//    - chaque cellule pointe vers sa cellule précédente et vers sa cellule suivante
//    - la première (resp. dernière) cellule n'a pas de cellule précédente (resp. suivante)

// La liste circulaire où:
//    - chaque cellule pointe vers sa cellule suivante
//    - la dernière cellule pointe vers la première cellule

// Ces deux dernières listes sont plus complexes à implémenter, implémentez une liste simplement chaînée
// avec les opérations de base:
//   - ajouter un élément en tête de liste  (push_front - une opération en temps constant O(1))
//   - chercher un élément dans la liste    (find -       une opération en temps linéaire O(n))
//   - supprimer un élément dans la liste   (remove -     une opération en temps linéaire O(n))
//   - afficher la liste                    (print -      une opération en temps linéaire O(n))
//   - vérifier si la liste est vide        (is_empty -   une opération en temps constant O(1))
// Non, nous ne voulons pas ajouter un élément en fin de liste:
//   - parce que nous ne voulons pas faire une opération d'ajout qui soit en temps linéaire O(n) - horrible !
// Et si on voulait une liste où on peut ajouter en tête et en fin de liste ?
//    On ferait une liste doublement chaînée avec un pointeur vers la première cellule et un vers la dernière cellule.

// Surtout dessinez la structure sur papier avant de coder
// et dessinez pas à pas des exemples d'ajout, de recherche, de suppression

// Oui il y aura un new (quelque part) et vous n'oublierez pas de libérer la mémoire
// (i.e. libérer les cellules quand elles ne sont plus utilisées)

// Voici un exemple de main qui doit fonctionner avec votre liste chaînée:

#include <iostream>

struct Cell
{
    Cell *pointer;
    int value;

    Cell(int value, Cell *pointer) : value(value), pointer(pointer) {

                                     };
};

struct LinkedList
{
    Cell *ptr = nullptr;
    int size = 0;

    bool is_empty()
    {
        if (size == 0)
        {
            return true;
        }
        return false;
    };

    void push_front(int value)
    {
        Cell *cell = new Cell(value, ptr);
        size++;
        ptr = cell;
    };

    void print()
    {
        Cell *pointeur = ptr;
        int elem;
        for (int i = 0; i < size; i++)
        {
            elem = (*pointeur).value;
            std::cout << elem << " -> ";
            pointeur = (*pointeur).pointer;
        }
        std::cout << "null" << std::endl;
    };

    bool find(int n)
    {
        Cell *pointeur = ptr;
        int elem;
        for (int i = 0; i < size; i++)
        {
            elem = (*pointeur).value;
            if (n == elem)
            {
                std::cout << "La valeur " << n << " est en position " << i << std::endl;
                return true;
            }
            pointeur = (*pointeur).pointer;
        }
        std::cout << "False" << std::endl;
        return false;
    }

    void remove(int n) {
        // rajouter condition si l'elem est en premier ou en dernier + cas ou liste vide
        if (size==0) {
            return;
        }
        if (n== (*ptr).value) {
            ptr= (*ptr).pointer;
        }

        Cell *pointeur = ptr;
        int elem = (*pointeur).value;
        for (int i = 0; i < size; i++) // cas ou liste pas vide + elem à enlever n'est ni premier ni dernier
        {
            elem = (*(*pointeur).pointer).value; // on est 'une case après le pointeur'
            if (n == elem)
            {
                Cell* p = (*(*pointeur).pointer).pointer; // on récupère la valeur du pointeur de la cell qu'on remove
                delete (*pointeur).pointer; // détruit la cell de elem
                pointeur= p;
                return;
            }
            pointeur = (*pointeur).pointer;
        }
    };

};

int main()
{
    {
        LinkedList list;
        list.print();
        list.push_front(45);
        list.push_front(12);
        list.print();
        list.find(12);
        list.find(32);
        list.remove(32);
        list.remove(12);
        // std::cout << (*list.ptr).value << (*(*list.ptr).pointer).value << std::endl;
        /*
        list.push_front(12);
        list.push_front(42);
        list.push_front(33);
        list.push_front(17);

        list.print(); // Affiche: 17 33 42 12 45
                      // oui l'ordre est inversé car on ajoute en tête de liste...

        list.remove(88); // Ne fait rien (et pas d'exception à générer)
        list.remove(17); // Attention on supprime la tête de liste !!
        list.remove(45); // Attention on supprime la queue de liste !!
        list.remove(42); // Supprime un élément du milieu de liste
        // que de cas à gérer... que de pointeurs à mettre à jour...

        list.print();
    */
    }
    return 0;
}