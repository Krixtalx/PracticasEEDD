#ifndef NODO_H
#define NODO_H

#include <iostream>



template <class T>
class Nodo {
private:
	Nodo<T>* anterior;
	Nodo<T>* siguiente;
	T dato;
	template<class T>
	friend class ListaDEnlazada;
public:
	Nodo();
	Nodo(T& _dato);
	Nodo(const Nodo& orig);
	virtual ~Nodo();

	Nodo<T>* GetAnterior() const;
	Nodo<T>* SetAnterior(Nodo<T>* anterior);
	Nodo<T>* GetSiguiente() const;
	Nodo<T>* SetSiguiente(Nodo<T>* siguiente);
	T& GetDato() const;
	Nodo<T>* SetDato(T dato);
};

/**
*@Brief Constructor por defecto
*/
template<class T>
Nodo<T>::Nodo() : anterior(0), siguiente(0) {}

/**
*@Brief Constructor parametrizado
*@param dato con el que crear el nodo
*/
template<class T>
Nodo<T>::Nodo(T& _dato) : dato(_dato), anterior(0), siguiente(0) {}

/**
*@Brief Constructor de copia
*/
template<class T>
Nodo<T>::Nodo(const Nodo& orig) {
	this->anterior = 0;
	this->siguiente = 0;
	this->dato = orig.dato;
}

/**
*@Brief Destructor
*/
template<class T>
Nodo<T>::~Nodo() {}

/**
*@Brief Getter del nodo anterior
*/
template <class T>
Nodo<T>* Nodo<T>::GetAnterior() const {
	return anterior;
}

/**
*@Brief Setter del nodo anterior
*@param Nodo que se desea poner como anterior
*/
template <class T>
Nodo<T>* Nodo<T>::SetAnterior(Nodo<T>* anterior) {
	this->anterior = anterior;
	return this;
}

/**
*@Brief Getter del nodo siguiente
*/
template <class T>
Nodo<T>* Nodo<T>::GetSiguiente() const {
	return siguiente;
}

/**
*@Brief Setter del nodo anterior
*@param Nodo que se desea poner como anterior
*/
template <class T>
Nodo<T>* Nodo<T>::SetSiguiente(Nodo* siguiente) {
	this->siguiente = siguiente;
	return this;
}

/**
*@Brief Getter del dato
*/
template <class T>
T& Nodo<T>::GetDato() const {
	return dato;
}

/**
*@Brief Setter del dato
*@param dato que se desea poner
*/
template <class T>
Nodo<T>* Nodo<T>::SetDato(T dato) {
	this->dato = dato;
	return this;
}

#endif /* NODO_H */