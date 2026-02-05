// Un dernier projet sur les graphes.
// Vous devez représenter un graphe sous la forme de liste d'adjacence, constitué de sommets nommés
// et d'arêtes portant une valeur numérique (double) entre ces sommets.

// Dans un graphe sous la forme de liste d'adjacence:
//    - le graphe possède le vecteur de ses sommets;
//    - chaque sommet possède le vecteurs des arêtes dont il est le sommet de départ.

// Vous devez coder les class Vertex, Edge et Graph, avec les consignes suivantes:
//    0) ne mettez pas d'attributs en public
//       ne mettez pas de méthodes pour accéder aux attributs
//       mais utilisez friend au besoin

//    1) les sommets sont identifiés par leurs noms qui sont des std::string

//    2) vous devez utiliser des std::vector pour les listes de sommets et d'arêtes
//       a) Vous devez donc conserver une correspondance entre le nom d'un sommet et son indice dans le graphe
//          pour cela le graphe possède une std::unordered_map<std::string, int> comme montré ci-dessous

//    3) vous utilisez new et delete pour les Vertex et Edge dans le graphe.

//    4) vous devez proposer une méthode de la classe Graph qui lise un graphe écrit dans un fichier
//       comme exemple, regardez la fonction read_graph ci-dessous

//    5) vous devez implémenter un parcours de ce graphe en profondeur (déjà fait en cours)
//       pour stocker les sommets déjà visités utilisez un std::set

//    6) vos devez implémenter une méthode de Graph qui construit la matrice d'adjacence du graphe
//       vous stockez cette matrice comme attribut du graphe
//       utilisez votre class Matrix ou codez-en une

//    7) appliquez à cette matrice d'adjacence l'Algorithme de Floyd-Warshall
//  https://fr.wikipedia.org/wiki/AlgorithmedeFloyd-Warshall
// qui calcule les plus courts chemins entre tous les sommets d'un graphe

//   8) IA générative:
//    a) N'utilisez pas d'IA générative pour générer votre code sauf pour des choses
//       très ciblées/spécifique mais pas pour générer tout un code !
//    b) quand vous faites générer une partie très spécifique de code, vous devez:
//       i) indiquer que c'est de l'IA
//       ii) relire, debugger, tester et donc comprendre exactement tout le code
//       iii) ne pas laisser de construction c++ que vous ne maîtrisez pas

//   9) une fois le programme complètement codé,
//      i) utilisez une IA générative pour générer un code avec les mêmes contraintes que le vôtre
//         mettez ce code dans un fichier du même nom que celui du projet avec "_IA" avant le .cpp ou le .h
//      ii) relisez-le et notez dans le fichier les endroit que vous ne comprenez pas
//          ou qui sont très différents de ce que vous avez utilisé en cours
//      iii) demandez à l'IA de vous expliquer ces endroits et mettez l'explication dans votre fichier
//      Mettez dans votre repo ce ou ces fichiers aussi (avec donc _IA avant le '.' du suffixe '***_IA.cpp" ou "***_IA.h")

// Cette fonction read_triplet lit une suite de triplets:
//           from_1 to_1 value_1 from_2 to_2 value_2 ... from_n to_n value_n
//    où les value_i sont des doubles e.g. 3.14159
//    où from_i et to_i sont des mots SANS espace e.g. Le_Havre mais pas Le Havre ou "Le Havre"
// voir fichier graph0.gr
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <stack> //J'ajoute les stack pour coder le dfs
#include "matrix.h"
#include "graphe.h"


using namespace std; // pour éviter d'écrire les std::


int main()
{
    Graph g;

    g.print();
    g.add_edge("Paris", "Londres", 1.2);
    g.print();


    // LECTURE DU GRAPHE
    Graph graph;
    graph.read_triplet("graph0.gr");
    Matrix* mat_adj= graph.matrix();
    Matrix* mat_dist = graph.floyd_warshall();
    mat_adj->print();
    mat_dist->print();
    graph.print();
    //graph.dfs();

    /*    // EXEMPLE D'UTILISATION D'UN DICTIONNAIRE STD::UNORDERED_MAP
        // voici un exemple d'utilisation d'un dictionnaire pour stocker:
        //    - comme clé les noms des sommets
        //    - comme valeur son indice dans le vector
        std::unordered_map<std::string, int> srt_to_indice;
        int i = 0;
        // "Paris" "Nice" 350.50
        srt_to_indice["Paris"] = i;
        i = i + 1;

        srt_to_indice["Nice"] = i;
        i = i + 1;

        // ou utilisez auto pour l'inférence de type (le type est généré)
        std::unordered_map<std::string, int>::iterator search_paris = srt_to_indice.find("Paris");
        if (search_paris != srt_to_indice.end())
            std::cout << "found Paris\n"
                      << search_paris->first << ' ' << search_paris->second << '\n';
        else
            std::cout << "Paris not found\n";

        auto search = srt_to_indice.find("Antibes");
        if (search != srt_to_indice.end())
            std::cout << "Antibes found\n"
                      << search->first << ' ' << search->second << '\n';
        else
            std::cout << "Antibes not found\n";

        // On accède à un l'indice d'un sommet
        std::cout << srt_to_indice["Paris"] << std::endl;

        // accès aux éléments du dictionnaire
        for (auto &e : srt_to_indice) // & pour éviter de recopier l'objet
        {
            std::cout << "key: " << e.first
                      << " value: " << e.second << std::endl;
        }

        // 2) accès par std::get<0> et std::get<1>
        // à préférer à first et second
        for (auto &e : srt_to_indice)
        {
            std::cout << "key: " << std::get<0>(e)
                      << " value: " << std::get<1>(e) << std::endl;
        }

        // EXEMPLE D'UTILISATION D'UN STD::SET
        std::set<int> visited;
        visited.insert(2);

        std::set<int>::iterator search_0 = visited.find(0);
        if (search_0 != visited.end())
            std::cout << "Found 0\n";
        else
            std::cout << "0 not found\n";

        std::set<int>::iterator search_2 = visited.find(2);
        if (search_2 != visited.end())
            std::cout << "found 2\n";
        else
            std::cout << "2 not found\n"; */

    return 0;
}

/*

mettre dans le fichier graph0.gr par exemple
Paris Lyon 100.56 Paris Nice 200.50 Paris Marseille 140.20 Paris Toulouse 200.8
Paris Le_Havre 120 Lyon Nice 80.50 Lyon Marseille 50
Marseille Nice 70 Marseille Toulouse 80 Toulouse Nice 100

*/