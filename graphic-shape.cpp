/* implement graphic shapes and an editor

the graphic shapes:
   - are Circle (radius), Rectangle (width, height) ...
   - have a position: x, y
   - can be moved
   - have member function that check if a shape is at a given position
     (juste check that the given point is inside the smallest rectangular bounding box englobing the shape)
   - have a member function that compute the area of the shape (fix a value for PI)

the editor:
  - contains a list of graphic shapes
  - can add/remove an existing graphic-shape to the list
  - has a member function find that returns the (first) graphic shape at a given position
  - can remove the graphic-shape found at a given position
  - can compute the area of the shape found at a given position

We can add a new shape to your code (Square) WITHOUT modifying your classes !
Only by adding some code and modifying the main function.

*/
#include <iostream>
#include <vector>

class Shape // une fois qu'on a mis un virtual ... = 0, l'objet shape devient "abstrait" on ne fabriquer une shape mais que des cercles et des rectangles
{
    int x;
    int y;

protected: // classe qui hérite de Shape on accès au truc protected
    Shape(int x, int y) : x(x), y(y) {};

public:
    void move(int i, int j)
    {
        x = i;
        y = j;
    };
    // double area(){ return -99;}; //ligne stupide mais obligatoire pour qu'il compile
    virtual double area() = 0; // virtual va faire que le code stock le type des différentes shape, si on appel area sur un cercle, il va appeler area du cercle
                               // = 0 signifie que shape est une classe abstraite
    bool is_at(int i,int j);
};

class Circle : public Shape // pour tout objet Circle créer, un objet shape associé est créer
{
private:
    int rayon;

public:
    Circle(int x, int y, int r) : Shape(x, y), rayon(r) {};
    double area()
    {
        return 3.14159 * rayon * rayon;
    }
};

class Rectangle : public Shape
{
private:
    int width;
    int height;

public:
    Rectangle(int x, int y, int w, int h) : Shape(x, y), width(w), height(h) {};
    double area()
    {
        return width*height;
    }
};

int main()
{
    Circle c1(100, 50, 12.4);
    c1.move(15, 67);
    std::cout<<c1.area()<<std::endl;
    Rectangle r1(56,67,100,300);
    std::cout<<r1.area()<<std::endl;

    std::vector <Shape*> shapes;
    shapes.push_back(&c1);
    shapes.push_back(&r1);

    for (int i=0; i<shapes.size(); i++) {
        shapes[i]->move(2,3); //il appel la fonction move dans shape
        std::cout << shapes[i]->area() << std::endl;//problème, area n'est pas définie pour un objet de type shape
                                                    // après avoir modifié area, cette ligne renvoie -99
                                                    //on n'est pas trop content
    };                      

//Attention:
/* Shape* ps1= &c1; on crée un pointeur vers la partie shape de c1
   Shape& rs1= c1; crée une référence vers la partie shape de c1
   Shape s1 = c1; crée une copie de la partie shape de c1
   ps1->move(2,3); déplace le cercle c1 à la position (2,3)
*/

/*
    Circle c2(30, 120, 45.89);

    Rectangle r1(30, 40, 60, 50);
    std::cout<< r1.area() << std::endl;

    Rectangle r2(70, 80, 100, 67);

    Editor ed;
    ed.add(c1);
    ed.add(c2);
    ed.add(r1);
    ed.add(r2);

    ed.find(71, 81).area();
    ed.find(30, 120).move(10, 80);*/

    return 0;
}