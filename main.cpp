#include <iostream>
#include "grafo.h"

void testInt() {
  Grafo<int> gi;
  gi.addNodo(1);
  gi.addNodo(2);
  gi.addNodo(3);

  gi.addEdge(1, 1);
  gi.addEdge(2, 2);
  gi.addEdge(3, 3);

  std::cout << gi << std::endl;

  std::cout << "RIMOZIONE NODO INTERMEDIO" << std::endl;
  gi.delNodo(2);
  std::cout << gi << std::endl;

  std::cout << "RIMOZIONE NODO FINALE" << std::endl;
  gi.delNodo(3);
  std::cout << gi << std::endl;

  std::cout << "RIMOZIONE NODO INIZIALE" << std::endl;
  gi.delNodo(1);
  std::cout << gi << std::endl;
}

void testChar() {
  Grafo<char> gc;
  gc.addNodo('A');
  gc.addNodo('B');
  gc.addNodo('C');

  gc.addEdge('A', 'A');
  gc.addEdge('B', 'B');
  gc.addEdge('C', 'C');

  std::cout << gc << std::endl;

  std::cout << "RIMOZIONE NODO INTERMEDIO" << std::endl;
  gc.delNodo('B');
  std::cout << gc << std::endl;

  std::cout << "RIMOZIONE NODO FINALE" << std::endl;
  gc.delNodo('C');
  std::cout << gc << std::endl;

  std::cout << "RIMOZIONE NODO INIZIALE" << std::endl;
  gc.delNodo('A');

  std::cout << gc << std::endl;
}

void simpleTest() {
  int n = 3;
  Grafo<int> gs(n);
  for (int i = 1; i <= n; i++)
    gs.addNodo(i);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      gs.addEdge(i,j);
  for (int i = 1; i <= n; i++)
    gs.delEdge(i,i);
  std::cout << gs << std::endl;
}

int main(void) {
  std::cout << "Grafo Orientato tramite matrici di adiacenza" << std::endl;
  Grafo<int> gra;
  gra.addNodo(1);
  gra.addNodo(4);
  gra.addNodo(2);
  gra.addNodo(3);

  typename Grafo<int>::const_iterator I = gra.begin();
  typename Grafo<int>::const_iterator E = gra.end();

  for (; I != E; I++)
    std::cout << *I;
  //testInt();
  //testChar();
  simpleTest();
  return 0;
}

//aggiungere elemento -> creando nuova matrice + grande e spostando tutto
