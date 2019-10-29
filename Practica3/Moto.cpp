#include "Moto.h"

Moto::Moto() : id("0") {
}

Moto::Moto(std::string id, UTM posicion, Estado estatus): id(id), posicion(posicion), estatus(estatus), usadoPor(0){
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

std::string Moto::getId()
{
	return id;
}

UTM& Moto::getUTM()
{
	return posicion;
}

/**
*@Brief M�todo encargado de activar la moto
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
*@Brief M�todo encargado de desactivar la moto
*/
void Moto::seDesactiva(){
	if (estatus.activa) {
		//Cliente* aux = new Cliente("Nulo");
		estatus.activa = false;
		estatus.bloqueada = true;
		usadoPor = 0;
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

double Moto::distanciaCliente(Cliente& cliente){
	if (estatus.bloqueada && !estatus.roto && !estatus.sinbateria) {
		return sqrt(pow(this->posicion.latitud - cliente.getPosicion().latitud, 2) + pow(this->posicion.longitud - cliente.getPosicion().longitud, 2));
	}
	return 99999999.99;
}
