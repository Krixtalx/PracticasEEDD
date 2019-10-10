#ifndef NODO_H
#define NODO_H

#include <iostream>

template <class T>
class Nodo {
private:
	Nodo<T>* anterior;
	Nodo<T>* siguiente;
	T dato;
public:
	Nodo();
	Nodo(const Nodo& orig);
	virtual ~Nodo();

	Nodo<T>* GetAnterior() const;
	Nodo<T>* SetAnterior(Nodo<T>* anterior);
	Nodo<T>* GetSiguiente() const;
	Nodo<T>* SetSiguiente(Nodo<T>* siguiente);
	T GetDato() const;
	Nodo<T>* SetDato(T dato);

};
template<class T>
Nodo<T>::Nodo() {}

template<class T>
Nodo<T>::Nodo(const Nodo& orig) {}

template<class T>
Nodo<T>::~Nodo() {}

template <class T>
Nodo<T>* Nodo<T>::GetAnterior() const {
	return anterior;
}

template <class T>
Nodo<T>* Nodo<T>::SetAnterior(Nodo<T>* anterior) {
	this->anterior = anterior;
	return this;
}

template <class T>
Nodo<T>* Nodo<T>::GetSiguiente() const {
	return siguiente;
}

template <class T>
Nodo<T>* Nodo<T>::SetSiguiente(Nodo* siguiente) {
	this->siguiente = siguiente;
	return this;
}

template <class T>
T Nodo<T>::GetDato() const {
	return dato;
}

template <class T>
Nodo<T>* Nodo<T>::SetDato(T dato) {
	this->dato = dato;
	return this;
}

#endif /* NODO_H */