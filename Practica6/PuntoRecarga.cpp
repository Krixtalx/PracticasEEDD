#include "PuntoRecarga.h"

PuntoRecarga::PuntoRecarga() : id(""), posicion(0,0)
{
}

PuntoRecarga::PuntoRecarga(string _id, UTM _posicion) : id(_id), posicion(_posicion)
{
}

PuntoRecarga::PuntoRecarga(string _id, double x, double y): id(_id){
	UTM aux(x, y);
	posicion = aux;
}

PuntoRecarga::~PuntoRecarga()
{
	//NO HAY NADA AQUI ES IMPOSIBLE QUE PETE ESTO, O SI
}

PuntoRecarga::PuntoRecarga(const PuntoRecarga& orig) : id(orig.id)
{
	posicion = orig.posicion;
}

PuntoRecarga& PuntoRecarga::operator=(const PuntoRecarga& right)
{
	if (this == &right) {
		return *this;
	}
	id = right.id;
	posicion = right.posicion;
	return *this;
}

/**
* @Brief Devuelve la coordenada X del Punto de Recarga
*/
float PuntoRecarga::getX()
{
	return posicion.latitud;
}

/**
* @Brief Devuelve la coordenada Y del Punto de Recarga
*/
float PuntoRecarga::getY()
{
	return posicion.longitud;
}
