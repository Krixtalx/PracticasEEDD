#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include "Nodo.h"

/**
*@brief Clase iterador para ListaDEnlazada
*/
template <class T>
class Iterador {
	Nodo<T>* nodoApuntado;
	template <class T>
	friend class ListaDEnlazada;
public:
	Iterador();
	Iterador(Nodo<T>* nodo);
	~Iterador();
	Iterador<T>& operator=(Iterador<T>& right);
	Iterador<T>& operator++(int);
	Iterador<T>& operator--(int);
	bool final();
	Nodo<T>* getNodo();
};

// ============================================================================

template <class T>
class ListaDEnlazada {
private:
	Nodo<T>* cabecera;
	Nodo<T>* cola;
	unsigned int tam;

public:
	ListaDEnlazada();
	ListaDEnlazada(const ListaDEnlazada<T>& orig);
	ListaDEnlazada<T>& operator=(ListaDEnlazada<T>& right);
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
	ListaDEnlazada<T>& borra(Iterador<T>& iterador);
	ListaDEnlazada<T> concatena(const ListaDEnlazada<T>& otraLista);
	Iterador<T> iterador() const;
};

//=======================================================================================================

template<class T>
Iterador<T>::Iterador() : nodoApuntado(0) {
}

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
*@Brief Operador de asignacion
*/
template<class T>
Iterador<T>& Iterador<T>::operator=(Iterador<T>& right){
	if (this = &right)
		return *this;
	this->nodoApuntado = right.nodoApuntado;
	return *this;
}

/**
*@Brief Pasa al nodo siguiente del apuntado
*@throws std::overflow_error si el nodo apuntado no tiene siguiente y no es la cola de la lista
*/
template<class T>
Iterador<T>& Iterador<T>::operator++(int){
	if (nodoApuntado->siguiente!=0){
		nodoApuntado = nodoApuntado->siguiente;
		return *this;
	}
	else {
		throw std::overflow_error("[Iterador<T>::operator++]El nodo apuntado no tiene ningún otro como siguiente");
	}

}

/**
*@Brief Pasa al nodo anterior del apuntado
*@throws std::overflow_error si el nodo apuntado no tiene anterior y no es la cabecera de la lista
*/
template<class T>
Iterador<T>& Iterador<T>::operator--(int){
	if (nodoApuntado->anterior != 0) {
		nodoApuntado = nodoApuntado->anterior;
		return *this;
	}
	else {
		throw std::overflow_error("[Iterador<T>::operator--]El nodo apuntado no tiene ningún otro como anterior");
	}
}

/**
*	@brief Comprueba si se ha llegado al final de la lista
*	@return True si no quedan elementos por los que iterar. False en otro caso
*/
template <class T>
bool Iterador<T>::final() {
	return (nodoApuntado == 0);
}

template<class T>
Nodo<T>* Iterador<T>::getNodo(){
	return this->nodoApuntado;
}



// ========== INICIO IMPLEMENTACION ListaDEnlazada ==========



/**
*	@brief Constructor por defecto
*/
template <class T>
ListaDEnlazada<T>::ListaDEnlazada() : cabecera(0), cola(0), tam(0) {
}

/**
*	@brief Constructor de copia
*	@param orig Lista a copiar
*/
template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada& orig) : tam(orig.tam) {
	unsigned int tamAux = orig.tam;
	Nodo<T>* auxOrig = orig.cabecera;	
	Nodo<T>* auxCop=0;
	if (auxOrig != 0) {
		this->cabecera = new Nodo<T>(*auxOrig);
		auxCop = this->cabecera;
		while (tamAux > 1) {
			auxOrig = auxOrig->siguiente;
			auxCop->siguiente = new Nodo<T>(*auxOrig);
			auxCop->siguiente->anterior = auxCop;
			auxCop = auxCop->siguiente;
			tamAux--;
		}
		this->cola = auxCop;
	}
}

/**
	@brief Operador de asignacion
	@param right Lista a copiar
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(ListaDEnlazada<T>& right) {
	if (this == &right)
		return *this;
	Nodo<T>* aux;
	while (tam > 0) {
		aux = cola->anterior;
		delete cola;
		cola = aux;
		tam--;
	}

	unsigned int tamAux = right.tam;
	aux = right.cabecera;
	Nodo<T>* auxCop;
	this->cabecera = new Nodo<T>(*aux);
	auxCop = this->cabecera;
	while (tamAux > 1) {
		aux = aux->siguiente;
		auxCop->siguiente = new Nodo<T>(*aux);
		auxCop->siguiente->anterior = auxCop;
		auxCop = auxCop->siguiente;
		tamAux--;
	}
	this->cola = auxCop;
	this->tam = tamAux;
	return *this;
}

/**
	@brief Operador de asignacion
	@param right Lista a copiar
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada<T>& right) {
	if (this == &right)
		return *this;
	Nodo<T>* aux;
	while (tam > 0) {
		aux = cola->anterior;
		delete cola;
		cola = aux;
		tam--;
	}

	unsigned int tamAux = right.tam;
	aux = right.cabecera;
	Nodo<T>* auxCop;
	this->cabecera = new Nodo<T>(*aux);
	auxCop = this->cabecera;
	while (tamAux > 1) {
		aux = aux->siguiente;
		auxCop->siguiente = new Nodo<T>(*aux);
		auxCop->siguiente->anterior = auxCop;
		auxCop = auxCop->siguiente;
		tamAux--;
	}
	this->cola = auxCop;
	this->tam = tamAux;
	return *this;
}

/**
*@Brief Destructor de ListaDEnlazada
*/
template<class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
	Nodo<T>* aux;
	while (tam > 0) {
		aux = cola->anterior;
		delete cola;
		cola = aux;
		tam--;
	}
}

/**
	@brief Devuelve una referencia al dato que almacena el primer nodo de la lista
	@throws runtime_error Si no hay primer nodo
*/
template<class T>
T& ListaDEnlazada<T>::Inicio() {
	if (cabecera == 0)
		throw std::runtime_error("[ListaDEnlaza<T>Inicio()] No hay nodo en el inicio");
	return cabecera->dato;
}

/**
	@brief Devuelve una referencia al dato que almacena el ultimo nodo de la lista
	@throws runtime_error Si no hay ultimo nodo
*/
template<class T>
T& ListaDEnlazada<T>::Final() {
	if (cabecera == 0)
		throw std::runtime_error("[ListaDEnlaza<T>Inicio()] No hay nodo en el final");
	return cola->dato;
}

template<class T>
unsigned int ListaDEnlazada<T>::getTam() {
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
		nuevo->siguiente = cabecera;
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
	Nodo<T>* nuevo = new Nodo<T>(dato);
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
*@Brief Inserta un nuevo nodo entre dos nodos de la lista
*@param Iterador que apunta al nodo siguiente
*@param Dato del nodo que se va a insertar
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::inserta(Iterador<T>& iterador, T& dato) {
	if (iterador.nodoApuntado) {
		this->insertaFinal(dato);
		return *this;
	}
	Nodo<T>* nuevoNodo = new Nodo<T>(dato);
	nuevoNodo->siguiente = iterador.nodoApuntado;
	nuevoNodo->anterior = iterador.nodoApuntado->anterior;
	iterador.nodoApuntado->anterior->siguiente = nuevoNodo;
	iterador.nodoApuntado->anterior = nuevoNodo;
	tam++;
	return *this;
}

/**
*@Brief Borra el nodo que se encuentra al principio de la lista
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::borraInicio() {
	cabecera = cabecera->siguiente;
	delete cabecera->anterior;
	cabecera->anterior = 0;
	tam--;
	return *this;
}

/**
*@Brief Borra el nodo que se encuentra al final de la lista
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::borrarFinal() {
	cola = cola->anterior;
	delete cola->siguiente;
	cola->siguiente = 0;
	tam--;
	return *this;
}

/**
	@brief Borra un nodo cualquiera de la lista
	@param Iterador que apunta al nodo a borrar
	@throws logic_error Si el iterador no apunta a un nodo
*/
template<class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::borra(Iterador<T>& iterador)
{
	if (!iterador.nodoApuntado)
		throw std::logic_error("[ListaDEnlazada<T>::borra()] El iterador no apunta a ningun nodo");
	if (iterador.nodoApuntado == cabecera) {
		this->borraInicio();
		return *this;
	}
	else if (iterador.nodoApuntado == cola) {
		this->borrarFinal();
		return *this;
	}
	iterador.nodoApuntado->anterior->siguiente = iterador.nodoApuntado->siguiente;
	iterador.nodoApuntado->siguiente->anterior = iterador.nodoApuntado->anterior;
	delete iterador.nodoApuntado;
	tam--;
	return *this;
}

/**
*@Brief Crea una nueva lista resultante de concatenar *this con otraLista
*@param Lista con la que concatenar
*/
template<class T>
ListaDEnlazada<T> ListaDEnlazada<T>::concatena(const ListaDEnlazada<T>& otraLista) {
	ListaDEnlazada<T> temp(*this);
	Iterador<T> iteraOtra = otraLista.iterador();
	while(!iteraOtra.final()) {
		temp.insertaFinal(iteraOtra.nodoApuntado->dato);
		iteraOtra++;
	}
	return temp;
}

/**
	@brief Devuelve un iterador apuntando a la cabecera de la lista
*/
template<class T>
Iterador<T> ListaDEnlazada<T>::iterador() const{
	return Iterador<T>(this->cabecera);
}

#endif /* LISTADENLAZADA_H */