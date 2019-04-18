/*
 @file    main.cpp
 @author  Tommasini Stefano, 810929
 @version 1.0
 */
#include <iostream>
#include "grafo.h"

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

struct equal_char{
	bool operator()(char a, char b) const{
		return a==b;
	}
};

struct equal_double{
	bool operator()(double a, double b) const{
		return a==b;
	}
};

void testIt() {
  Grafo<std::string, equal_String> gra;
  gra.addNodo("UNO");
  gra.addNodo("DUE");
  gra.addNodo("TRE");
  gra.addNodo("UNO");
  std::cout << gra << std::endl;

  Grafo<std::string, equal_String>::const_iterator i = gra.begin();
  Grafo<std::string, equal_String>::const_iterator ie = gra.end();

  std::cout << std::endl;
  for (; i != ie; i++)
      std::cout << *i;
  std::cout << std::endl;
  std::cout << std::endl;


}


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
  testIt();
  //simpleTest();
  return 0;
}

//aggiungere elemento -> creando nuova matrice + grande e spostando tutto
