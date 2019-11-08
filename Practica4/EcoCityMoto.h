#pragma once
#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include "Moto.h"
#include "Cliente.h"
#include <map>
#include <vector>

#include <cmath>

class EcoCityMoto
{
	unsigned idUltimo = 0;
	std::vector<Moto*>* motos = 0;
	std::map<std::string, Cliente>* clientes = 0;
	void cargaEEDD(string fichCli, string fichMotos);

public:
	EcoCityMoto();
	EcoCityMoto(unsigned _idUltimo);
	~EcoCityMoto();
	EcoCityMoto(EcoCityMoto& orig);
	EcoCityMoto& operator=(EcoCityMoto& right);
	Moto& localizaMotoCercana(UTM posicion);
	Moto& localizaMotoCercana(Cliente& cliente);
	void desbloqueaMoto(Moto& m, Cliente& cli);

	EcoCityMoto& insertaMoto(Moto* moto);
	Cliente* insertaCliente(Cliente& cliente);
	EcoCityMoto& insertaItinerario(Itinerario* itinerario, std::string dni);
	EcoCityMoto& crearItinerarios(UTM& min, UTM& max);
	std::string& verItinerario(Cliente& cliente);
	const std::string& verCliente(std::string& dni);
	bool buscaMoto(std::string id, Moto* &motoEncontrada);
	bool buscaCliente(std::string& dni, Cliente* &clienteEncontrado);
	EcoCityMoto& borraMoto(int pos);
	EcoCityMoto& borraItinerario(int pos, std::string dni);
	EcoCityMoto& recorreMapa();
	unsigned int idItinerario();
	unsigned int numeroClientes();
	void setIdUltimo(unsigned _id);
	Moto* localizaMotoSinBateria(float porctBateria);
	void borrarEEDD();
	int getNumClientes();

};


#endif // !ECOCITYMOTO_H