#ifndef AVL_H
#define AVL_H

#include "NodoAVL.h"

//TODO: LA PRACTICA

template <class T>
class AVL{
private:
	NodoAVL<T>* raiz;
	unsigned int alt;
	unsigned int tam;

public:
	AVL();
	AVL(const AVL<T>& orig);
	~AVL();
	AVL<T>& operator=(const AVL<T>& right);
	void recorreInorden();
	unsigned int numElementos();
	unsigned int altura();
	void rotIzq(NodoAVL<T>* nodo);
	void rotDer(NodoAVL<T>*  nodo);
	bool busca(T& dato, T& resultado);
	bool buscaIt(T& dato, T& resultado);
	bool inserta(T& dato);
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



#endif // !AVL_H