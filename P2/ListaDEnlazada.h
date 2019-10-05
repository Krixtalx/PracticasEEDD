#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Nodo.h"
#include "VDinamico.h"

template <class T>
class ListaDEnlazada {
private:
    VDinamico<Nodo<T>> vNodos;
    Nodo<T> cabecera;
    Nodo<T> cola;
public:
    ListaDEnlazada();
    ListaDEnlazada(const ListaDEnlazada& orig);
    ListaDEnlazada<T>& operator=(const ListaDEnlazada<T>& right);
    virtual ~ListaDEnlazada();
};


#endif /* LISTADENLAZADA_H */