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
	NodoAVL<T>* copiaRama(NodoAVL<T>* nodoacopiar);
	void rotarIzquierda(NodoAVL<T>*& nodo);
	void rotarDerecha(NodoAVL<T>*& nodo);
	bool insertaPriv(T& dato, NodoAVL<T>*& n);
	void recorreInorden(NodoAVL<T>* n);
	void borrarRama(NodoAVL<T>* n);
	int alturaNodo(NodoAVL<T>* n);
	int maximo(int a, int b);
	bool busca(T& dato, T& resultado, NodoAVL<T>* inicio);
	void verArbol(NodoAVL<T>* nodo, int n);
	void ajustaAltura(NodoAVL<T>* nodo);

public:
	AVL();
	AVL(const AVL<T>& orig);
	~AVL();
	AVL<T>& operator=(const AVL<T>& right);
	void recorreInorden();
	unsigned int numElementos();
	unsigned int altura();
	bool inserta(T& dato);
	bool busca(T& dato, T& resultado);
	bool buscaIt(T& dato, T& resultado);
	void verArbol();
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
AVL<T>::AVL(const AVL<T>& orig): alt(orig.alt), tam(orig.tam){
	raiz = copiaRama(orig.raiz);
}

/**
	@brief Destructor
*/
template<class T>
AVL<T>::~AVL()
{
	borrarRama(raiz);
}

/**
	@brief Operador de asignacion
	@return *this para operaciones en cascada
*/
template<class T>
AVL<T>& AVL<T>::operator=(const AVL<T>& right) 
{
	raiz = copiaRama(right.raiz);
	return *this;
}

/**
*@Brief Método público del método recorreInorden()
*/
template<class T>
void AVL<T>::recorreInorden()
{
	AVL<T>::recorreInorden(raiz);
}

/**
	@brief Muestra el contenido del arbol recorriendolo mediante inorden
	@param n Nodo incial del arbol
	@pre La clase T debe tener sobrecargado el operador <<
*/
template<class T>
void AVL<T>::recorreInorden(NodoAVL<T>* n)
{
	if (n == 0)	//Si el nodo es un puntero nulo, lanza excepcion
		throw std::invalid_argument("[AVL<T>::recorreInorden]: el parametro pasado es igual a 0");
	if (n->izq)	//Si el nodo tiene hijo izquierdo, lo recorre
		recorreInorden(n->izq);
	if (n->der)	//Si el nodo tiene hijo derecho, lo recorre
		recorreInorden(n->der);

	std::cout << n->dato << std::endl;

}

/**
*@Brief Borra todos los nodos que hayan por debajo del nodo pasado como parametro
*/
template<class T>
void AVL<T>::borrarRama(NodoAVL<T>* n)
{
	if (n) {
		if (n->izq != 0) {		//Si el nodo tiene hijo izquierdo
			borrarRama(n->izq);		//elimina el subarbol
		}
		if (n->der != 0) {		//Si el nodo tiene hijo derecho
			borrarRama(n->der);		//elimina el subarbol
		}
		delete n;
	}
}

/**
	@brief Devuelve la altura del nodo indicado
	@return -1 Si n es un puntero nulo
*/
template<class T>
int AVL<T>::alturaNodo(NodoAVL<T>* n)
{
	if (n)					//Si el puntero es un nodo valido
		return n->altura;		//devuelve su altura	
	return -1;				//si no, devuelve -1 para poder realizar comparaciones
}

/**
	@brief Devuelve el maximo de dos enteros
*/
template<class T>
int AVL<T>::maximo(int a, int b)
{
	return (a < b) ? b : a;
}

/**
*@Brief Método privado de busqueda. Se usa para la busqueda recursiva
*@Param dato: Dato a buscar
*@param resultado: Se almacena el resultado si se encuentra
*@param nodo : Nodo en el cual se empezará esa busqueda
*/
template<class T>
bool AVL<T>::busca(T& dato, T& resultado, NodoAVL<T>* inicio)
{
	if (inicio==0){										//Si el nodo es un puntero nulo
		return false;										//no es el dato buscado
	}
	if (dato<inicio->dato){								//Si el dato es menor que el valor del nodo
		if (busca(dato, resultado, inicio->izq))			//busca en el subarbol izquierdo
			return true;
	}
	else if (dato > inicio->dato) {						//Si el dato es mayor que el valor del nodo
		if (busca(dato, resultado, inicio->der)) {			//busca en el subarbol derecho
			return true;
		}
	}
	else {												//En otro caso, el nodo actual contiene el dato buscado
		resultado = inicio->dato;
		return true;
	}
	return false;
}

/**
*@Brief Método privado para la visualización por consola del Arbol. Se encarga de la recursividad.
*@Param nodo: Nodo en el que se iniciará la visualización
*@Param nivel: Nivel de profundidad del nodo
*/
template<class T>
 void AVL<T>::verArbol(NodoAVL<T>* nodo, int nivel){
	 if (nodo == 0) {
		 return;
	 }
	 verArbol(nodo->der, nivel + 1);
	 for (int i = 0; i < nivel; i++){
		 std::cout << "       ";
	 }
	 std::cout << nodo->dato << std::endl << std::endl;
	 verArbol(nodo->izq, nivel + 1);
}

/**
	@brief Devuelve el numero de nodos en el arbol
*/
template<class T>
unsigned int AVL<T>::numElementos()
{
	return tam;
}

/**
*@Brief Devuelve la altura del arbol
*/
template<class T>
unsigned int AVL<T>::altura()
{
	return alt;
}

/**
	@brief Inserta un dato en el arbol de forma recursiva
	@param dato Dato a insertar
	@return True si se ha podido insertar, False en otro caso
*/
template<class T>
bool AVL<T>::inserta(T& dato)
{

	if (insertaPriv(dato, raiz)) {	//Si se ha podido insertar recursivamente el dato
		if (raiz)						//Si el arbol tiene raiz
			alt = raiz->altura;				//iguala la altura del arbol a la del nodo raiz
		return true;					//devuelve true para confirmar la insercion
	}
	return false;
}
/**
*@Brief Método público para la busqueda recursiva
*@param dato: Dato a buscar
*@param resultado: Dato encontrado como resultado
*/
template<class T>
bool AVL<T>::busca(T& dato, T& resultado){
	 return busca(dato, resultado, raiz);
}

//TODO: comentar esto
template<class T>
bool AVL<T>::buscaIt(T& dato, T& resultado)
{
	NodoAVL<T>* i;
	for (i = raiz; i != 0;){
		if (i->dato == dato) {
			resultado = i->dato;
			return true;
		}
		else if (i->dato < dato)
			i = i->der;
		else if (dato < i->dato)
			i = i->izq;
	}
	return false;
}

/**
*@Brief Método público de visualizar por consola un arbol. Hace uso del método privado verArbol()
*/
template<class T>
void AVL<T>::verArbol(){
	std::cout << std::endl << std::endl << std::endl << std::endl ;
	std::cout << "--------------------------------------------------------------------------------------------------------------"<<std::endl<<std::endl;
	verArbol(raiz, 0);
}

/**
*@Brief Método privado recursivo que se encarga de copiar los diferentes nodos de la rama
*@param nodoacopiar: Nodo del cual se realizará la copia
*/
template<class T>
NodoAVL<T>* AVL<T>::copiaRama(NodoAVL<T>* nodoacopiar){
	if (nodoacopiar == 0)
		return 0;
	NodoAVL<T>* nodoNuevo = new NodoAVL<T>(*nodoacopiar);
	nodoNuevo->der = copiaRama(nodoacopiar->der);
	nodoNuevo->izq = copiaRama(nodoacopiar->izq);
	return nodoNuevo;
}

/**
	@brief Rota el nodo actual hacia la izquierda
	@param nodo Nodo a rotar
	@post El nodo indicado queda como hijo izquierdo de su subarbol derecho
*/
template<class T>
void AVL<T>::rotarIzquierda(NodoAVL<T>* &nodo)
{
	NodoAVL<T>* temp = nodo;	//Crea un puntero al nodo que se va a modificar para evitar perderlo
	nodo = nodo->der;			//Asigna a nodo todo su subarbol derecho
	temp->der = nodo->izq;		//El subarbol izquierdo de nodo se asigna como hijo derecho del original
	nodo->izq = temp;			//El nodo original se coloca como hijo izquierdo del nodo actualizado
								//Ajusta el balance de los nodos a partir de la altura de los hijos
	ajustaAltura(nodo);
	temp->bal = alturaNodo(temp->izq) - alturaNodo(temp->der);
	nodo->bal = alturaNodo(nodo->izq) - alturaNodo(nodo->der);
}

/**
	@brief Rota el nodo actual hacia la derecha
	@param nodo Nodo a rotar
	@post El nodo indicado queda como hijo derecho de su subarbol izquierdo
*/
template<class T>
void AVL<T>::rotarDerecha(NodoAVL<T>*& nodo)
{
	NodoAVL<T>* temp = nodo;	//Crea un puntero al nodo que se va a modificar para evitar perderlo
	nodo = nodo->izq;			//Asigna a nodo todo su subarbol izquierdo
	temp->izq = nodo->der;		//El subarbol derecho de nodo se asigna como hijo izquierdo del original
	nodo->der = temp;			//El nodo original se coloca como hijo derecho del nodo actualizado
								//Ajusta el balance de los nodos a partir de la altura de los hijos
	ajustaAltura(nodo);
	temp->bal = alturaNodo(temp->izq) - alturaNodo(temp->der);
	nodo->bal = alturaNodo(nodo->izq) - alturaNodo(nodo->der);
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
bool AVL<T>::insertaPriv(T& dato, NodoAVL<T>*& n)
{
	if (!n) {
		n = new NodoAVL<T>(dato);
		n->bal = 0;
		return true;
	}
	else if (dato < n->dato) {
		if (insertaPriv(dato, n->izq)){
			n->bal = (alturaNodo(n->izq) + 1) - (alturaNodo(n->der) + 1);
			if (n->bal == 2) {
				if (n->izq->bal == -1)
					rotarIzquierda(n->izq);
				rotarDerecha(n);
			}
			n->altura = 1 + maximo(alturaNodo(n->izq), alturaNodo(n->der));
			return true;
		}
	}
	else if (n->dato < dato) {
		if (insertaPriv(dato, n->der)) {
			n->bal = (alturaNodo(n->izq) + 1) - (alturaNodo(n->der) + 1);
			if (n->bal == -2) {
				if (n->der->bal == 1)
					rotarDerecha(n->der);
				rotarIzquierda(n);
			}
			n->altura = 1 + maximo(alturaNodo(n->izq), alturaNodo(n->der));
			return true;
		}
	}
	return false;
}

template<class T>
void AVL<T>::ajustaAltura(NodoAVL<T>* nodo)
{
	if (nodo->izq)
		ajustaAltura(nodo->izq);
	if (nodo->der)
		ajustaAltura(nodo->der);
	nodo->altura = 1 + maximo(alturaNodo(nodo->izq), alturaNodo(nodo->der));
}

#endif // !AVL_H