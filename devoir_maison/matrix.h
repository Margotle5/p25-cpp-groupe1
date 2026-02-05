//On reprend les classes matrix créée précédement
#pragma once 
#include <iostream>
#include <stdexcept>

class Buffer
{
    friend class Matrix;

private:
    int size;
    double *tab;

    // Le nombre d'objet partageant cet objet Buffer.
    int counter;

public:
    Buffer(int size, int init = 0)
        : size(size), counter(0)
    {
        tab = new double[size];

        // On initialise les éléments de la Matrice à leur valeur initiale.
        reset(init);
    }

    // Initialise tous les éléments à la même valeur.
    void reset(int value)
    {
        for (int i = 0; i < size; i++)
        {
            tab[i] = value;
        }
    }

    bool valid_index(int i)
    {
        return (i >= 0) and (i < size);
    }

    void print()
    {
        std::cout << "[";
        for (int i = 0; i < size; i++)
        {
            std::cout << tab[i] << " ";
        }
        std::cout << "]" << std::endl;
    }


    void set(int i, int value)
    {
        if (valid_index(i))
            tab[i] = value;

    }

    int get(int i)
    {
        if (valid_index(i))
            return tab[i];

    }

    void incr_counter()
    {
        counter = counter + 1;
    }

    void decr_counter()
    {
        counter = counter - 1;

    }

    int get_counter()
    {
        return counter;
    }

    ~Buffer()
    {
        delete[] tab; 
    }
};


class Matrix
{
    int rows = 0;
    int columns = 0;
    Buffer *buffer_ptr = nullptr;

    int flatten_indices(int i, int j)
    {
        return i * columns + j;
    }

    // Test de la validité des deux indices
    bool valid_indices(int i, int j)
    {
        return ((i >= 0) and (i < rows) and (j >= 0) and (j < columns));
    }

public:
    Matrix(int r, int c, int init = 0)
        : rows(r), columns(c)
    {
        std::cout << "Matrix::Matrix(int, int)\n";
        buffer_ptr = new Buffer(rows * columns, init);

        buffer_ptr->incr_counter();
    }

private:
    Matrix(int r, int c, Buffer *buffer_ptr)
        : rows(r),
          columns(c),
          buffer_ptr(buffer_ptr)
    {
        buffer_ptr->incr_counter();
    }


public:
    //Matrix() = default;

    Matrix(const Matrix& M): rows(M.rows), columns(M.columns), buffer_ptr(M.buffer_ptr) 
    {
        buffer_ptr->incr_counter();
    }

    Matrix& operator=(const Matrix& M){
        if (this!= &M) {
        decr_buffer();
        rows=M.rows;
        columns=M.columns;
        buffer_ptr=M.buffer_ptr;

        M.buffer_ptr->incr_counter();
        }
        return *this;
    }

    void print()
    {
        // Pout debugger j'affiche le compteur de Matrix
        std::cout << "[" << buffer_ptr->get_counter() << "]" << std::endl;
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
        std::cout << std::endl;
    }

    void set(int i, int j, double elem)
    {
        if (not valid_indices(i, j))
        {
            // on doit lancer une exception (à compléter) là on affiche un message et on quitte la fonction
            std::cerr << "Matrix::set wrong indices (" << i << ", " << j << ")\n";
        }
        else
        {
            buffer_ptr->set(flatten_indices(i, j), elem);
        }
    }

    int get(int i, int j)
    {
        if (not valid_indices(i, j))
        {
            // on doit lancer une exception (à compléter) là on affiche un message (et on ne sait pas quoi retourner...)
            std::cerr << "Matrix::get wrong indices (" << i << ", " << j << ")\n";
        }
        else
        {
            return buffer_ptr->get(flatten_indices(i, j));
        }
    }

    Matrix reshape(int i, int j)
    {
        if (i * j != rows * columns)
        {
            throw std::invalid_argument("Reshape incompatible with size");
        }
        return Matrix(i, j, buffer_ptr);
    }

private:

    void decr_buffer()
    {
        buffer_ptr->decr_counter();
        if (buffer_ptr->counter == 0)
        {
            delete buffer_ptr;
        }
    }

public:
    ~Matrix()
    {
        decr_buffer();
    }
};

