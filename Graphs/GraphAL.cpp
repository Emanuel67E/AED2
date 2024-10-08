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
  void add_edge(Vertex, Vertex);
  void remove_edge(Vertex, Vertex);
  uint get_num_vertices() {return num_vertices;}
  uint get_num_edges() {return num_edges;}
  std::list<T> get_adj(Vertex u) {
    if(0<=u && u<num_vertices) {
      return adj[u];
    }
    std::list<T> void_l;
    return void_l;
  }
};

template <typename T>
GraphAL<T>::GraphAL(uint _num_vertices) {
  num_vertices = _num_vertices;
  num_edges = 0;
  adj = new std::list<T>[num_vertices];
}

template <typename T>
GraphAL<T>::~GraphAL() {
  for(int i=0; i<num_vertices; ++i) {
    adj[i].clear();
  }
  delete[] adj;
  adj = nullptr;
}

template <typename T>
void GraphAL<T>::add_edge(Vertex u, Vertex v) {
  int notIn = 1;
  for(auto e: adj[u]) {
    if(e == v) {
      notIn = 0;
    }
  }
  int nv = num_vertices;
  int valid = (u!=v) && (0<=u && u<nv && 0<=v && v<nv);
  if(notIn && valid) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    ++num_edges;
  }
}

template <typename T>
void GraphAL<T>::remove_edge(Vertex u, Vertex v) {
  adj[u].remove(v);
  adj[v].remove(u);
}

template <typename T>
void input_graph(GraphAL<T>& g, uint num_edges) {
  uint max_vertice = g.get_num_vertices();
  T u, v;
  for(int i=0; i<num_edges; ++i) {
    std::cin >> u >> v;
    if(u>=0 && u<max_vertice && v>=0 && v<max_vertice) {
      g.add_edge(u, v);
    }
  }
}

template <typename T>
void print_graph(GraphAL<T> g) {
  uint num_vertices = g.get_num_vertices();
  uint num_edges = g.get_num_edges();

  std::cout << "num_vertices: " << num_vertices << "\n";
  std::cout << "num_edges: " << num_edges << "\n";

  for(int i=0; i<num_vertices; ++i) {
    std::cout << i << ": ";
    std::list adj = g.get_adj(i);
    for(auto e: adj) {
      std::cout << e << ", ";
    }
    std::cout << "\n";
  }
}

int main()
{
  uint num_vertices;
  uint num_edges;
  std::cin >> num_vertices >> num_edges;

  GraphAL<Vertex> g{num_vertices};

  input_graph(g, num_edges);
  print_graph(g);
}
