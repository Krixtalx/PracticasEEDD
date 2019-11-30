#pragma once

#include <vector>
#include "UTM.h"

template <class T>
class Celda {
	list <T> buffer;
public:
	unsigned getNumEle();
	T& masCercano(UTM coor);

};

template <class T>
class MallaRegular
{
	//TODO: atributos
	vector<vector<Celda>> buffer;
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
MallaRegular<T>::MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY): xMin(aXMin), xMas(aXMax), yMin(aYMin), yMax(aYMax){
	buffer.resize(nDivX);
	for (unsigned i = 0; i < length; i++){
		buffer[i].resize(nDivY);
	}
	interX = (xMax - xMin) / nDivX;
	interY = (yMax - yMin) / nDivY;
}

template<class T>
T& MallaRegular<T>::buscarCercano(float x, float y)
{
	UTM aux(x, y);
	int posX = (x - xMin) / interX;
	int posY = (yMax - y) / interY;

	return T();
}

template<class T>
MallaRegular<T>& MallaRegular<T>::insertar(T dato)
{

	// TODO: insertar una instrucción return aquí
}


