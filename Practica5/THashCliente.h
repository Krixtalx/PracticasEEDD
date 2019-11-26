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
public:
	Cliente cliente;
	long clave;
	EstadoHash estado = EstadoHash::libre;

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
	unsigned int colUltimo = 0;

	unsigned int hash1(unsigned long clave, int intento);
	unsigned int hash2(unsigned long clave, int intento);
	unsigned int hash3(unsigned long clave, int intento);
	unsigned int hash4(unsigned long clave, int intento);
	unsigned int hash5(unsigned long clave, int intento);
	unsigned int hash6(unsigned long clave, int intento);
	

public:
	float pNuevaTabla = 0.61;
	unsigned sumHash2 = 467;    //1 
	unsigned primoHash2 = 103;//1103 
	unsigned tamInicial = 1000;
	unsigned siguientePrimo(int x);

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
	void recalcular();
	unsigned int maxColisiones();
	float promedioColisiones();
	float factorCarga();
	unsigned int tamaTabla();
	void verTabla();
	vector<Entrada>::iterator iteradorInicio();
	vector<Entrada>::iterator iteradorFinal();
	unsigned ultimasColisiones();
};

#endif // !THASHCLIENTE_H