#include "integer.h" // on inclue le code de integer de dans
//Option 1:
//void foo(Int&); //permet de préciser au code le type que foo prend en argument

//Option 2:
#include "foo.h"

int main() {
    Int i;
    foo(i);
    i.incr();
    i.print();
//    i.get()=17; //si int& dans définition de i.get transforme la fonction en une "right value", quelque chose qu'on peut affecter
    return 0;
}