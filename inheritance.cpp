//Supposons qu'on veuille faire des formes géométriques
//On veut faire un code qui gère les objets graphiques

//On veut pouvoir déplacer les coordonnées des formes géométrique + calculer leur surface
//On veut ranger l'adresse dans des vecteurs

#include <vector> // création de vecteur std::vector<int> vi;
                  // vi.push_back(12) rajoute 12 au tableau;
                  //vecteur ne peuvent contenir des élement du même type, dans notre cas, il ne pourrait pas contenir des adresses de Circle et des Rectangle
                  //On va donc définir une class Shape qui englobe les classes Circle et Rectangle
class Circle_1 {
    int rayon;
    int x; //coordonnée du centre
    int y;
};

class Rectangle_1 {
    int width;
    int height;
    int x; // coordonnée du point en haut à gauche
    int y;
};

int main(){
    Circle_1 c1(30,20,10);
    Rectangle_1 r1 (40, 40, 10,25);
    return 0;
};