#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Nodo.h"

template <class T>
class ListaDEnlazada {
private:
    Nodo<T> cabecera;
    Nodo<T> cola;
public:
    ListaDEnlazada();
    ListaDEnlazada(const ListaDEnlazada& orig);
    ListaDEnlazada<T>& operator=(const ListaDEnlazada<T>& right);
    virtual ~ListaDEnlazada();
};

#endif /* LISTADENLAZADA_H */