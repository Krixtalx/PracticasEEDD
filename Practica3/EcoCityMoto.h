#pragma once
#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include "Moto.h"
#include "Cliente.h"
#include "AVL.h"
#include "VDinamico.h"

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
	Moto& localizaMotoCercana(UTM posicion);
	Moto& localizaMotoCercana(Cliente& cliente);
	void desbloqueaMoto(Moto m, Cliente cli);

	EcoCityMoto& insertaMoto(Moto& moto);
	EcoCityMoto& insertaCliente(Cliente& cliente);
	EcoCityMoto& insertaItinerario(Itinerario& itinerario, std::string dni);
	bool buscaMoto(std::string id, Moto& motoEncontrada);
	bool buscaCliente(std::string& dni, Cliente& clienteEncontrado);
	EcoCityMoto& borraMoto(int pos);
	EcoCityMoto& borraItinerario(int pos, std::string dni);
	unsigned int getAlturaAVL();
	EcoCityMoto& recorreAVLInorden();
	EcoCityMoto& verArbolCliente();

};


#endif // !ECOCITYMOTO_H