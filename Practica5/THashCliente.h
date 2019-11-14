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
	int numclientes = 0;
	int tamatabla = 0;
	int hash(unsigned long clave, int intento);
public:
	
	unsigned long djb2(string& palabra);
	bool insertar(unsigned long clave, string& dni, Cliente& cliente);
	void suicidarse(t_time* hora);
	

};

#endif // !THASHCLIENTE_H