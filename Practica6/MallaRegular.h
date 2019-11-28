#pragma once

#include <vector>
template <class T>
class Celda {

};

template <class T>
class MallaRegular
{
	//TODO: atributos
	vector<vector<T>> buffer;
	float xMin, xMax, yMin, yMax;
public:
	MallaRegular(float aXMin, float aYMin, float aXMax, float aYMax, int nDivX, int nDivY);
	T buscarCercano(float x, float y);
	bool fueraAmbito(float x, float y);
	unsigned maxElementosPorCelda();
	unsigned mediaElementosPorCelda();
};