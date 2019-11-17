#include "THashCliente.h"

Entrada::Entrada() : cliente(""), clave(0)
{
}

Entrada::Entrada(Cliente& cli, unsigned long cla) : cliente(cli), clave(cla)
{
}

Entrada::Entrada(Entrada& orig) : cliente(orig.cliente), clave(orig.clave), estado(orig.estado)
{
}

Entrada::~Entrada()
{
}

Entrada& Entrada::operator=(Entrada& right)
{
	if (this == &right)
		return *this;
	cliente = right.cliente;
	clave = right.clave;
	estado = right.estado;
	return *this;
}

int THashCliente::hash(unsigned long clave, int intento)
{
	return 0;
}

THashCliente::THashCliente()
{
	buffer = new vector<Entrada>;
}

THashCliente::THashCliente(int tamTabla) : tamatabla(tamTabla) {
	buffer = new vector<Entrada>;
}

THashCliente::THashCliente(THashCliente& orig) : numclientes(orig.numclientes), tamatabla(orig.tamatabla), maxCol(orig.maxCol), numCol(orig.numCol)
{
	buffer = new vector<Entrada>(*orig.buffer);
}

THashCliente& THashCliente::operator=(THashCliente& right)
{
	if (this == &right)
		return *this;
	delete buffer;
	buffer = new vector<Entrada>(*right.buffer);
	numclientes = right.numclientes;
	tamatabla = right.tamatabla;
	maxCol = right.maxCol;
	numCol = right.numCol;
	return *this;
}

unsigned long THashCliente::djb2(string& palabra) {
	unsigned long hash = 5381;
	int c;

	for (unsigned i = 0; i < palabra.length(); i++) {
		c = (unsigned long)palabra[i];
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

bool THashCliente::insertar(unsigned long clave, string& dni, Cliente& cliente) {

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
	return numclientes;
}

void THashCliente::redispersar(unsigned tama)
{
}

unsigned int THashCliente::maxColisiones()
{
	return maxCol;
}

unsigned int THashCliente::promedioColisiones()
{
	return 0;
}

float THashCliente::factorCarga()
{
	return numclientes/tamatabla;
}

unsigned int THashCliente::tamaTabla()
{
	return tamatabla;
}