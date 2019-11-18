#include "THashCliente.h"
#include <iostream>

//====================IMPLEMENTACIÓN DE LA CLASE ENTRADA====================

Entrada::Entrada() : cliente(""), clave(0)
{
}

Entrada::Entrada(Cliente& cli, unsigned long cla, EstadoHash _estado) : cliente(cli), clave(cla), estado(_estado)
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


//====================IMPLEMENTACIÓN DE LA CLASE THASHCLIENTE====================

unsigned long THashCliente::hash(unsigned long clave, int intento)
{
	return (clave + intento*intento) % tamatabla;
}

THashCliente::THashCliente()
{
	buffer = new vector<Entrada>;
}

THashCliente::THashCliente(int tamTabla) : tamatabla(tamTabla) {
	buffer = new vector<Entrada>(tamatabla);
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
/**
	@brief Inserta un cliente en la tabla
	@param clave Clave asociada al dni del cliente
	@param dni Atributo dni del cliente a insertar
	@param cliente Cliente a insertar
	@pre La clave debe coincidir con la codificacion djb2 del dni
	@throws std::invalid_argument si la clave no coincide con djb2(dni)
*/
bool THashCliente::insertar(unsigned long clave, string& dni, Cliente& cliente) {
	if (clave != djb2(dni))
		throw std::invalid_argument("[THashCliente::insertar] La clave no coincide con el dni");
	int intento = 0;
	unsigned long key = hash(clave, intento);
	while (intento < tamatabla && (*buffer)[key].estado == ocupado) {
		intento++;
		key = hash(clave, intento);
	}
	if (intento >= tamatabla) {
		return false;
	}
	if ((*buffer)[key].estado == borrado) {
		Entrada temp(cliente, clave, borrado);
		(*buffer)[key] = temp;
	}
	else {
		Entrada temp(cliente, clave, ocupado);
		(*buffer)[key] = temp;
	}
	return true;
	
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

//TODO: borrar esto cuando funcione la tabla
void THashCliente::verTabla()
{
	for (size_t i = 0; i < tamatabla; i++) {
		if ((*buffer)[i].estado != libre) {
			std::cout << "Posicion " << i << ": " << (*buffer)[i].cliente.toCSV() << std::endl;
		}
		else {
			std::cout << "Posicion " << i << ": Vacio" << std::endl;
		}
	}
}
