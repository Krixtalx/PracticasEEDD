#pragma once
#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H

#include <string>
#include <vector>
#include "Cliente.h"

using namespace std;

class THashCliente
{
	vector<Cliente>* buffer = 0;

	unsigned int numclientes = 0;
	unsigned int tamatabla = 0;
	unsigned int maxColisiones = 0;
	unsigned int numColisiones = 0;

	int hash(unsigned long clave, int intento);

public:
	THashCliente(int tamTabla);
	unsigned long djb2(string& palabra);
	bool insertar(unsigned long clave, string& dni, Cliente& cliente);
	bool buscar(unsigned long clave, string& dni, Cliente& cliente);
	bool borrar(unsigned long clave, string& dni);
	unsigned int numCliente();
	void redispersar(unsigned tama);
	unsigned int maxColisiones();
	unsigned int promedioColisiones();
	float factorCarga();
	unsigned int tamaTabla();

};

#endif // !THASHCLIENTE_H