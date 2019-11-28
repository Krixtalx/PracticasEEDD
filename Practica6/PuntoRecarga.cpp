#include "PuntoRecarga.h"

PuntoRecarga::PuntoRecarga() : id(""), posicion(0,0)
{
}

PuntoRecarga::PuntoRecarga(string _id, UTM _posicion) : id(_id), posicion(_posicion)
{
}

PuntoRecarga::~PuntoRecarga()
{
	//NO HAY NADA AQUI ES IMPOSIBLE QUE PETE ESTO, O SI
}

PuntoRecarga::PuntoRecarga(PuntoRecarga& orig) : id(orig.id), posicion(orig.posicion)
{
}

PuntoRecarga& PuntoRecarga::operator=(PuntoRecarga& right)
{
	if (this == &right) {
		return *this;
	}
	id = right.id;
	posicion = right.posicion;
	return *this;
}

float PuntoRecarga::getX()
{
	return posicion.latitud;
}

float PuntoRecarga::getY()
{
	return posicion.latitud;
}
