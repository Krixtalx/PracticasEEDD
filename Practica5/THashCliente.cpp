#include "THashCliente.h"

int THashCliente::hash(unsigned long clave, int intento)
{
	return 0;
}

THashCliente::THashCliente(int tamTabla): tamatabla(tamTabla){

}

unsigned long THashCliente::djb2(string& palabra){
	unsigned long hash = 5381;
	int c;

	for (int i = 0; i < palabra.length(); i++) {
		c = (unsigned long)palabra[i];
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

bool THashCliente::insertar(unsigned long clave, string& dni, Cliente& cliente){

	return false;
}

bool THashCliente::buscar(unsigned long clave, string& dni, Cliente& cliente)
{
	return false;
}

bool THashCliente::borrar(unsigned long clave, string& dni)
{
	return false;
}

unsigned int THashCliente::numCliente()
{
	return 0;
}

void THashCliente::redispersar(unsigned tama)
{
}

unsigned int THashCliente::maxColisiones()
{
	return 0;
}

unsigned int THashCliente::promedioColisiones()
{
	return 0;
}

float THashCliente::factorCarga()
{
	return 0.0f;
}

unsigned int THashCliente::tamaTabla()
{
	return 0;
}
