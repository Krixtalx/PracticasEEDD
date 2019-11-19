#pragma once
#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H

#include <string>
#include <vector>
#include "Cliente.h"

using namespace std;

enum EstadoHash{libre, ocupado, borrado};

class Entrada
{
	Cliente cliente;
	long clave;
	EstadoHash estado = EstadoHash::libre;
	friend class THashCliente;
public:
	Entrada();
	Entrada(Cliente& cli, unsigned long cla, EstadoHash _estado = libre);
	Entrada(Entrada& orig);
	~Entrada();
	Entrada& operator=(Entrada& right);
};

class THashCliente
{
	vector<Entrada>* buffer = 0;

	unsigned int numclientes = 0;
	unsigned int tamatabla = 0;
	unsigned int maxCol = 0;		//Maximo de colision en una operacion de insercion
	unsigned int numCol = 0;		//Numero total de colisiones de todas las inserciones

	unsigned int hash(unsigned long clave, int intento);
	int siguientePrimo(int x);

public:
	THashCliente();
	THashCliente(int tamatabla);
	THashCliente(THashCliente& orig);
	~THashCliente();
	THashCliente& operator=(THashCliente& right);
	unsigned long djb2(string& palabra);
	unsigned long djb2(const string& palabra);
	bool insertar(unsigned long clave, string& dni, Cliente& cliente);
	bool insertar(unsigned long clave, const string& dni, Cliente& cliente);
	bool buscar(unsigned long clave, string& dni, Cliente*& cliente);
	bool borrar(unsigned long clave, string& dni);
	unsigned int numCliente();
	void redispersar(unsigned tama);
	unsigned int maxColisiones();
	unsigned int promedioColisiones();
	float factorCarga();
	unsigned int tamaTabla();
	void verTabla();
};

#endif // !THASHCLIENTE_H