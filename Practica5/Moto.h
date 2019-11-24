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
	void setUTM(UTM& _posicion);
	estatus getEstado();
	void setEstado(estatus _estado);
	std::string getDatosCliente();
	Cliente* getCliente();
	void seActiva(Cliente& usuario);
	void seDesactiva(int duracion, int limiteBateria);
	void setPorcentajeBateria(int porcentaje, int limiteBateria);
	int getPorcentajeBateria();
	double distanciaMoto(Moto& otro);
	double distanciaCliente(Cliente& cliente);
	void comprobarBateria(int limiteBateria);
};

#endif // !MOTO_H