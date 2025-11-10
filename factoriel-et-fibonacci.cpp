#include <iostream>
#include <cstdlib>
#include <cstring>

int factorial(int n)
{
    int resultat = 1;
    if (n <= 0)
    {
        return resultat;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            resultat = resultat * i;
        }
        return resultat;
    }
}

/*Avec des templates*/
template <typename T>
T factorial(T n)
{
    if (n<=1){
        return 1;
    }
    return n*factorial(n-1);
}

int fibonacci(int n)
{
    int u_n = 0;
    int u_np1 = 1;
    int u = 0;

    if (n <= 1)
    {
        return n;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            u = u_np1;
            u_np1 = u_np1 + u_n;
            u_n = u;
        }
        return u_np1;
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        std::cout << "Tapper fibo ou fact suivit d'un nombre pour avoir fibo(n) ou fact(n)" << std::endl;
        return 0;
    }

    if (!strcmp(argv[1], "fibo"))
    {
        std::cout << fibonacci(std::atoi(argv[2])) << std::endl;
        return 0;
    }
    else if (!strcmp(argv[1], "fact"))
    {
        std::cout << factorial(std::atoi(argv[2])) << std::endl;
        return 0;
    }
    std::cout << "Tapper fibo ou fact suivit d'un nombre pour avoir fibo(n) ou fact(n)" << std::endl;
    return 0;
}