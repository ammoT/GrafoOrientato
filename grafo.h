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
    #ifdef NDEBUG
    std::cout << "init(size)" << std::endl;
    #endif
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
    #ifdef NDEBUG
    std::cout << "Grafo()" << std::endl;
    #endif
    init(_size);
  }

  Grafo(int sz) : _size(sz), nodi(0), archi(0), cont(0) {
    #ifdef NDEBUG
    std::cout << "Grafo(sz)" << std::endl;
    #endif
    init(_size);
  }

  ~Grafo(){
    #ifdef NDEBUG
    std::cout << "~Grafo()" << std::endl;
    #endif
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
    for (int i = 0; i < cont; i++)
      if(nodo == nodi[i])
        return i;
    return 404;
  }

  void addNodo(const T nodo) {
    #ifdef NDEBUG
    std::cout << "addNodo(nodo)" << std::endl;
    #endif

    if (exist(nodo) != 404)
      return;

    if(cont < _size) {
      nodi[cont] = nodo;
      cont++;
    }
    else {
      Grafo<T> tmp(_size + 1);
      unsigned int sz = getDim();
///////////////////////////////////////////// migliorare
      for (int i = 0; i < sz; i++){
        tmp.nodi[i] = nodi[i];
        for (int j = 0; j < sz; j++)
          tmp.archi[i][j] = archi[i][j];
        tmp.cont++;
        }
////////////////////////////////////////////
      swap(tmp);
      addNodo(nodo);
    }
  }

  void delNodo(const T nodo) {
    unsigned int n = exist(nodo);
    if(n == 404)
      return;
    else {
      Grafo<T> tmp(_size - 1);
      if (cont == n + 1){
        //std::cout << _size << std::endl;
        cont--;
        tmp = *this;
        swap(tmp);
      }
      else {
        unsigned int sz = getDim();
        for (int i = 0; i < sz; i++){
          if(i < n)
            tmp.addNodo(nodi[i]);
          else if (i < tmp._size)
          tmp.addNodo(nodi[i + 1]);
          for(int j = 0; j < sz; j++){
            if(i < n && j < n)
              tmp.archi[i][j] = archi[i][j];
            else if ((i >= n || j >= n) && (i < tmp._size && j < tmp._size))
              tmp.archi[i][j] = archi[i + 1][j + 1];
          }
        }
        swap(tmp);
      }
    }
  }

  unsigned int getDim() const {
    #ifdef NDEBUG
    std::cout << "getDim()" << std::endl;
    #endif
    return cont;
  }

  bool hasEdge(const T nodoP, const T nodoD) const {
    #ifdef NDEBUG
    std::cout << "hasEdge(nodoP, nodoD)" << std::endl;
    #endif
    unsigned int p,d; //indici posizione nodi nella matrice;
    p = exist(nodoP);
    d = exist(nodoD);
    if ((p && d) != 404)
      return archi[p][d];
    return 0;
  }

  void addEdge(const T nodoP, const T nodoD) const {
    #ifdef NDEBUG
    std::cout << "addEdge(nodoP, nodoD)" << std::endl;
    #endif
    unsigned int p,d; //indici posizione nodi nella matrice;
    p = exist(nodoP);
    d = exist(nodoD);
    if ((p && d) != 404)
      archi[p][d] = 1;
  }

  void swap(Grafo &other) {
    #ifdef NDEBUG
    std::cout << "swap(other)" << std::endl;
    #endif
    std::swap(nodi, other.nodi);
    std::swap(archi, other.archi);
    std::swap(_size, other._size);
    std::swap(cont, other.cont);
  }

};

template <typename T>
std::ostream &operator<<(std::ostream& os, const Grafo<T> &g){
  unsigned int size = g.getDim();
  if (size == 0)
    return os << "GRAFO VUOTO";
  os << "NODI : [ ";
  for (int i = 0; i < size; i++)
    os << g.nodi[i] << " ";
  os << "]" << std::endl;
  os << "MATRICE : " << std::endl;
  os << " | ";
  for (int i = 0; i < size; i++)
    os << g.nodi[i] << " ";
  os << std::endl;
  os << "------------" << std::endl;
  for (int i = 0; i < size; i++){
    os << g.nodi[i] << "| ";
    for (int j = 0; j < size; j++)
      os << g.archi[i][j] << " ";
    os << std::endl;
    }
  return os;
}
#endif
