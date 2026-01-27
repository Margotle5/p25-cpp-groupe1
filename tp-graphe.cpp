#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Vertex;
struct Edge;

vector<bool> false_list(int n) {
    vector<bool> v;
    for (int i=0; i<n; i++) {
        v.push_back(false);
    }
    return v;
}

struct Edge
{
    double weight;
    Vertex *start;
    Vertex *end;

    Edge(Vertex *start, Vertex *end, double weight) : start(start), end(end), weight(weight) {}

    void print() const;
};

struct Vertex
{
    std::vector<Edge *> edge_list;
    int value;

    Vertex(int i) : value(i) {};

    void add_edge(Vertex *j, double weight)
    {
        edge_list.push_back(new Edge(this, j, weight));
    }

    void print() const
    {
        cout << value << endl;
        for (int i = 0; i < edge_list.size(); i++)
        {
            edge_list[i]->print();
        }
    }
};

struct Graph
{
    std::vector<Vertex *> vertex_list;

    void add_vertex(int i)
    {
        if (vertex_list.size() < (i - 1))
        {
            for (int j = vertex_list.size(); j <= i; j++)
            {
                vertex_list.push_back(new Vertex(j));
            }
        }
    }

    void add_edge(int i, int j, double weight)
    {
        add_vertex(i);
        add_vertex(j);
        vertex_list[i]->add_edge(vertex_list[j], weight);
    }

    void print_adj() const
    {
        std::cout << "[";
        for (int i = 0; i < vertex_list.size(); i++)
        {
            std::cout << "[";
            Vertex *vertex = vertex_list[i];
            for (int j = 0; j < (vertex->edge_list).size(); j++)
            {
                std::cout << vertex->edge_list[j]->end->value << " ";
            }
            std::cout << "], ";
        }
        std::cout << "]" << std::endl;
    }

    void dfs_sommet(int i) const
    {
        if (vertex_list.size() == 0)
        {
            std::cout << "{}" << std::endl;
        }
        else if (i >= vertex_list.size())
        {
            cout << "Vertex not in graph" << endl;
        }
        else
        {
            vector<bool> was_visted= false_list(vertex_list.size());
            stack<Vertex *> stack;
            Vertex *current;

            stack.push(vertex_list[i]);

            while (stack.size() != 0)
            {
                current = stack.top();
                stack.pop();
                cout << current->value << " ";

                if (!was_visted[current->value])
                {
                    for (int i = 0; i < (current->edge_list).size(); i++)
                    {
                        if (!was_visted[(current->edge_list)[i]->end->value])
                        {
                            stack.push((current->edge_list)[i]->end);
                        }
                    }
                }
                was_visted[i] = true;
            }

            cout << endl;
        }
    }

    void dfs() {
        if (vertex_list.size() == 0)
        {
            std::cout << "{}" << std::endl;
        } else {
            vector<bool> was_visted= false_list(vertex_list.size());
            for (int i=0; i<vertex_list.size(); i++) {
                if (!was_visted[i]) {

                stack<Vertex *> stack;
                Vertex *current;

                stack.push(vertex_list[i]);

                while (stack.size() != 0) {
                    current = stack.top();
                    stack.pop();
                    cout << current->value << " ";

                    if (!was_visted[current->value]){
                        for (int i = 0; i < (current->edge_list).size(); i++){
                            if (!was_visted[(current->edge_list)[i]->end->value])
                            {
                                stack.push((current->edge_list)[i]->end);
                            }
                        }
                    }
                    was_visted[i] = true;
                }
                cout << endl;
            }
            }
        }

    }

    void print()
    {
        if (vertex_list.empty())
        {
            cout << "Empty graph" << endl;
        }
        else
        {
            for (int i = 0; i < vertex_list.size(); i++)
            {
                vertex_list[i]->print();
            }
        }
    }

};

inline void Edge::print() const
{
    cout << start->value << "->" << end->value << " weight:" << weight << endl;
}

int main()
{
    Graph g;

    g.add_edge(2, 5, 17.9);
    g.add_edge(5, 3, 23.9);
    g.add_edge(3, 4, 16.9);
    g.add_edge(4, 0, 699.9);
    g.print();
    cout << endl;
    g.dfs();

    return 0;
}