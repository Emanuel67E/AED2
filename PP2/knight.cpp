#include <iostream>
#include <list>
#include <vector>
#include <cstdio>

typedef unsigned int uint;

class BoardSquare {
public:
  int color;
  int distance;
  int father;
};

class Fila {
private:
  std::list<int> elementos;
public:
  void enfileirar(int u) {
    elementos.push_back(u);
  }
  int desenfileirar() {
    int u = elementos.front();
    elementos.pop_front();
    return u;
  }
  int se_vazia() {
    return elementos.empty();
  }
  int tamanho() {
    return elementos.size();
  }
};

class Board {
private:
  uint size; // lado do tabuleiro
  std::vector<std::vector<int>> adj;
public:
  Board(uint);
  void bfs(int, int*);
};

Board::Board(uint _size) {
  size = _size;
  int totalCells = size*size;
  adj.resize(totalCells, std::vector<int>(totalCells, 0));

  for(int i=0; i<totalCells; i++) {
    int row = i / size;
    int col = i % size;

    if(row >= 2) {
      if(col >= 1) {
        int j = (row-2)*size + (col-1); //cima-esquerda
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
      if(col < size-1) {
        int j = (row-2)*size + (col+1); //cima-direita
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
    }

    if(row < size-2) {
      if(col >= 1) {
        int j = (row+2)*size + (col-1); //baixo-esquerda
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
      if(col < size-1) {
        int j = (row+2)*size + (col+1); //baixo-direita
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
    }

    if(col >= 2) {
      if(row >= 1) {
        int j = (row-1)*size + (col-2); //esquerda-cima
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
      if(row < size-1) {
        int j = (row+1)*size + (col-2); //esquerda-baixo
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
    }

    if(col < size-2) {
      if(row >= 1) {
        int j = (row-1)*size + (col+2); //direita-cima
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
      if(row < size-1) {
        int j = (row+1)*size + (col+2); //direita-baixo
        adj[i][j] = 1;
        adj[j][i] = 1;
      }
    }
  }
}

void Board::bfs(int king, int* knights) {
  int totalCells = size*size;
  BoardSquare cell[totalCells];
  Fila fila;

  for(int i=0; i<totalCells; i++) {
    cell[i].color = -1;
    cell[i].distance = -1;
    cell[i].father = -1;
  }
  cell[king].color = 0;
  cell[king].distance = 0;
  cell[king].father = -1;

  fila.enfileirar(king);
  int min_distance = -1;

  while(fila.se_vazia() != 1) {
    int u = fila.desenfileirar();

    if(min_distance != -1 && cell[u].distance > min_distance) {
      continue;
    }

    if(knights[u] == 1) {
      if(min_distance == -1) {
        min_distance = cell[u].distance;
        printf("%d ", (min_distance-1) );
      }
      else if(cell[u].distance == min_distance) {
        printf("%d ", (min_distance-1) );
      }
    }

    for(int v=0; v<totalCells; v++) {
      if(adj[u][v] == 1) {
        if(cell[v].color == -1) {
          cell[v].color = 0;
          cell[v].distance = cell[u].distance + 1;
          cell[v].father = u;
          fila.enfileirar(v);
        }
      }
    }

    cell[u].color = 1;
  }
}

int main() {

  int board_size = 8;
  Board board(board_size);

  int num_tests;
  scanf("%d", &num_tests);

  int piecePos[num_tests][5];

  for(int i=0; i<num_tests; i++) {
    for(int j=0; j<5; j++) {
      char char_row, char_col;
      scanf(" %c%c", &char_col, &char_row);

      int row = (char_row-49);
      int col = (char_col-97);

      piecePos[i][j] = (row*8 + col);
    }
  }

  for(int i=0; i<num_tests; i++) {
    int king = piecePos[i][4];
    int totalCells = board_size * board_size;

    int knights[totalCells];
    for(int z=0; z<totalCells; z++) {
      knights[z] = 0;
    }

    for(int j=0; j<4; j++) {
      knights[ piecePos[i][j] ] = 1;
    }

    board.bfs(king, knights);
  }

  return 0;
}
