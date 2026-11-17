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
  T value; // O(1) - Constante
  DLink<T> *next; // O(1) - Constante
  DLink<T> *previous; // O(1) - Constante

  DLink(T val); // O(1) - Constante
  DLink(T val, DLink<T> *nxt, DLink<T> *prev); // O(1) - Constante
};

template <class T>
DLink<T>::DLink(T val) : value(val), next(NULL), previous(NULL) {} // O(1) - Constante

template <class T>
DLink<T>::DLink(T val, DLink<T> *nxt, DLink<T> *prev)
    : value(val), next(nxt), previous(prev) {} // O(1) - Constante

template <class T> class DList {
private:
  DLink<T> *head; // O(1) - Constante
  DLink<T> *tail; // O(1) - Constante
  int size; // O(1) - Constante

public:
  DList(); // O(1) - Constante
  ~DList(); // O(1) - Constante

  void insertion(T val);
  T deleteAt(int pos);
  T searchPos(int pos);
  int searchString(string val);
  void printList();
  void saveToFile(string filename) const;
  void loadFromFile(string filename);
};

template <class T> DList<T>::DList() : head(NULL), tail(NULL), size(0) {} // O(1) - Constante

template <class T> DList<T>::~DList() { // Complejidad general de la función: O(1) - Constante
  head = NULL; // O(1) - Constante
  tail = NULL; // O(1) - Constante
  size = 0; // O(1) - Constante
}

template <class T> int DList<T>::searchString(string val) { // Complejidad general de la función: O(1) mejor, O(N) promedio, O(N) peor
  DLink<T> *nodo_prueba; // O(1) - Constante
  nodo_prueba = head; // O(1) - Constante
  // Contador de canciones encontradas
  int ret = 0; // O(1) - Constante
  for(char &letra : val) { // O(N) - Lineal
      // Paso string dado a minusculas
      letra = tolower(letra); // O(1) - Constante
  }
  for (int i = 0; i < size; i++) { // O(N) - Lineal
    string strtest = nodo_prueba -> value; // O(1) - Constante
    for(char &letra : strtest){ // O(M) donde M es la longitud del string, en la práctica O(1)
        // Paso string de info de la cancion a minusculas
        letra = tolower(letra); // O(1) - Constante
    }
    // Uso funcion find de string para encontrar coincidencias
    if (strtest.find(val) != string::npos){ // O(1) - Constante
        cout << i + 1 << ".-" << nodo_prueba -> value << endl; // O(1) - Constante
        ret ++; // O(1) - Constante
    }
    nodo_prueba = nodo_prueba->next; // O(1) - Constante
  }
  return ret; // O(1) - Constante
}

template <class T> void DList<T>::insertion(T val) { // Complejidad general de la función: O(1) - Constante
  DLink<T> *nuevo_nodo = new DLink<T>(val); // O(1) - Constante
  // Si la lista esta vacia
  if (size == 0) { // O(1) - Constante
    tail = nuevo_nodo; // O(1) - Constante
    head = nuevo_nodo; // O(1) - Constante
  } else {
    tail->next = nuevo_nodo; // O(1) - Constante
    nuevo_nodo->previous = tail; // O(1) - Constante
    tail = nuevo_nodo; // O(1) - Constante
  }
  size++; // O(1) - Constante
}

template<class T> T DList<T>::searchPos(int pos){ // Complejidad general de la función: O(1) mejor, O(N) promedio, O(N) peor
    if(pos < 0 || pos >= size){ // O(1) - Constante
            return "Invalid"; // O(1) - Constante
    }
    DLink<T> *nodo_prueba; // O(1) - Constante
    nodo_prueba = head; // O(1) - Constante
    for(int i = 0; i < pos; i++ ){ //O(N) - Lineal
        nodo_prueba = nodo_prueba -> next; // O(1) - Constante
    }
    return nodo_prueba -> value; // O(1) - Constante
}


template <class T> T DList<T>::deleteAt(int pos) { // Complejidad general de la función: O(1) mejor, O(N) promedio, O(N) peor
  // Si la posicion es íinvalida o lista vacia
  if (pos < 0 || pos >= size) { // O(1) - Constante
    return T(); // O(1) - Constante
  }
  DLink<T> *nodo_prueba = head; // O(1) - Constante
  DLink<T> *nodo_anterior; // O(1) - Constante
  DLink<T> *nodo_siguente; // O(1) - Constante
  T valor_borrado; // O(1) - Constante
  // Si la posicion es la primera
  if (pos == 0) { // O(1) - Constante
    valor_borrado = head->value; // O(1) - Constante
    // Si la lista solo tiene un elemento
    if (size == 1) { // O(1) - Constante
      head = NULL; // O(1) - Constante
      tail = NULL; // O(1) - Constante
      // Si la posicion es la primera y tiene mas elementos
    } else {
      head = head->next; // O(1) - Constante
      head->previous = NULL; // O(1) - Constante
    }
    // Si la posicion es la ultima
  } else if (pos == size - 1) { // O(1) - Constante
    for (int i = 0; i < pos; i++) { //O(N) - Lineal
      nodo_prueba = nodo_prueba->next; // O(1) - Constante
    }
    valor_borrado = nodo_prueba->value; // O(1) - Constante
    nodo_anterior = nodo_prueba->previous; // O(1) - Constante
    tail = nodo_anterior; // O(1) - Constante
    nodo_anterior->next = NULL; // O(1) - Constante
    // Si la posicion esta entre la primera y la ultima (caso general)
  } else {
    for (int i = 0; i < pos; i++) { //O(N) - Lineal
      nodo_prueba = nodo_prueba->next; // O(1) - Constante
    }
    valor_borrado = nodo_prueba->value; // O(1) - Constante
    nodo_anterior = nodo_prueba->previous; // O(1) - Constante
    nodo_siguente = nodo_prueba->next; // O(1) - Constante
    nodo_anterior->next = nodo_siguente; // O(1) - Constante
    nodo_siguente->previous = nodo_anterior; // O(1) - Constante
  }
  size--; // O(1) - Constante
  delete nodo_prueba; // O(1) - Constante
  return valor_borrado; // O(1) - Constante
}


template <class T> void DList<T>::printList() { // Complejidad general de la función : O(N) - Lineal
  DLink<T> *nodo_prueba; // O(1) - Constante
  nodo_prueba = head; // O(1) - Constante
  int i = 1; // O(1) - Constante
  while (nodo_prueba != NULL) { //O(N) - Lineal
    std::cout << i << ".-" << nodo_prueba->value << std::endl; // O(1) - Constante
    nodo_prueba = nodo_prueba->next; // O(1) - Constante
    i++; // O(1) - Constante
  }
}

// Metodos para abrir y guardar informacion de la estructura de datos en un
// archivo

template <class T> void DList<T>::saveToFile(string filename) const { // Complejidad general de la función : O(N) - Lineal
  ofstream archivo(filename); // O(1) - Constante
  DLink<T> *nodo_prueba = head; // O(1) - Constante
  while (nodo_prueba != NULL) { //O(N) - Lineal
    archivo << nodo_prueba->value << "\n"; // O(1) - Constante
    nodo_prueba = nodo_prueba->next; // O(1) - Constante
  }
}

template <class T> void DList<T>::loadFromFile(string filename) { // Complejidad general de la función : O(N) - Lineal
  ifstream archivo(filename); // O(1) - Constante
  T valor; // O(1) - Constante
  while (getline(archivo, valor)) { //O(N) - Lineal
    insertion(valor); // O(1) - Constante
  }
}

#endif
