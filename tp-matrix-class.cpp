#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>

class Buffer
{
    friend class Matrix; // Les classes amis peuvent accéder à tous le contenu de Buffer
private:
    int size;
    double *tab;
    int nb_matrix; // nombre de Matrix relier au Buffer

public:
    // Création du tableau dans la mémoire dynamique
    Buffer(int size) : nb_matrix(0), size(size)
    {
        tab = new double[size];
    }

    void print()
    { // pour debuger
        std::cout << "[";
        for (int i = 0; i < size; i++)
        {
            std::cout << tab[i];
        }
        std::cout << ']' << std::endl;
    }

    bool valid_index(int i)
    {
        return (i >= 0) and (i < size);
    }

    void set(int i, double value) // modifier la valeur d'un élément particulier
    {
        if (valid_index(i))
            tab[i] = value;
    }

    double get(int i) // récupérer la valeur d'un élément particulier
    {
        if (valid_index(i))
            return tab[i];
    }

    void incr_nb_matrix()
    {
        nb_matrix = nb_matrix + 1;
    }

    ~Buffer()
    {
        delete tab;
    }
};

class Matrix
{
    Buffer *buffer_ptr;
    int rows;
    int columns;

public:
    int flatten_indices(int i, int j) {
        return i*columns + j;
    }

    bool valid_indices(int i, int j) {
        return ((i>=0) and (i<rows) and (j>=0) and (j<columns));
    }

    Matrix(int r, int c) : rows(r), columns(c)
    {
        buffer_ptr = new Buffer(rows * columns);
        buffer_ptr->nb_matrix = buffer_ptr->nb_matrix + 1;
    }

    Matrix(int r, int c, Buffer *buffer_ptr) : rows(r), columns(c), buffer_ptr(buffer_ptr)
    {
        buffer_ptr->nb_matrix = buffer_ptr->nb_matrix + 1; // ou buffer->incr_nb_matrix()
    }

    void print()
    {
        int n = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                std::cout << buffer_ptr->get(flatten_indices(i,j)) << " ";
                n = n + 1;
            }
            std::cout << std::endl;
        }
    }

    void set(int i, int j, double elem)
    {
        buffer_ptr->set(flatten_indices(i,j), elem);
    }

    double get(int i, int j)
    {
        std::cout << buffer_ptr->get(flatten_indices(i, j)) << std::endl; // pour debuger
        return buffer_ptr->get(flatten_indices(i, j));
    }

    Matrix reshape(int i, int j)
    {
        if (i*j != rows*columns) {
            throw std::invalid_argument("Reshape incompatible");
        }
        Matrix m = Matrix(i, j, buffer_ptr);
        return m;
    }

    ~Matrix()
    {
        if (buffer_ptr->nb_matrix == 1)
        {
            delete buffer_ptr;
        }
    }
};

int main()
{
    Matrix m = Matrix(4, 3);
    m.set(0, 0, 17.2);
    m.set(0, 1, 21.3);
    m.print();
    return 0;
    Matrix m2(2,4);
    Matrix m3(m2); // Que se passe-t-il? même chose que Matrix m3= m2; mais le problème est que incr_nb_matrix ne sera pas appelé
}