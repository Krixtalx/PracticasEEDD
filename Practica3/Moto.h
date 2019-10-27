#pragma once
#ifndef MOTO_H
#define MOTO_H

#include <string>
#include "UTM.h"
#include "Cliente.h"

struct Estado {
	bool bloqueada=false;
	bool activa=false;
	bool sinbateria=false;
	bool roto=false;
};

class Moto{
private:
	std::string id;
	UTM posicion;
	Estado estatus;
	Cliente usadoPor;
public:
	Moto();
	Moto(std::string id, UTM posicion, Estado estatus, Cliente usadoPor);
	Moto(const Moto& orig);
	~Moto();
	void seActiva(Cliente usuario);
	void seDesactiva();
	void setSinbateria();
	void setRoto();
	double distanciaMoto(Moto& otro);
};

#endif // !MOTO_H