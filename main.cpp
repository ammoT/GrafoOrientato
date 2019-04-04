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
}

int main(void) {
  std::cout << "Grafo Orientato tramite matrici di adiacenza" << std::endl;

  testInt();
  testChar();
  
  return 0;
}

//aggiungere elemento -> creando nuova matrice + grande e spostando tutto
