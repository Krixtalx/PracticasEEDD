#ifndef NODOAVL_H
#define NODOAVL_H

#include <iostream>

template <class T>
class NodoAVL {
private:
	NodoAVL<T>* izq;
	NodoAVL<T>* der;
	T dato;
	char bal = 0;
	int altura = 0;
	template<class T>
	friend class AVL;
public:
	NodoAVL();
	NodoAVL(T& _dato);
	NodoAVL(const NodoAVL<T>& orig);
	virtual ~NodoAVL();
	NodoAVL<T>& operator=(const NodoAVL<T>* right);
	NodoAVL<T>* GetIzq() const;
	NodoAVL<T>* SetIzq(NodoAVL<T>* izq);
	NodoAVL<T>* GetDer() const;
	NodoAVL<T>* SetDer(NodoAVL<T>* der);
	T& GetDato();
	NodoAVL<T>* SetDato(T dato);
	std::string toCSV();
};

/**
*@Brief Constructor por defecto
*/
template<class T>
NodoAVL<T>::NodoAVL() : izq(0), der(0) {}

/**
*@Brief Constructor parametrizado
*@param dato con el que crear el nodo
*/
template<class T>
NodoAVL<T>::NodoAVL(T& _dato) : dato(_dato), izq(0), der(0) {}

/**
*@Brief Constructor de copia
*/
template<class T>
NodoAVL<T>::NodoAVL(const NodoAVL<T>& orig) {
	this->izq = 0;
	this->der = 0;
	this->dato = orig.dato;
}

/**
*@Brief Destructor
*/
template<class T>
NodoAVL<T>::~NodoAVL() {}

/**
	@brief Operador de asignacion
*/
template<class T>
NodoAVL<T>& NodoAVL<T>::operator=(const NodoAVL<T>* right)
{
	if (this = right)
		return *this;
	this->izq = right->izq;
	this->der = right->der;
	this->dato = right->dato;
	return *this;
}

/**
*@Brief Getter del nodo izquierdo
*/
template <class T>
NodoAVL<T>* NodoAVL<T>::GetIzq() const {
	return izq;
}

/**
*@Brief Setter del nodo izquierdo
*@param Nodo que se desea poner a la izquierda
*/
template <class T>
NodoAVL<T>* NodoAVL<T>::SetIzq(NodoAVL<T>* izq) {
	this->izq = izq;
	bal++;
	return this;
}

/**
*@Brief Getter del nodo derecho
*/
template <class T>
NodoAVL<T>* NodoAVL<T>::GetDer() const {
	return der;
}

/**
*@Brief Setter del nodo derecho
*@param Nodo que se desea poner a la derecha
*/
template <class T>
NodoAVL<T>* NodoAVL<T>::SetDer(NodoAVL<T>* der) {
	this->der = der;
	bal--;
	return this;
}

/**
*@Brief Getter del dato
*/
template <class T>
T& NodoAVL<T>::GetDato() {
	return dato;
}

/**
*@Brief Setter del dato
*@param dato que se desea poner
*/
template <class T>
NodoAVL<T>* NodoAVL<T>::SetDato(T dato) {
	this->dato = dato;
	return this;
}

/**
*@Brief Pasa el dato a CSV
*@Prev La clase del dato debe tener implementado un metodo toCSV()
*/
template<class T>
std::string NodoAVL<T>::toCSV()
{
	return dato.toCSV();
}

#endif /* NODO_H */