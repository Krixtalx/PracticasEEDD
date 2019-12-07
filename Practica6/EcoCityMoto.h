#pragma once
#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include "Moto.h"
#include "Cliente.h"
#include "THashCliente.h"
#include "MallaRegular.h"
#include "PuntoRecarga.h"
#include <map>
#include <vector>
#include <cmath>

class EcoCityMoto
{
	unsigned idUltimo = 0;
	std::vector<Moto*>* motos = 0;
	THashCliente* clientes = 0;
	MallaRegular<PuntoRecarga> recargas;
	void cargaEEDD(string fichCli, string fichMotos);
	const static int limiteBateria = 15;

public:
	EcoCityMoto();
	EcoCityMoto(unsigned _idUltimo, size_t tamTabla);
	~EcoCityMoto();
	EcoCityMoto(EcoCityMoto& orig);
	EcoCityMoto& operator=(EcoCityMoto& right);
	Moto& localizaMotoCercana(UTM posicion);
	Moto& localizaMotoCercana(Cliente& cliente);
	void desbloqueaMoto(Moto& m, Cliente& cli);

	EcoCityMoto& insertaMoto(Moto* moto);
	Cliente* insertaCliente(Cliente& cliente);
	bool nuevoCliente(Cliente& cliente);
	EcoCityMoto& insertaItinerario(Itinerario* itinerario, std::string dni);
	EcoCityMoto& crearItinerarios(UTM& min, UTM& max);
	std::string& verItinerario(Cliente& cliente);
	bool buscaMoto(std::string id, Moto* &motoEncontrada);
	Cliente* buscarCliente(std::string& dni);
	bool buscaCliente(std::string& dni, Cliente* &clienteEncontrado);
	EcoCityMoto& borraMoto(int pos);
	EcoCityMoto& borraItinerario(int pos, std::string dni);
	unsigned int idItinerario();
	void setIdUltimo(unsigned _id);
	vector<Moto*>* localizaMotoSinBateria();
	void borrarEEDD();
	void borraClientes();
	void borraMotos();
	unsigned getNumClientes();
	unsigned getNumMotos();
	Moto* getMotoAleatoria();
	int getLimiteBateria();
	bool eliminarCliente(std::string id);
	string estadoTabla();
	unsigned long claveString(string& dni);
	EcoCityMoto& vectorToTabla(std::vector<Cliente*>* v, unsigned tamInicio, unsigned primo, unsigned suma);
	void cargarClientes(string& archivo);
	void cargarMotos(string& archivo);
	void guardarClientesItinerarios(string& archivo);
	vector<string>* getDniClientes();
	unsigned ultimasColisiones();
	THashCliente* getTabla();

	void crearPuntosDeRecarga(UTM minimo, UTM maximo, int diviX, int diviY);
	string infoRecargas();
	PuntoRecarga* buscarCercano(float x, float y);
	void verPuntos();
};


#endif // !ECOCITYMOTO_H