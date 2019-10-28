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
	Moto localizaMotoCercana(UTM posicion);
	void desbloqueaMoto(Moto m, Cliente cli);
	//Basicamente solo hay que utilizar el metodo de cada clase, pero es para tenerlo en la interfaz de usuario todo con EcoCityMoto, que si no te puedes pegar un tiro
	EcoCityMoto& insertaMoto(Moto& moto);
	EcoCityMoto& insertaCliente(Cliente& cliente);
	EcoCityMoto& insertaItinerario(Itinerario& itinerario, std::string dni);
	Moto& buscaMoto(std::string id);
	bool buscaCliente(std::string& dni, Cliente& clienteEncontrado);
	EcoCityMoto& borraMoto(int pos);
	EcoCityMoto& borraItinerario(int pos, std::string dni);
	unsigned int getAlturaAVL();
	EcoCityMoto& recorreAVLInorden();
	EcoCityMoto& verArbolCliente();

};


#endif // !ECOCITYMOTO_H