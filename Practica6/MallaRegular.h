#pragma once

#include <vector>
#include <list>
#include "UTM.h"

template <class T>
class Celda {
	list<T> lista;
public:
	unsigned getNumEle();
	T& masCercano(UTM coor);
	void insertar(T dato);
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
	T* aux;
	double distancia=9999;
	if (lista.size() > 0) {
		typename std::list<T>::iterator it;
		for (it=lista.begin(); it != lista.end(); it++){
			if (coor.distancia((*it).getUTM()) < distancia) {
				distancia = coor.distancia((*it).getUTM());
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


//-------------------------------------------------------------------------------------------------------------------


template <class T>
class MallaRegular
{
	//TODO: atributos
	vector<vector<Celda<T>>> buffer;
	float xMin, xMax, yMin, yMax, interX, interY;
public:
	MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
	T& buscarCercano(float x, float y);
	bool fueraAmbito(float x, float y);
	MallaRegular<T>& insertar(T dato);
	unsigned maxElementosPorCelda();
	unsigned mediaElementosPorCelda();
};


// ---------------------- IMPLEMENTACIONES --------------------------------------------------------

/**
* @Brief Constructor parametrizado de Malla Regular
*/
template<class T>
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY): xMin(aXMin), xMax(aXMax), yMin(aYMin), yMax(aYMax){
	buffer.resize(nDivX);
	for (unsigned i = 0; i < buffer.size(); i++){
		buffer[i].resize(nDivY);
	}
	interX = (xMax - xMin) / nDivX;
	interY = (yMax - yMin) / nDivY;
}

/**
*@Brief Busca el dato más cercano a la posicion que se indica mediantes los parametros x, y
*/
template<class T>
T& MallaRegular<T>::buscarCercano(float x, float y)
{
	UTM coordenadas(x, y);
	int posX = (x - xMin) / interX;
	int posY = (yMax - y) / interY;
	int iniciobucleX, iniciobucleY, finbucleX, finbucleY;
	double distancia=9999;
	T* aux, aux2;

	if (posX != 0 && posX != (xMax / interX)) {
		iniciobucleX = posX - 1;
		finbucleX = posX + 1;
	}
	else if (posX == 0) {
		iniciobucleX = 0;
		finbucleX = posX + 1;
	}
	else {
		iniciobucleX = posX - 1;
		finbucleX = (xMax/interX);
	}
	
	if (posY != 0 && posY != (yMax / interY)) {
		iniciobucleY = posY - 1;
		finbucleY = posY + 1;
	}
	else if (posY == 0) {
		iniciobucleY = 0;
		finbucleY = posY + 1;
	}
	else {
		iniciobucleY = posY - 1;
		finbucleY = (yMax / interY);
	}
	while (!aux) {
		for (unsigned i = iniciobucleX; i <= finbucleX; i++) {
			for (unsigned j = iniciobucleY; j <= finbucleY; j++) {
				aux2 = &(buffer[i][j].masCercano(coordenadas));
				if (coordenadas.distancia(aux2->getUTM()) < distancia) {
					distancia = coordenadas.distancia(aux2->getUTM());
					aux = aux2;
				}
			}
		}
		if (iniciobucleX-- < 0) {
			iniciobucleX++;
		}
		if (iniciobucleY-- < 0) {
			iniciobucleY++;
		}
		if (finbucleX++ > (xMax/interX)) {
			finbucleX--;
		}
		if (finbucleY++ > (yMax / interY)) {
			finbucleY--;
		}
	}
	return *aux;
}

/**
* @Brief Inserta el dato en la celda correspondiente
* @pre Es necesario que la clase T tenga implementado el método UTM GetUTM()
*/
template<class T>
MallaRegular<T>& MallaRegular<T>::insertar(T dato){
	int posX = (dato.getUTM().latitud - xMin) / interX;
	int posY = (yMax - dato.getUTM().longitud) / interY;
	buffer[posX][posY].insertar(dato);
}

