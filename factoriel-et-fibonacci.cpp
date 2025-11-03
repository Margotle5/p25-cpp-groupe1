#include <iostream>
#include <cstdlib>

int factorial (int n){
    int resultat=1 ;
    if (n<=0){
        return resultat;
    } else {
        for (int i = 1; i<=n; i++) {
            resultat=resultat*i;
        }
        return resultat;
    }
}

int fibonacci(int n){
    int u_n=0 ;
    int u_np1=1 ;
    int u=0 ;
    
    if (n==0 || n==1){
        return n;
    } else {
        for (int i=1; i<=n; i++) {
            u=u_np1;
            u_np1=u_np1 + u_n;
            u_n=u ;
            //std::cout <<"u_n"<<u_n <<" u_np1"<<u_np1 <<" u"<<u << std::endl;
        }
        return u_np1;
    }
}

int main(int argc, char* argv[]){
    if (std::atoi(argv[1])==1) {
        std::cout <<fibonacci(std::atoi(argv[2]))<< std::endl;   
        return 0;
    } else {
        std::cout << factorial(std::atoi(argv[2]))<< std::endl;
        return 0;
    }
}