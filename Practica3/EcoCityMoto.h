#pragma once
#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include "AVL.h"
#include "VDinamico.h"
#include "Cliente.h"
#include "Moto.h"

#include <cmath>

class EcoCityMoto
{
	unsigned idUltimo = 0;
	VDinamico<Moto>* motos = 0;
	AVL<Cliente>* clientes = 0;

public:
	EcoCityMoto();
	EcoCityMoto(unsigned _idUltimo);
	~EcoCityMoto();
	EcoCityMoto(EcoCityMoto& orig);
	EcoCityMoto& operator=(EcoCityMoto& right);
	Moto localizaMotoCercana(UTM posicion);
	void desbloqueaMoto(Moto m, Cliente cli);
	EcoCityMoto& insertaMoto(Moto& moto);
	EcoCityMoto& insertaCliente(Cliente& cliente);
	EcoCityMoto& insertaItinerario(Itinerario& itinerario);
	EcoCityMoto& buscaMoto(std::string id);
	EcoCityMoto& buscaCliente(std::string dni);
	EcoCityMoto& borraMoto(int pos);
	EcoCityMoto& borraItinerario(int pos);

};


#endif // !ECOCITYMOTO_H