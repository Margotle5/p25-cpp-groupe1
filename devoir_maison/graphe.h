#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <stack> //J'ajoute les stack pour coder le dfs
#include "matrix.h"


using namespace std;

class Edge;
class Vertex;
class Graph;

class Edge
{
    friend class Vertex;
    friend class Graph;

protected:
    
    int start;
    int end;
    double weight;
    Graph* graph;
    
    Edge(int start, int end, double weight, Graph* graph) : start(start), end(end), weight(weight), graph(graph) {}

    //Pour debuger
    void print();
};

class Vertex
{
    friend class Graph;
    friend class Edge;

protected:
    int name;
    vector<Edge *> edge_list;
    Graph* graph;

    Vertex(int name, Graph* graph) : name(name), graph(graph) {};

    void add_edge(int end, double weight)
    {
        edge_list.push_back(new Edge(name, end, weight, graph));
    }

    // Pour debuger
    void print()
    {
        for (Edge* edge : edge_list) {
            edge->print();
        }
    }

    string str_name(); //pour récupérer le nom d'un sommet

    ~Vertex() 
    {
        for (Edge* edge : edge_list)
        delete edge;
    }

};

class Graph
{
    friend class  Vertex;
    friend class Edge;

protected:
    vector<Vertex *> vertex_list;
    unordered_map<string, int> correlation_map;
    
public:   
    Matrix* adj_matrix=nullptr;

    // on utilise le constructeur par défaut


protected:
    bool is_in_graph(string name)
    {
        return !(correlation_map.find(name) == correlation_map.end());
    }


    void add_vertex(const string &name)
    {
        if (!is_in_graph(name)) {
            vertex_list.push_back(new Vertex(correlation_map.size(), this));
            correlation_map.insert({name, correlation_map.size()});
        }
    }

public:
    Matrix* matrix(){
        adj_matrix = new Matrix(vertex_list.size(), vertex_list.size());
        for (int i = 0; i<vertex_list.size(); i++) {
            for (Edge* edge : vertex_list[i]->edge_list) {
                adj_matrix->set(i,edge->end, 1);
            }
        }
        return adj_matrix;
    }
    

    void read_triplet(const string &filename) {
        ifstream file(filename);

        if (not file.is_open())
        {
        throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
        }

        std::string from, to;
        double value;

        while (file >> from >> to >> value) 
        {
            add_edge(from, to, value);
        }

        file.close();

    }


    void add_edge(const string &begin, const string &end, double value)
    {
        add_vertex(begin);
        add_vertex(end);

        vertex_list[correlation_map[begin]]->add_edge(correlation_map[end], value);
    }

    void dfs() {
        set<int> visited;
        stack<int> stack;

        if (vertex_list.size() != 0)
        {
            visited.insert(vertex_list[0]->name);
            stack.push(vertex_list[0]->name);
            int current;

            while (stack.size() != 0) {
                current = stack.top();
                stack.pop();

                if (visited.find(current)!=visited.end()) {
                    visited.insert(current);
                    for (Edge* edge : vertex_list[current]->edge_list) {
                        stack.push(edge->end);
                    }
                }

            }
            


        }

    }

    // Pour debuger
    void print()
    {
        for (Vertex *vertex : vertex_list)
        {
            cout << vertex->name << ": " << vertex->str_name() <<endl;
            vertex->print();
        }
    }

    ~Graph() 
    {
        for (Vertex* vertex : vertex_list) {
            delete vertex;
        }
        delete adj_matrix;
    }
};

Graph read_triplet(const std::string &filename)
{
    Graph g;
    std::cout << "read_triplet(" << filename << ")" << std::endl;

    // on essaie d'ouvrir le fichier en lecture
    // pour cela on crée un objet de type std::ifstream (input file stream)
    //    et le constructeur ouvre le fichier
    std::ifstream file(filename);

    if (not file.is_open())
    {
        // si le fichier n'a pas pu être ouvert, on s'en va e.g. par une exception
        throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
    }

    // si on est arrivé là c'est que le fichier est ouvert, on va le lire
    // on sait qu'il contient le graphe sur une ligne sous la forme de triplets: from to value
    // e.g. Paris Lyon 100 Paris Nice 200 Paris ...

    // from, to sont des strings et value un double
    // on réserve trois variables pour lire ces valeurs
    std::string from, to;
    double value;

    while (file >> from >> to >> value) // tant qu'on a un triplet (les 2 strings et l'int) à lire
    // notons que l'expression "file >> var" a comme valeur l'état du fichier après la lecture de var
    {
        std::cout << from << " " << to << " " << value << std::endl;
        g.add_edge(from, to, value);
        // là on l'affiche simplement l'arête, mais il faut l'ajouter au graphe !
        // g.add_vertex(from, to, value);
    }
    std::cout << std::endl;

    file.close(); // on ferme le fichier

    // Attention ça échouera si vous mettez un nom de ville avec un espace (ou une tabulation)
    // (même si vous mettez des " " autour), en effet
    //    - quand une std::string est lue, la lecture se fait jusqu'au premier espace
    //      si vous mettez "Le Havre" ça fera deux mots donc ça échouera
    //      il faudra mettre Le_Havre

    return g;
}

inline string Vertex::str_name() {
    for (auto &e : graph->correlation_map) {
        if (e.second==name) {
            return e.first;
        }
    }

    return "problem"; // Le code ne devrait jamais arriver ici mais il ne veut pas complier sans elle
}

inline void Edge::print() {
    cout << graph->vertex_list[start]->str_name() << " -> " << graph->vertex_list[end]->str_name() << " : " << weight << endl;
}