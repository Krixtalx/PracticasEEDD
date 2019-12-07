#pragma once
#ifndef PUNTORECARGA_H
#define PUNTORECARGA_H

#include <string>
#include "UTM.h"

using namespace std;

class PuntoRecarga
{
	string id;
	UTM posicion;
public:
	PuntoRecarga();
	PuntoRecarga(string _id, UTM _posicion);
	PuntoRecarga(string _id, double x, double y);
	~PuntoRecarga();
	PuntoRecarga(const PuntoRecarga& orig);
	PuntoRecarga& operator=(const PuntoRecarga& right);
	float getX();
	float getY();
};


#endif // !PUNTORECARGA_H