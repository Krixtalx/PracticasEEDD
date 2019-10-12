#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Nodo.h"

template <class T>
class ListaDEnlazada {
private:
	Nodo<T>* cabecera;
	Nodo<T>* cola;
	int tam;
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
	ListaDEnlazada<T>& concatena(const ListaDEnlazada<T>& otraLista);
	Iterador<T> iteradorInicio();
};

/**
	@brief Clase iterador para ListaDEnlazada
*/
template <class T>
class Iterador {
	Nodo<T>* nodoApuntado;
	friend class ListaDEnlazada<T>;
public:
	Iterador(Nodo<T>* nodo);
	~Iterador();
	bool final();
	void siguienteNodo();
	void anteriorNodo();
};

/**
	@brief Constructor parametrizado
	@param nodo Cabecera de la lista
	@post Crea un iterador apuntando a la cabecera de una lista
*/
template <class T>
Iterador<T>::Iterador(Nodo<T>* nodo) : nodoApuntado(nodo) {
}

/**
	@brief Destructor
*/
template <class T>
Iterador<T>::~Iterador() {
}

/**
	@brief Comprueba si se ha llegado al final de la lista
	@return True si no quedan elementos por los que iterar. False en otro caso
*/
template <class T>
bool Iterador<T>::final() {
	return (nodoApuntado == 0);
}

/**
	@brief Itera al siguiente nodo de la lista
*/
template <class T>
void Iterador<T>::siguienteNodo() {
	nodoApuntado = nodoApuntado->siguiente;
}

/**
	@brief Itera al nodo anterior de la lista
*/
template <class T>
void Iterador<T>::anteriorNodo() {
	nodoApuntado = nodoApuntado->anterior;
}

// ========== INICIO IMPLEMENTACION ListaDEnlazada ==========

/**
	@brief Constructor por defecto
*/
template <class T>
ListaDEnlazada<T>::ListaDEnlazada() : cabezera(0), cola(0), tam(0) {
}

/**
*	@brief Constructor de copia
*	@param orig Lista a copiar
*/
template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada& orig) {
	//TODO: implementar copia (this->insertarFinal())

}

/**
	@brief Operador de asignacion
	@param right Lista a copiar
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada<T>& right)
{
	// TODO: Implementar asignacion
}

/**
*@Brief Destructor de ListaDEnlazada
*/
template<class T>
ListaDEnlazada<T>::~ListaDEnlazada(){
	Nodo<T>* aux;
	while (tam > 0) {
		aux = cola->anterior;
		delete cola;
		cola = aux;
		tam--;
	}
}

/**
*@Brief Inserta un dato en el inicio de la Lista
*@param Dato que debe de llevar el nodo a insertar
*/
template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::insertaInicio(T& dato) {
	Nodo<T>* nuevo = new Nodo<T>(dato);
	if (tam == 0) {
		cabecera = nuevo;
		cola = nuevo;
	}
	else {
		nuevo.siguiente = cabecera;
		cabecera->anterior = nuevo;
		cabecera = nuevo;
	}
	tam++
}

/**
*@Brief Inserta un dato en el final de la Lista
*@param Dato que debe de llevar el nodo a insertar
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::insertaFinal(T& dato) {
	Nodo<T>* nuevo = new nodo <T>;
	if (tam == 0) {
		cabecera = nuevo;
		cola = nuevo;
	}
	else {
		cola->siguiente = nuevo;
		nuevo->anterior = cola;
		cola = nuevo;
	}
	tam++;
}

/**
	@brief Elimina el primer nodo de la lista
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::borraInicio()
{
	cabecera = cabecera.siguiente;
	delete cabecera->anterior;
	cabecera->anterior = 0;
	tam--;
	
}

/**
	@brief Elimina el ultimo nodo de la lista
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::borrarFinal()
{
	cola = cola->anterior;
	delete cola->siguiente;
	cola->siguiente = 0;
	tam--;
}

/**
	@brief Concatena una lista a *this
	@param otraLista Lista a concatenar
	@pro Los nodos de otraLista se añaden al final de *this
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::concatena(const ListaDEnlazada<T>& otraLista)
{
	while(otraLista.tam)
	{
		this->insertaFinal(otraLista.cola->dato);
		otraLista.borrarFinal();
	}
}

#endif /* LISTADENLAZADA_H */