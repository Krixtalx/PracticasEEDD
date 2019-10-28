#include "Moto.h"

Moto::Moto() : id("0") {
}

Moto::Moto(std::string id, UTM posicion, Estado estatus): id(id), posicion(posicion), estatus(estatus){
}

Moto::Moto(const Moto& orig){
	id = orig.id;
	posicion = orig.posicion;
	estatus = orig.estatus;
	usadoPor = orig.usadoPor;
}

Moto::~Moto(){
}

Moto& Moto::operator=(Moto& right)
{
	id = right.id;
	posicion.latitud = right.posicion.latitud;
	posicion.longitud = right.posicion.longitud;
	estatus = right.estatus;
	usadoPor = right.usadoPor;
	return *this;
}

/**
*@Brief Método encargado de activar la moto
*@Param Cliente: usuario que activa la moto
*/
void Moto::seActiva(Cliente& usuario){
	if (estatus.bloqueada && !estatus.sinbateria && !estatus.roto){
		estatus.activa = true;
		estatus.bloqueada = false;
		usadoPor = &usuario;
	}
}

/**
*@Brief Método encargado de desactivar la moto
*/
void Moto::seDesactiva(){
	if (estatus.activa) {
		Cliente* aux = new Cliente("Nulo");
		estatus.activa = false;
		estatus.bloqueada = true;
		usadoPor = aux;
	}
}
/**
*@Brief Setter del campo sinBateria de estatus
*/
void Moto::setSinbateria(){
	estatus.sinbateria = true;
}
/**
*@Brief Setter del campo Roto de estatus
*/
void Moto::setRoto(){
	estatus.roto = true;
}
/**
*@Brief Calcula la distancia entre 2 motos
*/
double Moto::distanciaMoto(Moto& otro){
	return sqrt(pow(this->posicion.latitud - otro.posicion.latitud, 2) + pow(this->posicion.longitud - otro.posicion.longitud, 2));
}