#pragma once
#ifndef MOTO_H
#define MOTO_H

#include <string>
#include "Cliente.h"
#include "UTM.h"

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
	Cliente* usadoPor=0;
	friend class EcoCityMoto;
public:
	Moto();
	Moto(std::string id, UTM posicion, Estado estatus);
	Moto(const Moto& orig);
	~Moto();
	Moto& operator=(Moto& right);
	std::string getId();
	UTM& getUTM();
	void seActiva(Cliente& usuario);
	void seDesactiva();
	void setSinbateria();
	void setRoto();
	double distanciaMoto(Moto& otro);
	double distanciaCliente(Cliente& cliente);
};

#endif // !MOTO_H