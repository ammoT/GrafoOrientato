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

void testIt();
void testMetodiFondamentali();
void testDelete();

int main(void) {
  std::cout << "Grafo Orientato tramite matrici di adiacenza, Tommasini Stefano 810929" << std::endl;
	testMetodiFondamentali();
	testDelete();
  testIt();
  return 0;
}

void testMetodiFondamentali() {
	Grafo<int> g;

	g.addNodo(1);
	g.addNodo(2);
	g.addNodo(3);
	g.addEdge(1,1);
	g.addEdge(3,2);

	std::cout << "Stampo g dopo inserimenti" << std::endl;
	std::cout << g << std::endl;

	Grafo<int> g2(g);

	std::cout << "Testo costruttore di copia, stampo g2" << std::endl;
	std::cout << g2 << std::endl;

	Grafo<int> g3;
	g3 = g2;

	std::cout << "Testo operatore = , stampo g3" << std::endl;
	std::cout << g3 << std::endl;
}

void testDelete() {
	int n = 3;
	Grafo<int> gs(n);

	std::cout << "Test delEdge" << std::endl;

  for (int i = 1; i <= n; i++)
    gs.addNodo(i);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      gs.addEdge(i,j);
  for (int i = 1; i <= n; i++)
    gs.delEdge(i,i);

  std::cout << gs << std::endl;

	std::cout << "Test delNodo" << std::endl;

	gs.delEdge(1,3);
	gs.delNodo(2);

	std::cout << gs << std::endl;
}

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
