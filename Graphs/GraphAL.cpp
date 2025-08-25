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
}

int main() 
{
  puts("All right\n");
  return 0;
}
