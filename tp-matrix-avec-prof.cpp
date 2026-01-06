#include <iostream>
#include <stdexcept>

// Cours du mardi 6 janvier 2026.
// 1) on corrige le TP sur le Buffer partagé
// 2) on introduit le constructeur de copie
// 3) on introduit l'affectation
// 4) définition des méthodes en dehors de la classe
//    + inline
// 5) operator<< et const member functions

// ce code est inspiré du code de Margot Lecinq

// Un tableau qui peut être partagé entre plusieurs objets.
class Buffer
{
    friend class Matrix;
    // La classe Matrix pourra accéder aux attributs et aux méthodes private (et protected) de la classe Buffer.
    // Une classe choisit ses amis.

private:
    // version avec allocation d'un tableau avec new
    int size;
    double *tab;

    // Le nombre d'objet partageant cet objet Buffer.
    int counter;

public:
    // On met par défaut la valeur initiale à 0.
    Buffer(int size, int init = 0)
        : counter(0), size(size)
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

    // Test de la validité de l'index.
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

    // On ajoute des accesseurs/modifiers pour les élément du tableau.
    void set(int i, int value)
    {
        if (valid_index(i))
            tab[i] = value;
        // else => on doit lancer une exception (à compléter)
    }

    int get(int i)
    {
        if (valid_index(i))
            return tab[i];
        // else => on doit lancer une exception (à compléter)
    }

    // On ajoute les fonctions pour gérer le compteur.
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
        delete[] tab; // attention à ne pas oublier le []
                      // (tab a été créé par un new [])
    }
};

// Objet Matrice avec tableau sous-jacent partagé lors de l'opération de reshape.
class Matrix
{
    // Le tableau sous-jacent
    Buffer *buffer_ptr;

    // l'indexation
    int rows;
    int columns;

    // fonction pour passer d'une indexation dans un tableau à 2 dimensions (i, j)
    //                      à une indexation dans un tableau à 1 dimension  (i)
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
    // Valeur initiale des éléments est 0 par défaut
    Matrix(int r, int c, int init = 0)
        : rows(r), columns(c)
    {
        std::cout << "Matrix::Matrix(int, int)\n";
        // On alloue dans le tas (heap, mémoire dynamique) l'objet Buffer
        // qui sera potentiellement partagé par plusieurs objets.
        // Il doit exister si l'objet courant est détruit,
        // la seule manière de faire est d'allouer l'objet Buffer dans le tas (heap allocated)
        // on ne le détruira que quand plus aucun objet Matrix n'existe
        buffer_ptr = new Buffer(rows * columns, init);

        // On incrémente le compteur du nombre d'objets Matrix qui référencent cet objet.
        // buffer_ptr->counter = buffer_ptr->counter + 1; soit directement quand Buffer a déclaré Matrix en friend
        buffer_ptr->incr_counter(); // soit par l'appel d'une méthode de l'objet Buffer
    }

private:
    // Cette méthode permet de partager le buffer sous-jacent entre plusieurs objets Matrix.
    // Elle sera appelée par Matrix::reshape
    Matrix(int r, int c, Buffer *buffer_ptr)
        : rows(r),
          columns(c),
          buffer_ptr(buffer_ptr)
    {
        buffer_ptr->incr_counter();
    }


public:
    Matrix(const Matrix& M): rows(M.rows), columns(M.columns), buffer_ptr(M.buffer_ptr) //Pourquoi il faut des références -> car on nous fournit une référence et non une adresse mémoire
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
    // On enlève l'objet Matrix courant du décompte:
    // 2 cas:
    //   - c'est le dernier objet qui utilise le Buffer
    //   - ou non
    void decr_buffer()
    {
        // on décrémente le compteur
        buffer_ptr->decr_counter();

        // si le counter est à 0
        // c'est que plus aucun objet Matrix ne partage ce Buffer
        // => on détruit le Buffer
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

int main()
{
    // Matrix m1 = Matrix(4, 3);
    // faire plus simplement:
    Matrix m1(4, 3);
    m1.set(0, 0, 17.2);
    // m1.set(0, 3, 21.3);
    m1.print();
    {
        Matrix m2 = m1.reshape(2, 6);
        m2.set(1, 1, 2025);
        m2.print();
        m1.print();
    }
    Matrix m3 = m1.reshape(6, 2);
    m3.set(0, 0, 2026);

    // enlever le commentaire pour ajouter un code faux...
    Matrix m4(2, 4);
    Matrix m5(m4);
    // Comprenez-vous ce qui se passe ?

    // enlever le commentaire pour ajouter un code faux...
    Matrix m6(4, 6);
    m6.print();
    Matrix m7(2, 3);
    m6 = m7; //c++ va enfait faire m6.operator=(m7); il faut donc redéfinir operator=
    // Comprenez-vous ce qui se passe ?
    m6.print();
    return 0;
}
