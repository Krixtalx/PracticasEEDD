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

/**
* @Brief Devuelve el n� de elementos que hay en la celda.
*/
template<class T>
unsigned Celda<T>::getNumEle()
{
	return lista.size();
}

/**
* @Brief Devuelve el dato m�s cercano al UTM que se pasa como parametro
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
* @Brief Inserta una copia del dato que se pasa como parametro al final de la lista.
*/
template<class T>
void Celda<T>::insertar(T dato){
	lista.push_back(dato);
}

/**
* @Brief Muestra las coordenadas de los elementos que hay en la celda.
*/
template<class T>
void Celda<T>::verCelda(){
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
	pair<float, float> getTamCelda();
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

/**
* @Brief Constructor de copia de Malla Regular
*/
template<class T>
MallaRegular<T>::MallaRegular(MallaRegular& orig) : xMin(orig.xMin), xMax(orig.xMax), yMin(orig.yMin), yMax(orig.yMax), nDivX(orig.nDivX), nDivY(orig.nDivY), interX(orig.interX), interY(orig.interY), nElementos(orig.nElementos)
{
	buffer = orig.buffer;
}

/**
* @Brief Destructor de Malla Regular
*/
template<class T>
MallaRegular<T>::~MallaRegular()
{
}

/**
* @Brief Operador= de Malla Regular
*/
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
	interX = right.interX;
	interY = right.interY;
	nElementos = right.nElementos;
	buffer = right.buffer;
	return *this;
}



/**
*@Brief Busca el dato m�s cercano a la posicion que se indica mediantes los parametros x, y
*@Return Devuelve el dato que encuentre. Si no encuentra ninguno, devuelve un puntero nulo
*@Throw Out_of_range si las coordenadas pasadas como parametro no se encuentra en el rango permitido
*/
template<class T>
T* MallaRegular<T>::buscarCercano(float x, float y)
{

	if (x<xMin || x>xMax || y<yMin || y>yMax)
		throw std::out_of_range("[MallaRegular::buscarCercano]:Las coordenadas pasadas como parametro no se encuentran en el rango permitido.");

	UTM coordenadas(x, y);
	int posX = (x - xMin) / interX;
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
	if (finbucleX >= nDivX)
		finbucleX--;
	if (iniciobucleY < 0)
		iniciobucleY++;
	if (finbucleY >= nDivY)
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
*@Brief Comprueba si existe un punto fijo a menos de una celda de distancia de la posici�n
*@Return true si no hay punto fijo a menos de una celda, false en otro caso
*@Throw Out_of_range si las coordenadas pasadas como parametro no se encuentra en el rango permitido
*/
template<class T>
bool MallaRegular<T>::fueraAmbito(float x, float y)
{
	if (x<xMin || x>xMax || y<yMin || y>yMax)
		throw std::out_of_range("[MallaRegular::fueraAmbito]:Las coordenadas pasadas como parametro no se encuentran en el rango permitido.");

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
	if (finbucleX >= nDivX)
		finbucleX--;
	if (iniciobucleY < 0)
		iniciobucleY++;
	if (finbucleY >= nDivY)
		finbucleY--;
	for (unsigned i = iniciobucleX; i <= finbucleX; i++) {
		for (unsigned j = iniciobucleY; j <= finbucleY; j++) {
			aux = &(buffer[i][j].masCercano(coordenadas));
			if (aux) {
				if (abs(x - aux->getX()) <= interX && abs(y - aux->getY()) <= interY) {
					return false;
				}
			}
		}
	}
	return true;
}

/**
* @Brief Inserta el dato en la celda correspondiente
* @pre Es necesario que la clase T tenga implementados los m�todos getX() y getY()
*/
template<class T>
MallaRegular<T>& MallaRegular<T>::insertar(T& dato){
	int posX = (dato.getX() - xMin) / interX;
	int posY = (dato.getY() - yMin) / interY;
	buffer[posX][posY].insertar(dato);
	nElementos++;
	return *this;
}

/**
*@Brief Devuelve el mayor n� de elementos que hay en las celdas 
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
*@Brief Devuelve el n�mero medio de elementos por celda
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

/**
*@Brief Devuelve n� de elementos que hay en las celdas
*/
template<class T>
unsigned MallaRegular<T>::getNumElementos()
{
	return nElementos;
}

/**
*@Brief Recorre cada celda y muestra por pantalla sus elementos.
*/
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

/**
*@Brief Devuelve el tama�o de las celdas
*@Return Devuelve un pair donde el primer campo es el tama�o X de la celda y el segundo campo es el tama�o Y de la celda
*/
template<class T>
pair<float, float> MallaRegular<T>::getTamCelda()
{
	return pair<float, float>(interX, interY);
}

