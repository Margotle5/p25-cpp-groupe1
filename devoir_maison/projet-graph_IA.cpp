/*Généré par Chatgpt*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <fstream>
#include <limits>

// Forward declarations
class Vertex;
class Edge;
class Graph;

/* ===================== Edge ===================== */
class Edge {
private:
    Vertex* destination;
    double weight;

    friend class Graph;
    friend class Vertex;

public:
    Edge(Vertex* dest, double w) : destination(dest), weight(w) {}
};

/* ===================== Vertex ===================== */
class Vertex {
private:
    std::string name; //l'IA utilise des string à la place des int 
    std::vector<Edge*> edges;

    friend class Graph;

public:
    Vertex(const std::string& n) : name(n) {}

    ~Vertex() {
        for (Edge* e : edges)
            delete e;
    }
};

/* ===================== Matrix ===================== */
class Matrix {
private:
    std::vector<std::vector<double>> data; //La classe matrix de l'IA est un tableau de tableau

    friend class Graph;

public:
    Matrix(int n) {
        data.resize(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));
        for (int i = 0; i < n; ++i)
            data[i][i] = 0.0;
    }
};

/* ===================== Graph ===================== */
class Graph {
private:
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> index_map;
    Matrix* adjacency_matrix = nullptr;

    void dfs_recursive(Vertex* v, std::set<std::string>& visited) {
        visited.insert(v->name);
        std::cout << v->name << " ";

        for (Edge* e : v->edges) {
            if (visited.find(e->destination->name) == visited.end()) {
                dfs_recursive(e->destination, visited);
            }
        }
    }

public:
    ~Graph() {
        for (Vertex* v : vertices)
            delete v;
        delete adjacency_matrix;
    }

    void add_vertex(const std::string& name) { //L'IA a mit add_vertex en public
        if (index_map.find(name) != index_map.end())
            return;

        vertices.push_back(new Vertex(name));
        index_map[name] = vertices.size() - 1; //l'IA ajoute la numéro du sommet après avoir ajouté le sommet dans la map 
    }

    void add_edge(const std::string& from, const std::string& to, double weight) {
        Vertex* src = vertices[index_map[from]];
        Vertex* dest = vertices[index_map[to]];
        src->edges.push_back(new Edge(dest, weight));
    }

    void read_graph(const std::string& filename) {
        std::ifstream file(filename);
        std::string from, to;
        double weight;

        while (file >> from >> to >> weight) {
            add_vertex(from);
            add_vertex(to);
            add_edge(from, to, weight);
        }
    }

    void depth_first_search(const std::string& start) {
        std::set<std::string> visited;
        dfs_recursive(vertices[index_map[start]], visited);
        std::cout << std::endl;
    }

    void build_adjacency_matrix() {
        int n = vertices.size();
        adjacency_matrix = new Matrix(n);

        for (int i = 0; i < n; ++i) {
            for (Edge* e : vertices[i]->edges) {
                int j = index_map[e->destination->name];
                adjacency_matrix->data[i][j] = e->weight;
            }
        }
    }

    void floyd_warshall() {
        int n = vertices.size();
        auto& m = adjacency_matrix->data;

        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (m[i][k] + m[k][j] < m[i][j]) //l'IA utilise une comparaison alors que j'ai utilisé la fonction min
                        m[i][j] = m[i][k] + m[k][j];
    }

    void print_matrix() {
        int n = vertices.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjacency_matrix->data[i][j] == std::numeric_limits<double>::infinity())
                    std::cout << "INF "; 
                else
                    std::cout << adjacency_matrix->data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

/* ===================== Exemple main ===================== */
int main() {
    Graph g;
    g.read_graph("graph.txt");

    std::cout << "DFS depuis A: ";
    g.depth_first_search("A");

    g.build_adjacency_matrix();
    g.floyd_warshall();

    std::cout << "\nMatrice des plus courts chemins:\n";
    g.print_matrix();

    return 0;
}
