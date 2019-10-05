#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Nodo.h"
#include "VDinamico.h"

template <class T>
class ListaDEnlazada {
private:
    VDinamico<Nodo> vNodos;
public:
    ListaDEnlazada();
    ListaDEnlazada(const ListaDEnlazada& orig);
    virtual ~ListaDEnlazada();
private:

};

#endif /* LISTADENLAZADA_H */

