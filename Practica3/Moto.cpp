#include "Moto.h"

Moto::Moto() : id("0") {
}

Moto::Moto(const Moto& orig){
	id = orig.id;
	posicion = orig.posicion;
	estatus = orig.estatus;
	usadoPor = orig.usadoPor;
}

Moto::~Moto(){
}


void Moto::seActiva(Cliente usuario){
	if (estatus.bloqueada && !estatus.sinbateria && !estatus.roto){
		estatus.activa = true;
		estatus.bloqueada = false;
		usadoPor = usuario;
	}
}

void Moto::seDesactiva(){
	if (estatus.activa) {
		Cliente aux("Nulo");
		estatus.activa = false;
		estatus.bloqueada = true;
		usadoPor = aux;
	}
}

void Moto::setSinbateria(){
	estatus.sinbateria = true;
}

void Moto::setRoto(){
	estatus.roto = true;
}
