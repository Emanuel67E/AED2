#include <iostream>
#include <list>

typedef unsigned int uint;
typedef unsigned int Vertex;

template <typename T>
class GraphAL {
private:
  uint num_vertices;
  uint num_edges;
  std::list<T> *adj;
public:
  GraphAL(uint);
  ~GraphAL();
  void add_edge();
};

template <typename T>
GraphAL<T>::GraphAL(uint num_vertices) {
  num_vertices = num_vertices;
  num_edges = 0;
  adj = new std::list<T>[num_vertices];
}

template <typename T>
GraphAL<T>::~GraphAL() {
  for(int i=0; i<num_vertices; ++i) {
    adj[i].clear();
  }
  
}

template <typename T>
GraphAL<T>::add_edge(Vertex u, Vertex v) {
  adj[u].push_back(v);
  adj[v].push_back(u);
  ++num_edges;
}

int main()
{
  
}
