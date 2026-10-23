// Autor: Hector Gassan

#ifndef DLIST_H
#define DLIST_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class T> class DLink {
public:
  T value;
  DLink<T> *next;
  DLink<T> *previous;

  DLink(T val);
  DLink(T val, DLink<T> *nxt, DLink<T> *prev);
};

template <class T>
DLink<T>::DLink(T val) : value(val), next(NULL), previous(NULL) {}

template <class T>
DLink<T>::DLink(T val, DLink<T> *nxt, DLink<T> *prev)
    : value(val), next(nxt), previous(prev) {}

template <class T> class DList {
private:
  DLink<T> *head;
  DLink<T> *tail;
  int size;

public:
  DList();
  ~DList();

  void insertion(T val);
  int search(T val) const;
  void update(int pos, T val);
  T deleteAt(int pos);
  string toStringForward() const;
  string toStringBackward() const;
  void printList();
  void saveToFile(string filename) const;
  void loadFromFile(string filename);
};

template <class T> DList<T>::DList() : head(NULL), tail(NULL), size(0) {}

template <class T> DList<T>::~DList() {
  head = NULL;
  tail = NULL;
  size = 0;
}

template <class T> void DList<T>::insertion(T val) {
  DLink<T> *nuevo_nodo = new DLink<T>(val);
  // Si la lista esta vacia
  if (size == 0) {
    tail = nuevo_nodo;
    head = nuevo_nodo;
  } else {
    tail->next = nuevo_nodo;
    nuevo_nodo->previous = tail;
    tail = nuevo_nodo;
  }
  size++;
}

template <class T> int DList<T>::search(T val) const {
  DLink<T> *nodo_prueba;
  nodo_prueba = head;
  for (int i = 0; i < size; i++) {
    if (nodo_prueba->value == val) {
      return i;
    }
    nodo_prueba = nodo_prueba->next;
  }
  return -1;
}

template <class T> void DList<T>::update(int pos, T val) {
  // Si la posicion es invalida o lista vacia
  if (pos < 0 || pos >= size) {
    return;
  }
  DLink<T> *nodo_prueba;
  nodo_prueba = head;
  for (int i = 0; i < pos; i++) {
    nodo_prueba = nodo_prueba->next;
  }
  nodo_prueba->value = val;
}

template <class T> T DList<T>::deleteAt(int pos) {
  // Si la posicion es íinvalida o lista vacia
  if (pos < 0 || pos >= size) {
    return T();
  }
  DLink<T> *nodo_prueba = head;
  DLink<T> *nodo_anterior;
  DLink<T> *nodo_siguente;
  T valor_borrado;
  // Si la posicion es la primera
  if (pos == 0) {
    valor_borrado = head->value;
    // Si la lista solo tiene un elemento
    if (size == 1) {
      head = NULL;
      tail = NULL;
      // Si la posicion es la primera y tiene mas elementos
    } else {
      head = head->next;
      head->previous = NULL;
    }
    // Si la posicion es la ultima
  } else if (pos == size - 1) {
    for (int i = 0; i < pos; i++) {
      nodo_prueba = nodo_prueba->next;
    }
    valor_borrado = nodo_prueba->value;
    nodo_anterior = nodo_prueba->previous;
    tail = nodo_anterior;
    nodo_anterior->next = NULL;
    // Si la posicion esta entre la primera y la ultima (caso general)
  } else {
    for (int i = 0; i < pos; i++) {
      nodo_prueba = nodo_prueba->next;
    }
    valor_borrado = nodo_prueba->value;
    nodo_anterior = nodo_prueba->previous;
    nodo_siguente = nodo_prueba->next;
    nodo_anterior->next = nodo_siguente;
    nodo_siguente->previous = nodo_anterior;
  }
  size--;
  delete nodo_prueba;
  return valor_borrado;
}

template <class T> string DList<T>::toStringForward() const {
  stringstream aux;
  DLink<T> *p;

  p = head;
  aux << "[";
  while (p != NULL) {
    aux << p->value;
    if (p->next != NULL) {
      aux << ", ";
    }
    p = p->next;
  }
  aux << "]";
  return aux.str();
}

template <class T> string DList<T>::toStringBackward() const {
  stringstream aux;
  DLink<T> *p;

  p = tail;
  aux << "[";
  while (p != NULL) {
    aux << p->value;
    if (p->previous != NULL) {
      aux << ", ";
    }
    p = p->previous;
  }
  aux << "]";
  return aux.str();
}

template <class T> void DList<T>::printList() {
  DLink<T> *nodo_prueba;
  nodo_prueba = head;
  int i = 1;
  while (nodo_prueba != NULL) {
    std::cout << i << ".-" << nodo_prueba->value << std::endl;
    nodo_prueba = nodo_prueba->next;
    i++;
  }
}

// Metodos para abrir y guardar informacion de la estructura de datos en un
// archivo

template <class T> void DList<T>::saveToFile(string filename) const {
  ofstream archivo(filename);
  DLink<T> *nodo_prueba = head;
  while (nodo_prueba != NULL) {
    archivo << nodo_prueba->value << "\n";
    nodo_prueba = nodo_prueba->next;
  }
}

template <class T> void DList<T>::loadFromFile(string filename) {
  ifstream archivo(filename);
  T valor;
  while (getline(archivo, valor)) {
    insertion(valor);
  }
}

#endif
