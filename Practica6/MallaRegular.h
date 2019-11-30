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
};


template<class T>
T& Celda<T>::masCercano(UTM coor)
{
	T* aux;
	double distancia=9999;
	if (lista.size() > 0) {
		for (std::list<T>::iterator it=lista.begin(); it != lista.end(); it++){
			if (coor.distancia((*it).getUTM()) < distancia) {
				distancia = coor.distancia((*it).getUTM());
				aux = &(*it);
			}
		}
	}
	return *aux;
}

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
* 
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

template<class T>
T& MallaRegular<T>::buscarCercano(float x, float y)
{
	UTM coordenadas(x, y);
	int posX = (x - xMin) / interX;
	int posY = (yMax - y) / interY;
	double distancia=9999;
	T* aux, aux2;

	if (posX!=0 && posX!=(xMax/interX)){
		for (unsigned i = posX-1; i <= posX+1; i++)
		{
			if (posY != 0 && posY != (yMax / interY)) {
				for (unsigned j = posY-1; j <= posY+1; j++)
				{
					aux2 = &(buffer[i][j].masCercano(coordenadas));
					if (coordenadas.distancia(aux2->getUTM()) < distancia) {
						distancia = coordenadas.distancia(aux2->getUTM());
						aux = aux2;
					}
				}
			}
		}
	}
	return *aux;
}

template<class T>
MallaRegular<T>& MallaRegular<T>::insertar(T dato)
{

	// TODO: insertar una instrucción return aquí
}

