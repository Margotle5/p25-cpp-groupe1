#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>

class Buffer
{
    friend class Matrix;

    double *tab;
    int nb_matrix;
    int size;
    
public:
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
        std::cout << std::endl;
    }

    ~Buffer()
    {
        delete tab;
    }
};

class Matrix
{
    friend class Buffer;
    Buffer *buffer_ptr;
    int rows;
    int columns;

public:
    Matrix(int r, int c) : rows(r), columns(c)
    {
        buffer_ptr = new Buffer(rows * columns);
        buffer_ptr->nb_matrix = buffer_ptr->nb_matrix + 1;
    }

    Matrix(int r, int c, Buffer *buffer_ptr) : rows(r), columns(c), buffer_ptr(buffer_ptr)
    {
        buffer_ptr->nb_matrix = buffer_ptr->nb_matrix + 1;
    }

    void print()
    {
        int n = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                std::cout << buffer_ptr->tab[n] << " ";
                n = n + 1;
            }
            std::cout << std::endl;
        }
    }

    void set(int i, int j, double elem)
    {
        buffer_ptr->tab[i + j] = elem;
    }

    int get(int i, int j)
    {
        std::cout << buffer_ptr->tab[i + j] << std::endl; // pour debuger
        return buffer_ptr->tab[i + j];
    }

    Matrix reshape(int i, int j)
    {
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
    m.set(0, 3, 21.3);
    m.print();
    return 0;
}