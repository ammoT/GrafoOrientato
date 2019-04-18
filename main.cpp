#include <iostream>
#include "grafo.h"
#include <string.h>

//funtori
struct equal_String{
	bool operator()(std::string a, std::string b) const{
		return !a.compare(b);
	}
};

struct equal_int{
	bool operator()(int a, int b) const{
		return a==b;
	}
};

void simpleTest() {
  int n = 3;
  Grafo<int, equal_int> gs(n);
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
  Grafo<int, equal_int> gra;
  gra.addNodo('C');
  gra.addNodo('I');
  gra.addNodo('A');
  gra.addNodo('O');

  Grafo<char>::const_iterator I = gra.begin();
  Grafo<char>::const_iterator IE = gra.end();

  std::cout << std::endl;
  for (; I != IE; I++)
      std::cout << *I;
  std::cout << std::endl;
  std::cout << std::endl;
  //testInt();
  //testChar();
  //simpleTest();
  return 0;
}

//aggiungere elemento -> creando nuova matrice + grande e spostando tutto
