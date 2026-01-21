/*

implement a hierarchy of classes for arithmetic expression manipulations:
    - the classes holds, evaluates and prints arithmetic expressions
    - print in infix, prefix or postfix notation

Additional work:
   - note that the postfix notation is also called Reverse Polish notation (RPN)
   - it is a mathematical notation in which operators follow their operands
   - this notation does not need any parentheses i.e. this notation is non ambigu
   - => you can read (easily) RPN expressions using a stacks
  implement a code to read RPN expression and store them with your class objects
  RPN arithmetic expression are passed as main command-line arguments

./main 87 12 - + 75 -
*/
#include <iostream>
#include <exception>
#include <vector>

class arithmetic_expr {
public:
    virtual void print() const = 0;
    virtual int eval() const = 0;
};


class Constant: public arithmetic_expr
{
public:
    uint value;

    Constant(uint val) : arithmetic_expr(), value(val) { };

    void print() const {
        std::cout << value ;
    }

    int eval() const {
        return value;
    }
};

class UnaryMinus: public arithmetic_expr
{
protected:
    arithmetic_expr& expr;
public:
    UnaryMinus(arithmetic_expr& val) : arithmetic_expr(), expr(val) {};

    void print()const {
        expr.print();
        std::cout<< " -";
    }

    int eval() const {
        return (- expr.eval());
    }
};

class Plus: public arithmetic_expr
{
public: 
    arithmetic_expr& val1;
    arithmetic_expr& val2;

    Plus(arithmetic_expr& v1, arithmetic_expr& v2): val1(v1), val2(v2) {};

    void print() const {
        val1.print();
        std::cout<<" ";
        val2.print();
        std::cout<< "+";
    }

    int eval() const{
        return (val1.eval() + val2.eval());
    }
};

class Minus: public arithmetic_expr {
public:
    arithmetic_expr& val1;
    arithmetic_expr& val2;

    Minus(arithmetic_expr& v1, arithmetic_expr& v2): val1(v1), val2(v2) {};

    void print() const {
        val1.print();
        std::cout << " ";
        val2.print();
        std::cout<<"-";
    }

    int eval() const {
        return (val1.eval() - val2.eval());
    }
};

class Divide: public arithmetic_expr {
public:
    arithmetic_expr& val1;
    arithmetic_expr& val2;

    Divide(arithmetic_expr& v1, arithmetic_expr& v2): val1(v1), val2(v2) {};

    void print() const {
        val1.print();
        std::cout << " ";
        val2.print();
        std::cout<<"/";
    }

    int eval() const {
        if (val2.eval()==0) {
            throw std::runtime_error("Probleme");
            return -1;
        } else {
        return (val1.eval()/val2.eval());
        }
    }
};

int main()
{
    try
    {
        // Constant c1(12), c2(-87), c3(23); // try it (-87 is not an unsigned int)
        Constant c1(12), c2(87), c3(75);

        c1.print(); // affiche 12
        std::cout << std::endl;
        std::cout << "eval " << c1.eval() << std::endl; // affiche 12

        UnaryMinus u1(c1);
        u1.print(); // affiche 12 -
        std::cout << std::endl;
        std::cout << "eval " << u1.eval() << std::endl; // affiche -12

        Plus p1(c2, u1);
        p1.print(); // affiche 87 12 -+
        std::cout << std::endl;
        std::cout << "eval " << p1.eval() << std::endl; // affiche 75

        Minus m1(p1, c3);
        m1.print(); // 87 12 -+75 -
        std::cout << std::endl;
        std::cout << "eval " << m1.eval() << std::endl; // affiche 0

        Divide d1(p1, m1);
        std::cout << std::endl;
        //std::cout << d1.eval() << std::endl; // throws an instance of 'std::runtime_error'

        std::vector <arithmetic_expr*> expr;
        expr.push_back(&c1);
        expr.push_back(&u1);
        for (int i=0; i<expr.size(); i++ ) {
            std::cout << "element " << i <<" of the vector: ";
            expr[i]->print();
            std::cout<<std::endl;
        }
        // parcourez le vecteur*/
    }
    catch (std::runtime_error &e)
    {
        // affiche zero divide error
        std::cout << e.what() << std::endl;
    } 
    return 0;
}
