#include <iostream>
#include <stdexcept>

void print(int* tab, int& size, int& nb) {
    std::cout <<"[ ";
    for (int i=nb-1; i>=0; i--) {
        std::cout << tab[i] << " ";
    }
    std::cout <<"["<<std::endl;
}

bool is_empty(int& nb) {
    if (nb==0) {
        return true;
    }
    return false;
}

bool is_full(int& nb, int& size) {
    if (nb<size) {
        return false;
    }
    return true;
}

void push(int* tab,int& size,int& nb,int val) {
    if (nb>=size){
        throw std::length_error(std::string("Erreur: tab doesn't have enough space to add value"));
    }
    tab[nb]=val;
    nb=nb+1;
}

int top(int* tab, int& size, int& nb){
    if (nb==0){
        throw std::out_of_range(std::string("Erreur: rien dans le tableau"));
        return -1;
    }
    return tab[nb-1];
}

int pop(int* tab,int& size,int& nb){
    if (nb==0){
        std::out_of_range(std::string("Nothing to pop"));
        return -1;
    } else {
        nb=nb-1;
        return tab[nb];
    }
}
int main(){

    // on définit les 3 variables constituant la pile
    int size = 5;
    int stack[size];
    int nb = 0;

    int& nb_r=nb;

    // rajoutez aux blocks catch les erreurs
    // pouvant être déclenchées par les opérations sur la pile
    try
    {
        print(stack, size, nb_r); // affiche [ [
        push(stack, size, nb_r, -17);

        // on affiche l'élément en haut de pile
        std::cout << top(stack, size, nb_r) << std::endl; // affiche -17

        print(stack, size, nb_r); // affiche [-17 90 [

        int e = pop(stack, size, nb_r);
        std::cout << e << std::endl;
        print(stack, size, nb_r); // affiche [-17 [

        push(stack, size, nb_r, 20);
        push(stack, size, nb_r, -78);
        push(stack, size, nb_r, -9);
        push(stack, size, nb_r, -56);
        push(stack, size, nb_r, -9);
        push(stack, size, nb_r, 68);
    }
    catch (std::length_error)
    {
        std::cerr <<"Le tableau est plein: ";
        print(stack, size, nb_r);
    }
    catch (std::out_of_range){
        std::cerr <<"Le tableau est vide:";
        print(stack, size, nb_r);
    }
    return 0;
}