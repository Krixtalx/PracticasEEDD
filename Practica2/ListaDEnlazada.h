#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Nodo.h"

template <class T>
class ListaDEnlazada {
private:
	Nodo<T>* cabecera;
	Nodo<T>* cola;
	bool estaVacia;
	friend class Nodo<T>;
public:
	ListaDEnlazada();
	ListaDEnlazada(const ListaDEnlazada& orig);
	ListaDEnlazada<T>& operator=(const ListaDEnlazada<T>& right);
	virtual ~ListaDEnlazada();
	ListaDEnlazada<T>& insertaInicio(T& dato);
	ListaDEnlazada<T>& insertaFinal(T& dato);
	ListaDEnlazada<T>& borraInicio();
	ListaDEnlazada<T>& borrarFinal();
	ListaDEnlazada<T>& concatena(const ListaEnlazada<T>& otraLista);
};

/**
	@brief Constructor por defecto
*/
template <class T>
ListaDEnlazada<T>::ListaDEnlazada() : cabezera(0), cola(0), estaVacia(true) {
}

/**
	@brief Constructor de copia
	@param orig Lista a copiar
*/
template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada& orig) {
	//TODO: implementar copia (this->insertarFinal())
	
}

template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::insertaInicio(T& dato) {
	Nodo<T>* nuevo = new Nodo<T>(dato);
	if (this->estaVacia) {
		this->cabecera = nuevo;
		this->cola = nuevo;
	}
	else {
		nuevo.siguiente = this->cabecera;
		this->cabecera->anterior = nuevo;
		this->cabecera = nuevo;
		
	}
}

template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::insertaFinal(T& dato) {
	Nodo<T>* nuevo = new nodo <T>;
		if (this->estaVacia) {
		this->cabecera = nuevo;
		this->cola = nuevo;
	}
	else {
		nuevo.siguiente = 0;
		this->cola->siguiente = nuevo;
		this->cola = nuevo;
	}
		
	
}

#endif /* LISTADENLAZADA_H */