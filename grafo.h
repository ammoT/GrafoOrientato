#ifndef GRAFO_H
#define GRAFO_H
#include <iterator>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <cassert>
#include <string.h>
template <typename T , typename Eql>
class Grafo{
private:
  struct nodo {
    T id;
    bool used;
    //nodo() : id(0), used(0) {}
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

  Eql _equal;

public:
  void init(unsigned int size){
    #ifdef NDEBUG
    std::cout << ">init(size)" << std::endl;
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
    std::cout << ">Grafo()" << std::endl;
    #endif
  }

  explicit Grafo(int sz) : _size(sz), nodi(0), archi(0) {
    #ifdef NDEBUG
    std::cout << ">Grafo(sz)" << std::endl;
    #endif
    init(_size);
  }

  Grafo(const Grafo &other) : _size(0), archi(0), nodi(0) {
    #ifdef NDEBUG
    std::cout << ">copy constructor()" << std::endl;
    #endif
    init(other._size);
    for (int i = 0; i < other.NumNodi(); i++){
      nodi[i] = other.nodi[i];
      for (int j = 0; j < other.NumNodi(); j++)
        archi[i][j] = other.archi[i][j];
      }
  }

  Grafo& operator=(const Grafo &other) {
    #ifdef NDEBUG
    std::cout << ">operator=()" << std::endl;
    #endif
    if(this != &other){
      Grafo<T,Eql> tmp(other);
      swap(tmp);
    }
    return *this;
  }

  void swap(Grafo &other) {
    #ifdef NDEBUG
    std::cout << ">swap(other)" << std::endl;
    #endif
    std::swap(nodi, other.nodi);
    std::swap(archi, other.archi);
    std::swap(_size, other._size);
  }

  ~Grafo(){
    #ifdef NDEBUG
    std::cout << ">~Grafo()" << std::endl;
    #endif
    delete[] nodi;
    for (int i = 0; i < _size; i++)
      delete[] archi[i];
    delete[] archi;
    init(0);
  }

  //Trova quanti nodi sono stati inseriti
  unsigned int NumNodi() const {
    unsigned int cont = 0;
    for (int i = 0; i < _size && nodi[i].used; i++)
      cont++;
    return cont;
  }

  unsigned int NumArchi() const {
    unsigned int cont = 0;
    for (int i = 0; i < NumNodi(); i++)
      for (int j = 0; j < NumNodi(); j++)
        if (archi[i][j])
          cont++;
    return cont;
  }

  //aggiungi nodo
  void addNodo(T val) {
    if (exist(val) >= 0)
      std::cout << ">NODO GIA PRESENTE" << std::endl;
    else if(NumNodi() == _size){
      std::cout << "NO SPACE" << std::endl;
      Grafo<T,Eql> tmp((_size + 1)* 2);
      for (int i = 0; i < NumNodi(); i++) {
        tmp.nodi[i] = nodi[i];
        for(int j = 0; j < NumNodi(); j++)
         tmp.archi[i][j] = archi[i][j];
       }
       tmp.addNodo(val);
      swap(tmp);
    }
    else {
      nodi[NumNodi()].id = val;
      nodi[NumNodi()].used = 1;
    }
  }

  //controllo se esiste un nodo con quel identificativo
  int exist(const T val) const{
    for (int i = 0; i < NumNodi(); i++)
      if ((_equal(nodi[i].id, val)))//nodi[i].id == val)
        return i;
    return -1;
  }

  void addEdge(const T nodoP, const T nodoD) const {
    #ifdef NDEBUG
    std::cout << ">addEdge(nodoP, nodoD)" << std::endl;
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
    std::cout << ">hasEdge(nodoP, nodoD)" << std::endl;
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
    std::cout << ">DelNodo(nodo)" << std::endl;
    #endif
    int target = exist(nodo);
    if (target >= 0){
      Grafo<T,Eql> tmp(_size - 1);
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
    std::cout << ">delEdge(nodoP, nodoD)" << std::endl;
    #endif
    if(hasEdge(nodoP, nodoD)){
      int p = exist(nodoP);
      int d = exist(nodoD);
      archi[p][d] = 0;
    }
    else
      std::cout << "Arco non presente" << std::endl;
  }

  class const_iterator;

  class const_iterator {
		const nodo *n;
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

    const_iterator() : n(0) {
			//!!!
		}

    const_iterator(const const_iterator &other) : n(other.n) {
			//!!!
		}

		const_iterator& operator=(const const_iterator &other) {
      n = other.n;
    return *this;
		}

		~const_iterator() {
			n = 0;
		}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return n->id;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(n->id);
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
      const_iterator tmp(*this);
			n = n + 1;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			n = n + 1 ;
      return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return n == other.n;
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return n != other.n;
		}


  private:
  //Dati membro

  // La classe container deve essere messa friend dell'iteratore per poter
  // usare il costruttore di inizializzazione.
  friend class Grafo; // !!! Da cambiare il nome!

  // Costruttore privato di inizializzazione usato dalla classe container
  // tipicamente nei metodi begin e end
  const_iterator(const nodo *nn) : n(nn) {
    //!!!
  }

  // !!! Eventuali altri metodi privati
};

  // Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(nodi);
	}

	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(&nodi[NumNodi()]);
	}


};

template <typename T, typename E>
std::ostream &operator<<(std::ostream& os, const Grafo<T,E> &g){
  unsigned int size = g.NumNodi();
  if (size == 0)
    return os << "GRAFO VUOTO";
  os <<"Ci sono " << size <<  " NODI : [ ";
  for (int i = 0; i < size; i++)
    os << g.nodi[i].id << " ";
  os << "]" << std::endl;
  os << "Numero Archi : " << g.NumArchi() << std::endl;
  os << "MATRICE : " << std::endl;
  os << " | ";
  for (int i = 0; i < size; i++)
    os << g.nodi[i].id << " ";
  os << std::endl;
  for (int i = 0; i < (size * 2) + 3; i++)
    os << "-";
  os << std::endl;
  for (int i = 0; i < size; i++){
    os << g.nodi[i].id << "| ";
    for (int j = 0; j < size; j++)
      os << g.archi[i][j] << " ";
    os << std::endl;
    }
  return os;
}
#endif
