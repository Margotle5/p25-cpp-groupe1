#include <iostream>
#pragma once //si le fichier est included plusieurs fois, le ficher ne sera inclue qu'une seule fois

struct Int {
    int value=0;
    void incr(); //déclaration d'une fonction à définir après
    void decr() {value-=1;};
    int get() {return value;}; //si on met int& on donne accès à une certaine partie de notre mémoire à main_int.cpp
    void print() {
        std::cout << value << std::endl;
    }

};

inline void Int::incr(){ value ++;}

