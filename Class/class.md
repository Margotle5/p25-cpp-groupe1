definition de class:

struct nom {
    int donnee1=0;
    int donnee2=0;
    ...
};

les ; à la fin son nécessaire

Le constructeur:
méthode qui agit que sur les objets des type de la nouvelle class

struct rational // définition d'une nouvelle classe
{
    int num = 0;
    int denom = 1;
    rational (int n, int d) {
        
    }
};

struct Intstack {
    int size;
    int nb;
    int* tab;
    
};

int main()
{
    rational r(1,2);
    std::cout <<r.num << "/" << r.denom<<std::endl;
    return 0;

}