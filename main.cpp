#include <iostream>
#include "grafo.h"
void testing() {
  Grafo<int> g(5);
  g.addNodo(1);
  g.addNodo(2);

  Grafo<int> g2(g);
  Grafo<int> g3;

  g2.addNodo(3);
  g2.addNodo(4);
  g2.addNodo(5);

  g3 = g2;

  g3.addNodo(6);
  g3.addNodo(1);
  g.addNodo(9);

  g.addEdge(1,1);

  std::cout << "HAS EDGE g(1,1) : " << g.hasEdge(1,2) << std::endl;

  std::cout << g << std::endl;
  std::cout << g2 << std::endl;
  std::cout << g3 << std::endl;

  g3.delNodo(4);

  std::cout << g3 << std::endl;
}
int main(void) {
  std::cout << "Grafo Orientato tramite matrici di adiacenza" << std::endl;
  testing();
  return 0;
}

//aggiungere elemento -> creando nuova matrice + grande e spostando tutto
