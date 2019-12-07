#pragma once

#include <vector>
#include <list>
#include "UTM.h"
#include <cmath>
#include <iostream>

template <class T>
class Celda {
	list<T> lista;
public:
	unsigned getNumEle();
	T& masCercano(UTM coor);
	void insertar(T dato);
	void verCelda();
};

// ---------------------- IMPLEMENTACIONES --------------------------------------------------------

template<class T>
unsigned Celda<T>::getNumEle()
{
	return lista.size();
}

/**
* @Brief Devuelve el dato más cercano al UTM que se pasa como parametro
*/
template<class T>
T& Celda<T>::masCercano(UTM coor)
{
	T* aux = 0;
	double distancia=9999;
	if (lista.size() > 0) {
		typename std::list<T>::iterator it;
		for (it=lista.begin(); it != lista.end(); it++){
			UTM utmCercano((*it).getX(), (*it).getY());
			if (coor.distancia(utmCercano) < distancia) {
				distancia = coor.distancia(utmCercano);
				aux = &(*it);
			}
		}
	}
	return *aux;
}

/**
* @Brief Inserta una copia del dato que se pasa como parametro al final de la lista
*/
template<class T>
void Celda<T>::insertar(T dato){
	lista.push_back(dato);
}

template<class T>
void Celda<T>::verCelda()
{
	typename list<T>::iterator it;
	for (it = lista.begin(); it != lista.end(); it++)
		std::cout << (*it).getX() << " - " << (*it).getY() << std::endl;
}


//-------------------------------------------------------------------------------------------------------------------


template <class T>
class MallaRegular
{
	vector<vector<Celda<T>>> buffer;
	float xMin = 0, xMax = 0, yMin = 0, yMax = 0, interX = 0, interY = 0;
	unsigned nDivX = 0, nDivY = 0, nElementos = 0;
public:
	MallaRegular();
	MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
	MallaRegular(MallaRegular& orig);
	~MallaRegular();
	MallaRegular<T>& operator=(MallaRegular& right);
	T* buscarCercano(float x, float y);
	bool fueraAmbito(float x, float y);
	MallaRegular<T>& insertar(T& dato);
	unsigned maxElementosPorCelda();
	float mediaElementosPorCelda();
	unsigned getNumElementos();
	void recorrerMalla();
};


// ---------------------- IMPLEMENTACIONES --------------------------------------------------------

template<class T>
MallaRegular<T>::MallaRegular()
{
}

/**
* @Brief Constructor parametrizado de Malla Regular
*/
template<class T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY): xMin(aXMin), xMax(aXMax), yMin(aYMin), yMax(aYMax), nDivX(nDivX), nDivY(nDivY){
	buffer.resize(nDivX);
	for (unsigned i = 0; i < buffer.size(); i++){
		buffer[i].resize(nDivY);
	}
	interX = (xMax - xMin) / nDivX;
	interY = (yMax - yMin) / nDivY;
}

template<class T>
MallaRegular<T>::MallaRegular(MallaRegular& orig) : xMin(orig.xMin), xMax(orig.xMax), yMin(orig.yMin), yMax(orig.yMax), nDivX(orig.nDivX), nDivY(orig.nDivY)
{
	buffer = orig.buffer;
}

template<class T>
MallaRegular<T>::~MallaRegular()
{
}

template<class T>
MallaRegular<T>& MallaRegular<T>::operator=(MallaRegular& right)
{
	if (this == &right) {
		return *this;
	}
	xMin = right.xMin;
	xMax = right.xMax;
	yMin = right.yMin;
	yMax = right.yMax;
	nDivX = right.nDivX;
	nDivY = right.nDivY;
	buffer = right.buffer;
	return *this;
}



/**
*@Brief Busca el dato más cercano a la posicion que se indica mediantes los parametros x, y
*/
template<class T>
T* MallaRegular<T>::buscarCercano(float x, float y)
{
	//TODO: excepciones si x, y no estan en rango
	UTM coordenadas(x, y);
	int posX = (x - xMin) / interX;
	//int posY = (yMax - y) / interY;
	int posY = (y - yMin) / interY;
	int iniciobucleX, iniciobucleY, finbucleX, finbucleY;
	double distancia=9999;
	T* aux = 0;
	T* aux2 = 0;

	iniciobucleX = posX-1;
	finbucleX = posX+1;
	iniciobucleY = posY-1;
	finbucleY = posY+1;
	if (iniciobucleX < 0)
		iniciobucleX++;
	if (finbucleX >= (xMax / interX))
		finbucleX--;
	if (iniciobucleY < 0)
		iniciobucleY++;
	if (finbucleY >= (yMax / interY))
		finbucleY--;
	while (!aux) {
		for (unsigned i = iniciobucleX; i <= finbucleX; i++) {
			for (unsigned j = iniciobucleY; j <= finbucleY; j++) {
				aux2 = &(buffer[i][j].masCercano(coordenadas));
				if (aux2) {
					UTM utmCercano(aux2->getX(), aux2->getY());
					if (coordenadas.distancia(utmCercano) < distancia) {
						distancia = coordenadas.distancia(utmCercano);
						aux = aux2;
					}
				}
				
			}
		}
		if (iniciobucleX <= 0 && finbucleX >= nDivX && iniciobucleY <= 0 && finbucleY >= nDivY)
			return 0;
		if (iniciobucleX-- < 0) {
			iniciobucleX++;
		}
		if (iniciobucleY-- < 0) {
			iniciobucleY++;
		}
		if (finbucleX++ >= (xMax/interX)) {
			finbucleX--;
		}
		if (finbucleY++ >= (yMax / interY)) {
			finbucleY--;
		}
	}
	return aux;
}

/**
*@Brief Comprueba si existe un punto fijo a menos de una celda de distancia de la posición
*@Return true si no hay punto fijo a menos de una celda, false en otro caso
*/
template<class T>
bool MallaRegular<T>::fueraAmbito(float x, float y)
{
	//TODO: excepciones si x, y no estan en rango
	UTM coordenadas(x, y);
	int posX = (x - xMin) / interX;
	int posY = (y - yMin) / interY;
	int iniciobucleX, iniciobucleY, finbucleX, finbucleY;
	T* aux = 0;

	iniciobucleX = posX - 1;
	finbucleX = posX + 1;
	iniciobucleY = posY - 1;
	finbucleY = posY + 1;
	if (iniciobucleX < 0)
		iniciobucleX++;
	if (finbucleX >= (xMax / interX))
		finbucleX--;
	if (iniciobucleY < 0)
		iniciobucleY++;
	if (finbucleY >= (yMax / interY))
		finbucleY--;
	for (unsigned i = iniciobucleX; i <= finbucleX; i++) {
		for (unsigned j = iniciobucleY; j <= finbucleY; j++) {
			aux = &(buffer[i][j].masCercano(coordenadas));
			if (aux) {
				if (abs(x - aux.getX()) <= interX && abs(y - aux.getY()) <= interY) {
					return false;
				}
			}
		}
	}
	return true;
}

/**
* @Brief Inserta el dato en la celda correspondiente
* @pre Es necesario que la clase T tenga implementados los métodos getX() y getY()
*/
template<class T>
MallaRegular<T>& MallaRegular<T>::insertar(T& dato){
	//int posX = (dato.getUTM().latitud - xMin) / interX;
	//int posY = (yMax - dato.getUTM().longitud) / interY;
	int posX = (dato.getX() - xMin) / interX;
	int posY = (dato.getY() - yMin) / interY;
	buffer[posX][posY].insertar(dato);
	nElementos++;
	return *this;
}

/**
*@Brief Devuelve el mayor nº de elementos que hay en las celdas 
*/
template<class T>
unsigned MallaRegular<T>::maxElementosPorCelda(){
	unsigned max = 0;
	for (unsigned i = 0; i < nDivX; i++){
		for (unsigned j = 0; j < nDivY; j++){
			if (buffer[i][j].getNumEle() > max)
				max = buffer[i][j].getNumEle();
		}
	}
	return max;
}

/**
*@Brief Devuelve el número medio de elementos por celda
*/
template<class T>
float MallaRegular<T>::mediaElementosPorCelda()
{
	float totalElem = 0;
	for (unsigned i = 0; i < nDivX; i++) {
		for (unsigned j = 0; j < nDivY; j++) {
			totalElem += buffer[i][j].getNumEle();
		}
	}
	return totalElem/(nDivX*nDivY);
}

template<class T>
inline unsigned MallaRegular<T>::getNumElementos()
{
	return nElementos;
}

template<class T>
void MallaRegular<T>::recorrerMalla()
{
	for (size_t i =	0; i < nDivX; i++)
	{
		for (size_t j = 0; j < nDivY; j++) {
			buffer[i][j].verCelda();
		}
	}
}

