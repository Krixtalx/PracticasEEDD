#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "NodoAVL.h"

//TODO: LA PRACTICA

template <class T>
class AVL{
private:
	NodoAVL<T>* raiz;
	unsigned int alt;
	unsigned int tam;
	void rotarIzquierda(NodoAVL<T>*& nodo);
	void rotarDerecha(NodoAVL<T>*& nodo);

public:
	AVL();
	AVL(const AVL<T>& orig);
	~AVL();
	AVL<T>& operator=(const AVL<T>& right);
	void recorreInorden(NodoAVL<T>* n);
	unsigned int numElementos();
	unsigned int altura();
	NodoAVL<T>* getRaiz();
	bool busca(T& dato, T& resultado);
	bool buscaIt(T& dato, T& resultado);
	bool inserta(T& dato, NodoAVL<T>* &n);
	//TODO: Implementa ahora todo eso, fiera
};

/**
	@brief Constructor por defecto
*/
template<class T>
AVL<T>::AVL(): raiz(0), alt(0), tam(0){

}

/**
	@brief Constructor por copia
	@param orig Objeto del que se copian los nodos
*/
template<class T>
AVL<T>::AVL(const AVL<T>& orig): raiz(orig.raiz), alt(orig.alt), tam(orig.tam)
{
	//TODO: copiar nodos
}

/**
	@brief Destructor
*/
template<class T>
AVL<T>::~AVL()
{
	//TODO: destruir nodos
}

template<class T>
AVL<T>& AVL<T>::operator=(const AVL<T>& right) 
{
	//TODO: asignar
}

/**
	@brief Muestra el contenido del arbol recorriendolo mediante inorden
	@param n Nodo incial del arbol
	@pre La clase T debe tener sobrecargado el operador <<
*/
template<class T>
void AVL<T>::recorreInorden(NodoAVL<T>* n)
{
	//TODO: exceción si n = 0
	if (n->izq)
		recorreInorden(n->izq);
	if (n->der)
		recorreInorden(n->der);

	std::cout << n->dato << std::endl;

}

template<class T>
unsigned int AVL<T>::numElementos()
{
	return tam;
}

template<class T>
unsigned int AVL<T>::altura()
{
	return alt;
}

template<class T>
NodoAVL<T>* AVL<T>::getRaiz()
{
	return this->raiz;
}

/**
	@brief Rota el nodo actual hacia la izquierda
	@param nodo Nodo a rotar
	@post El nodo indicado queda como hijo izquierdo de su subarbol derecho
*/
template<class T>
void AVL<T>::rotarIzquierda(NodoAVL<T>* &nodo)
{
	NodoAVL<T>* temp = nodo;
	nodo = nodo->der;          //Asigna a nodo su subarbol derecho
	temp->der = nodo->izq;     //Asigna a la derecha del nodo original el subarbol izquierdo de nodo
	nodo->izq = temp;          //Asgina el nodo original actualizado a la izquierda de nodo
	temp->bal++;
	if (nodo->bal < 0)         //Si nodo tenia mayor altura por la derecha
		temp->bal -= nodo->bal;  //entonces la descuenta del nodo original
	nodo->bal++;
	if (temp->bal > 0)         //Si el nodo original tenia mayor altura por la izquierda
		nodo->bal += temp->bal;  //entonces se le asigna a nodo
}

/**
	@brief Rota el nodo actual hacia la derecha
	@param nodo Nodo a rotar
	@post El nodo indicado queda como hijo derecho de su subarbol izquierdo
*/
template<class T>
void AVL<T>::rotarDerecha(NodoAVL<T>*& nodo)
{
	NodoAVL<T>* temp = nodo;
	nodo = nodo->izq;          //Asigna a nodo su subarbol izquierdo
	temp->izq = nodo->der;     //Asigna a la izquierda del nodo original el subarbol derecho de nodo
	nodo->der = temp;          //Asigna el nodo original actualizado a la derecha de nodo
	temp->bal--;
	if (nodo->bal > 0)         //Si nodo tenia mayor altura por la izquierda
		temp->bal -= nodo->bal;  //entonces la descuenta del nodo original
	nodo->bal--;
	if (temp->bal < 0)         //Si el nodo original tenia mayor altura por la derecha
		nodo->bal += temp->bal;  //entonces se le asigna a nodo
}

/**
	@brief Inserta el dato indicado en el arbol
	@param dato Dato a insertar
	@param n Nodo donde se intenta insertar el dato
	@pre La clase T debe tener sobrecargado el operador <
	@post El dato queda insertado en una hoja del arbol siguiendo la estructura de un ABB
	@return true Si se ha podido insertar el dato
*/
template<class T>
bool AVL<T>::inserta(T& dato, NodoAVL<T>*& n)
{
	if (!n) {                                         //Si no hay nodo, inserta el dato
		n = new NodoAVL<T>(dato);
		n->bal = 0;
		return true;
	}
	else if (dato < n->dato) {                        //Si el dato es menor,
		if (inserta(dato, n->izq)){                     //si ha podido insertarlo en el nodo izquierdo
			n->bal++;                                     //ajusta el balance del nodo,
			if (n->bal == 2) {                            //si el balance es incorrecto
				if (n->izq->bal == -1)                      //comprueba el caso de balance
					rotarIzquierda(n->izq);                   //rota primero a la izquierda (caso 2 = caso 4 + caso 1)
				rotarDerecha(n);                            //rota a la derecha (caso 1)
			}
			return true;
		}
	}
	else if (n->dato < dato) {                        //Si el dato es mayor,
		if (inserta(dato, n->der)) {                    //si ha podido insertarlo en el nodo derecho
			n->bal--;                                     //ajusta el balance del nodo
			if (n->bal == -2) {                           //si el balance es incorrecto
				if (n->der->bal == 1)                       //comprueba el caso de balance
					rotarDerecha(n->der);                     //rota primero a la derecha (caso 3 = caso 1 + caso 4)
				rotarIzquierda(n);                          //rota a la izquierda(caso 4)
			}
			return true;
		}
	}
	return false;
}
#endif // !AVL_H