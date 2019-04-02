#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <ostream>
#include <cassert>
template <typename T>
class Grafo{
public:
  unsigned int cont;
  unsigned int _size;
  T *nodi;
  bool **archi;

public:
  void init(unsigned int size){
    nodi = new T[size];
    for(int i = 0; i < _size; i++)
      nodi[i] = 0;
    archi = new bool*[size];
    for (int i = 0; i < size; i++)
      archi[i] = new bool[size];
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
        archi[i][j] = false;
  }

  Grafo() : _size(0) ,nodi(0), archi(0), cont(0){
    init(_size);
  }

  Grafo(int sz) : _size(sz), nodi(0), archi(0), cont(0) {
    init(_size);
  }

  ~Grafo(){
    delete[] nodi;
    for (int i = 0; i < _size; i++)
      delete[] archi[i];
    nodi = 0;
    archi = 0;
  }

  Grafo(const Grafo &other) : _size(0), archi(0), nodi(0), cont(0) {
    Grafo<T> tmp(other._size);
    for (int i = 0; i < other.getDim(); i++){
      tmp.nodi[i] = other.nodi[i];
      for (int j = 0; j < other.getDim(); j++)
        tmp.archi[i][j] = other.archi[i][j];
      tmp.cont++;
      }
    swap(tmp);
  }

  Grafo& operator=(const Grafo &other) {
    Grafo<T> tmp(other);
    swap(tmp);
    return *this;
  }

  unsigned int  exist(const T nodo) const {
    for (int i = 0; i < getDim(); i++)
      if(nodo == nodi[i])
        return i;
    return 404;
  }

  void addNodo(const T nodo) {

    if (exist(nodo) != 404)
      return;

    if(cont < _size) {
      nodi[cont] = nodo;
      cont++;
    }
    else {
      Grafo<T> tmp(_size + 1);
///////////////////////////////////////////// migliorare
      for (int i = 0; i < getDim(); i++){
        tmp.nodi[i] = nodi[i];
        for (int j = 0; j < getDim(); j++)
          tmp.archi[i][j] = archi[i][j];
        tmp.cont++;
        }
////////////////////////////////////////////
      swap(tmp);
      addNodo(nodo);
    }
  }

  void delNodo(const T nodo) {
    if(exist(nodo) == 404)
      return;
    else {
      for (int i = 0; i < getDim(); i++)
        if(nodo == nodi[i])
          nodi[i] = 0;
    }
  }

  unsigned int getDim() const {
    return cont;
  }

  bool hasEdge(const T nodoP, const T nodoD) const {
    unsigned int p,d; //indici posizione nodi nella matrice;
    p = exist(nodoP);
    d = exist(nodoD);
    if ((p && d) != 404)
      return archi[p][d];
    return 0;
  }

  void addEdge(const T nodoP, const T nodoD) const {
    unsigned int p,d; //indici posizione nodi nella matrice;
    p = exist(nodoP);
    d = exist(nodoD);
    if ((p && d) != 404)
      archi[p][d] = 1;
  }

  void swap(Grafo &other) {
    std::swap(nodi, other.nodi);
    std::swap(archi, other.archi);
    std::swap(_size, other._size);
    std::swap(cont, other.cont);
  }

};

template <typename T>
std::ostream &operator<<(std::ostream& os, const Grafo<T> &g){
  os << "NODI : ";
  for (int i = 0; i < g.getDim(); i++)
    os << g.nodi[i] << " ";
  os << std::endl;
  os << "MATRICE : " << std::endl;
  os << " | ";
  for (int i = 0; i < g.getDim(); i++)
    os << g.nodi[i] << " ";
  os << std::endl;
  os << "------------" << std::endl;
  for (int i = 0; i < g.getDim(); i++){
    os << g.nodi[i] << "| ";
    for (int j = 0; j < g.getDim(); j++)
      os << g.archi[i][j] << " ";
    os << std::endl;
    }
    return os;
}
#endif
