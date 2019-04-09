#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <ostream>
#include <cassert>
template <typename T>
class Grafo{
private:
  struct nodo {
    T id;
    bool used;
    explicit nodo() : id(0), used(0) {}
    nodo& operator=(const nodo &other) {
      id = other.id;
      used = other.used;
      return *this;
    }
  };
public:
  unsigned int _size;
  nodo *nodi;
  bool **archi;

public:
  void init(unsigned int size){
    #ifdef NDEBUG
    std::cout << "init(size)" << std::endl;
    #endif
    _size = size;
    nodi = new nodo[size];
    archi = new bool*[size];
    for (int i = 0; i < size; i++)
      archi[i] = new bool[size];
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
        archi[i][j] = false;
  }

  Grafo() : _size(0), nodi(0), archi(0){
    #ifdef NDEBUG
    std::cout << "Grafo()" << std::endl;
    #endif
  }

  explicit Grafo(int sz) : _size(sz), nodi(0), archi(0) {
    #ifdef NDEBUG
    std::cout << "Grafo(sz)" << std::endl;
    #endif
    init(_size);
  }

  Grafo(const Grafo &other) : _size(0), archi(0), nodi(0) {
    #ifdef NDEBUG
    std::cout << "copy constructor()" << std::endl;
    #endif
    init(other._size);
    for (int i = 0; i < other.getDim(); i++){
      nodi[i] = other.nodi[i];
      for (int j = 0; j < other.getDim(); j++)
        archi[i][j] = other.archi[i][j];
      }
  }

  Grafo& operator=(const Grafo &other) {
    #ifdef NDEBUG
    std::cout << "operator=()" << std::endl;
    #endif
    if(this != &other){
      Grafo<T> tmp(other);
      swap(tmp);
    }
    return *this;
  }

  void swap(Grafo &other) {
    #ifdef NDEBUG
    std::cout << "swap(other)" << std::endl;
    #endif
    std::swap(nodi, other.nodi);
    std::swap(archi, other.archi);
    std::swap(_size, other._size);
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

  //Trova quanti nodi sono stati inseriti
  unsigned int getDim() const {
    unsigned int cont = 0;
    for (int i = 0; i < _size && nodi[i].used; i++)
      cont++;
    return cont;
  }

  //aggiungi nodo
  void addNodo(T val) {
    if (exist(val) >= 0)
      std::cout << "NODO GIA PRESENTE" << std::endl;
    else if(getDim() == _size){
      std::cout << "NO SPACE" << std::endl;
      Grafo<T> tmp(_size * 2);
      for (int i = 0; i < getDim(); i++) {
        tmp.nodi[i] = nodi[i];
        for(int j = 0; j < getDim(); j++)
         tmp.archi[i][j] = archi[i][j];
       }
       tmp.addNodo(val);
      swap(tmp);
    }
    else {
      nodi[getDim()].id = val;
      nodi[getDim()].used = 1;
    }
  }

  //controllo se esiste un nodo con quel identificativo
  int exist(const T val) const{
    for (int i = 0; i < getDim(); i++)
      if (nodi[i].id == val)
        return i;
    return -1;
  }

  void addEdge(const T nodoP, const T nodoD) const {
    #ifdef NDEBUG
    std::cout << "addEdge(nodoP, nodoD)" << std::endl;
    #endif
    int p,d; //indici posizione nodi nella matrice;
    p = exist(nodoP);
    d = exist(nodoD);
    if ((p && d) >= 0)
      archi[p][d] = 1;
    else
      std::cout << "ARCO NON AGGIUNTO";
  }

  bool hasEdge(const T nodoP, const T nodoD) const {
    #ifdef NDEBUG
    std::cout << "hasEdge(nodoP, nodoD)" << std::endl;
    #endif
    unsigned int p,d; //indici posizione nodi nella matrice;
    p = exist(nodoP);
    d = exist(nodoD);
    if ((p && d) >= 0)
      return archi[p][d];
    return 0;
  }

  void delNodo(const T nodo) {
    #ifdef NDEBUG
    std::cout << "DelNodo(nodo)" << std::endl;
    #endif
    int target = exist(nodo);
    if (target >= 0){
      Grafo<T> tmp(_size - 1);
      for(int i = 0; i < target;i++){
        tmp.nodi[i] = nodi[i];
        for(int j = 0; j < target; j++)
          tmp.archi[i][j] = archi[i][j];
      }
      for(int i = target + 1; i < _size; i++){
        tmp.nodi[i - 1] = nodi[i];
        for(int j = target + 1; j < _size; j++)
          tmp.archi[i - 1][j - 1] = archi[i][j];
      }
      swap(tmp);
    }
    else
      std::cout << "Nodo non presente" << std::endl;
  }

  //rimozione ARCO
  void delEdge(const T nodoP, const T nodoD) {
    #ifdef NDEBUG
    std::cout << "delEdge(nodoP, nodoD)" << std::endl;
    #endif
    if(hasEdge(nodoP, nodoD)){
      int p = exist(nodoP);
      int d = exist(nodoD);
      archi[p][d] = 0;
    }
    else
      std::cout << "Arco non presente" << std::endl;
  }
};

template <typename T>
std::ostream &operator<<(std::ostream& os, const Grafo<T> &g){
  unsigned int size = g.getDim();
  if (size == 0)
    return os << "GRAFO VUOTO";
  os << "NODI : [ ";
  for (int i = 0; i < size; i++)
    os << g.nodi[i].id << " ";
  os << "]" << std::endl;
  os << "MATRICE : " << std::endl;
  os << " | ";
  for (int i = 0; i < size; i++)
    os << g.nodi[i].id << " ";
  os << std::endl;
  os << "------------" << std::endl;
  for (int i = 0; i < size; i++){
    os << g.nodi[i].id << "| ";
    for (int j = 0; j < size; j++)
      os << g.archi[i][j] << " ";
    os << std::endl;
    }
  return os;
}
#endif
