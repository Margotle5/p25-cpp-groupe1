#include <iostream>
#include <limits>

int main (int argc, char* argv []) {
    
    int i=0;
    for (int i=0; i<argc; i++){
        std::cout <<argv[i] << std::endl;
    }

    return 0;
}

