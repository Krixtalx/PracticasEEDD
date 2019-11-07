#pragma once
#ifndef MOTO_H
#define MOTO_H

#include <string>
#include "Cliente.h"
#include "UTM.h"

struct Estado {
	bool bloqueada=false;
	bool activa=false;
	bool sinbateria = false;
	bool roto=false;
};

enum estatus {bloqueada = 0, activa, sinbateria, rota};

class Moto{
private:
	std::string id;
	UTM posicion;
	estatus estado = estatus::bloqueada;
	const static int limiteBateria = 15;
	int porcentajeBateria = 50;
	Cliente* usadoPor=0;
	friend class EcoCityMoto;
public:
	Moto();
	Moto(std::string id, UTM posicion, estatus _estado, int porcentajeBateria);
	Moto(const Moto& orig);
	~Moto();
	Moto& operator=(Moto& right);
	std::string getId();
	UTM& getUTM();
	estatus getEstado();
	std::string getDatosCliente();
	void seActiva(Cliente& usuario);
	void seDesactiva();
	void setPorcentajeBateria(int porcentaje);
	int getPorcentajeBateria();
	void setSinbateria();
	void setRoto();
	double distanciaMoto(Moto& otro);
	double distanciaCliente(Cliente& cliente);
};

#endif // !MOTO_H