#include <iostream>
#include <stdexcept>
#include <list>

typedef unsigned int uint;
typedef unsigned int Vertex;

class GraphAL {
private:
  uint num_vertices;
  uint num_edges;
  std::list<Vertex> *adj;
public:
  GraphAL(uint);
  ~GraphAL();
  void add_edge(Vertex, Vertex);
  void remove_edge(Vertex, Vertex);
  std::list<Vertex> get_adj(Vertex);
  uint get_num_vertices() { return num_vertices;}
};

GraphAL::GraphAL(uint _num_vertices) {
  num_vertices = _num_vertices;
  num_edges = 0;
  adj = new std::list<Vertex>[num_vertices];
}

GraphAL::~GraphAL() {
  delete[] adj;
 adj = nullptr;
}

void GraphAL::add_edge(Vertex u, Vertex v) {
  if(u == v || u >= num_vertices || v >= num_vertices) {
    throw std::runtime_error("Entradas invalidas!\n");
  }
  adj[u].push_back(v);
  adj[v].push_back(u);
  num_edges++;
}

void GraphAL::remove_edge(Vertex u, Vertex v) {
  if(u == v || u >= num_vertices || v >= num_vertices) {
    throw std::runtime_error("Entradas invalidas!\n");
  }
  adj[u].remove(v);
  adj[v].remove(u);
  num_edges--;
}

std::list<Vertex> GraphAL::get_adj(Vertex u) {
  if(u >= num_vertices) {
    throw std::runtime_error("Entrada invalida!\n");
  }
  return adj[u];
}

void print_adjacency_list(GraphAL g) {
  for(int u=0; u<g.get_num_vertices(); u++) {
    std::list<Vertex> adj = g.get_adj(u);
    std::cout << u << ": ";
    for(auto e: adj) {
      std::cout << e << ", ";
    }
    std::cout << std::endl;
  }
}

int main() 
{
  puts("All right\n");
  return 0;
}
