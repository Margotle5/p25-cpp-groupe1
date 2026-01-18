#include "integer.h"
//On veut que ce code reste cacher donc on ne veut pas "l'include dans main_int.cpp"
//on ne peut pas créer un exécutable de ce ficher car il n'y a pas de main pour l'exécuter on fait la commande:
//g++ -c foo.cpp
void foo(Int &pi) {
    pi.incr();
};