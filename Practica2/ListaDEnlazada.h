#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Nodo.h"

/**
*@brief Clase iterador para ListaDEnlazada
*/
template <class T>
class Iterador {
	Nodo<T>* nodoApuntado;
	friend class ListaDEnlazada;
public:
	Iterador(Nodo<T>* nodo);
	~Iterador();
	bool final();
	void siguienteNodo();
	void anteriorNodo();
};

// ============================================================================

template <class T>
class ListaDEnlazada {
private:
	Nodo<T>* cabecera;
	Nodo<T>* cola;
	Iterador<T> IteradorLista;
	unsigned int tam;
	friend class Nodo;

public:
	ListaDEnlazada();
	ListaDEnlazada(const ListaDEnlazada& orig);
	ListaDEnlazada<T>& operator=(const ListaDEnlazada<T>& right);
	virtual ~ListaDEnlazada();
	T& Inicio();
	T& Final();
	unsigned int getTam();
	ListaDEnlazada<T>& insertaInicio(T& dato);
	ListaDEnlazada<T>& insertaFinal(T& dato);
	ListaDEnlazada<T>& inserta(Iterador<T>& iterador, T& dato);
	ListaDEnlazada<T>& borraInicio();
	ListaDEnlazada<T>& borrarFinal();
	ListaDEnlazada<T>& concatena(const ListaDEnlazada<T>& otraLista);
};

//=======================================================================================================

/**
*	@brief Constructor parametrizado
*	@param nodo Cabecera de la lista
*	@post Crea un iterador apuntando a la cabecera de una lista
*/
template <class T>
Iterador<T>::Iterador(Nodo<T>* nodo) : nodoApuntado(nodo) {
}

/**
*	@brief Destructor
*/
template <class T>
Iterador<T>::~Iterador() {
}

/**
*	@brief Comprueba si se ha llegado al final de la lista
*	@return True si no quedan elementos por los que iterar. False en otro caso
*/
template <class T>
bool Iterador<T>::final() {
	return (nodoApuntado == 0);
}

/**
*	@brief Itera al siguiente nodo de la lista
*/
template <class T>
void Iterador<T>::siguienteNodo() {
	nodoApuntado = nodoApuntado->siguiente;
}

/**
*	@brief Itera al nodo anterior de la lista
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
	unsigned int tamAux = orig.tam;
	Nodo<T>* auxOrig = orig.cabecera;
	Nodo<T>* auxCop;
	this->cabecera = new Nodo<T>(auxOrig);
	auxCop = this->cabecera;
	while (tamAux > 0) {
		aux = aux->siguiente;
		auxCop->siguiente = new Nodo<T>(aux);
		auxCop->siguiente->anterior = auxCop;
		auxCop = auxCop->siguiente;
		tam--;
	}
	this->cola = auxCop;
}

/**
	@brief Operador de asignacion
	@param right Lista a copiar
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada<T>& right){
	Nodo<T>* aux;
	while (tam > 0) {
		aux = cola->anterior;
		delete cola;
		cola = aux;
		tam--;
	}

	unsigned int tamAux = right.tam;
	Nodo<T>* auxOrig = right.cabecera;
	Nodo<T>* auxCop;
	this->cabecera = new Nodo<T>(auxOrig);
	auxCop = this->cabecera;
	while (tamAux > 0) {
		aux = aux->siguiente;
		auxCop->siguiente = new Nodo<T>(aux);
		auxCop->siguiente->anterior = auxCop;
		auxCop = auxCop->siguiente;
		tam--;
	}
	this->cola = auxCop;
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

template<class T>
T& ListaDEnlazada<T>::Inicio(){
	return cabecera->dato;
}

template<class T>
T& ListaDEnlazada<T>::Final(){
	return cola->dato;
}

template<class T>
unsigned int ListaDEnlazada<T>::getTam(){
	return tam;
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
	tam++;
	return *this;
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
	return *this;
}

/**
*@Brief Sustituye el dato del nodo apuntado por el Iterador
*@param Iterador que apunta al nodo
*@param Dato con el que se va a sustituir
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::inserta(Iterador<T>& Iterador, T& dato){
	Iterador.nodoApuntado->SetDato(dato);
	return *this;
}

/**
*@Brief Borra el dato que se encuentra al principio de la lista
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::borraInicio(){
	cabecera = cabecera->siguiente;
	delete cabecera->anterior;
	cabecera->anterior = 0;
	tam--;
	return *this;
}

/**
*@Brief Borra el dato que se encuentra al final de la lista
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::borrarFinal(){
	cola = cola->anterior;
	delete cola->siguiente;
	cola->siguiente = 0;
	tam--;
	return *this;
}

/**
*@Brief Enlaza el final de la lista que ejecuta el método con el principio de la lista que se pasa como parametro
*@param Lista con la que concatenar
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::concatena(const ListaDEnlazada<T>& otraLista){
	this->cola->siguiente = otraLista.cabecera;
	this->cola->siguiente->anterior = cola;
	this->cola = otraLista.cola;
	return *this;
}

#endif /* LISTADENLAZADA_H */