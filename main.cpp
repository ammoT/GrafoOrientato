#include <iostream>
#include "grafo.h"
#include <string>

//funtori
struct equal_String{
	bool operator()(String a, String b) const{
		return !a.compare(b);
	}
};

//funtore di compere int perchè vanno passati alla classe e contengono l'operator

struct compare_int{
	bool operator()(int a, int b) const{
		return a<b;//condizione di olist cicla finchè è vero ordino in ordine decrescente
	}
};
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
  Grafo<char> gra;
  gra.addNodo('C');
  gra.addNodo('I');
  gra.addNodo('A');
  gra.addNodo('O');

  Grafo<char>::const_iterator I = gra.begin();
  Grafo<char>::const_iterator E = gra.end();

  std::cout << std::endl;
  for (; I != E; I++)
      std::cout << *I;
  std::cout << std::endl;
  std::cout << std::endl;
  //testInt();
  //testChar();
  //simpleTest();
  return 0;
}

//aggiungere elemento -> creando nuova matrice + grande e spostando tutto
