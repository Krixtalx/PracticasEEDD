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
	bool insertaPriv(T& dato, NodoAVL<T>*& n);
	void recorreInorden(NodoAVL<T>* n);
	void borrarRama(NodoAVL<T>* n);
	int alturaNodo(NodoAVL<T>* n);
	int maximo(int a, int b);
	bool busca(T& dato, T& resultado, NodoAVL<T>* inicio);
	void verArbol(NodoAVL<T>* nodo, int n);

public:
	AVL();
	AVL(const AVL<T>& orig);
	~AVL();
	AVL<T>& operator=(const AVL<T>& right);
	NodoAVL<T>& getRaiz();
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
	borrarRama(raiz);
}

template<class T>
AVL<T>& AVL<T>::operator=(const AVL<T>& right) 
{
	//TODO: asignar
}

template<class T>
NodoAVL<T>& AVL<T>::getRaiz()
{
	return *raiz;
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
	if (n == 0)
		throw std::invalid_argument("[AVL<T>::recorreInorden]: el parametro pasado es igual a 0");
	if (n->izq)
		recorreInorden(n->izq);
	if (n->der)
		recorreInorden(n->der);

	std::cout << n->dato << std::endl;

}

/**
*@Brief Borra todos los nodos que hayan por debajo del nodo pasado como parametro
*/
template<class T>
void AVL<T>::borrarRama(NodoAVL<T>* n)
{
	if (n->izq != 0) {
		borrarRama(n->izq);
	}
	if (n->der != 0) {
		borrarRama(n->der);
	}
	delete n;
}

/**
	@brief Devuelve la altura del nodo indicado
*/
template<class T>
int AVL<T>::alturaNodo(NodoAVL<T>* n)
{
	if (n)
		return n->altura;
	return 0;
}

/**
	@brief Devuelve el maximo de los numeros indicados
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
	if (inicio==0){
		return false;
	}
	if (dato<inicio->dato){
		if (busca(dato, resultado, inicio->izq))
			return true;
	}
	else if (dato > inicio->dato) {
		if (busca(dato, resultado, inicio->der)) {
			return true;
		}
	}
	else {
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
		 std::cout << "          ";
	 }
	 std::cout << nodo->dato<<std::endl<<std::endl;
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
	@brief Devuelve la altura del arbol
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
	if (raiz)
		alt = raiz->altura;
	if (insertaPriv(dato, raiz))
		return true;
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

template<class T>
void AVL<T>::verArbol(){
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
	verArbol(raiz, 0);
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
bool AVL<T>::insertaPriv(T& dato, NodoAVL<T>*& n)
{
	//TODO: Se tiene que ir actualizando la altura o si no, actualizar el método altura()
	if (!n) {                                         //Si no hay nodo, inserta el dato
		n = new NodoAVL<T>(dato);
		n->bal = 0;
		return true;
	}
	else if (dato < n->dato) {                        //Si el dato es menor,
		if (insertaPriv(dato, n->izq)){                     //si ha podido insertarlo en el nodo izquierdo
			n->bal++;                                     //ajusta el balance del nodo,
			if (n->bal == 2) {                            //si el balance es incorrecto
				if (n->izq->bal == -1)                      //comprueba el caso de balance
					rotarIzquierda(n->izq);                   //rota primero a la izquierda (caso 2 = caso 4 + caso 1)
				rotarDerecha(n);                            //rota a la derecha (caso 1)
			}
			n->altura = 1 + maximo(alturaNodo(n->izq), alturaNodo(n->der));//Establece la altura del nodo a uno mas que la maxima altura de sus hijos
			return true;
		}
	}
	else if (n->dato < dato) {                        //Si el dato es mayor,
		if (insertaPriv(dato, n->der)) {                    //si ha podido insertarlo en el nodo derecho
			n->bal--;                                     //ajusta el balance del nodo
			if (n->bal == -2) {                           //si el balance es incorrecto
				if (n->der->bal == 1)                       //comprueba el caso de balance
					rotarDerecha(n->der);                     //rota primero a la derecha (caso 3 = caso 1 + caso 4)
				rotarIzquierda(n);                          //rota a la izquierda(caso 4)
			}
			n->altura = 1 + maximo(alturaNodo(n->izq), alturaNodo(n->der));//Establece la altura del nodo a uno mas que la maxima altura de sus hijos
			return true;
		}
	}
	return false;
}
#endif // !AVL_H