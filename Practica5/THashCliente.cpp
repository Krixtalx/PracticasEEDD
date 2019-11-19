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

/**
*@Brief Calcula y devuelve el hash 
*/
unsigned int THashCliente::hash(unsigned long clave, int intento)
{
	return (clave + intento*intento) % tamatabla;
}

/**
*@Brief Constructor por defecto
*/
THashCliente::THashCliente()
{
	buffer = new vector<Entrada>;
}

/**
*@Brief Constructor parametrizado
*/
THashCliente::THashCliente(int tamTabla) : tamatabla(tamTabla) {
	buffer = new vector<Entrada>(tamatabla);
}

/**
*@Brief Constructor de copia
*/
THashCliente::THashCliente(THashCliente& orig) : numclientes(orig.numclientes), tamatabla(orig.tamatabla), maxCol(orig.maxCol), numCol(orig.numCol)
{
	buffer = new vector<Entrada>(*orig.buffer);
}

THashCliente::~THashCliente(){
	delete buffer;
}

/**
*@Brief Operador =
*/
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

/**
*@Brief Implementación del algoritmo djb2 para el calculo del hash
*/
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
	unsigned int key = hash(clave, intento);
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
	numclientes++;
	numCol += intento;
	if (intento > maxCol)
		maxCol = intento;
	return true;
	
}

/**
	@brief Busca un cliente en la tabla
	@param clave Clave asociada al dni del cliente
	@param dni Atributo dni del cliente a buscar
	@param cliente Cliente a buscar
	@pre La clave debe coincidir con la codificacion djb2 del dni
	@throws std::invalid_argument si la clave no coincide con djb2(dni)
*/
bool THashCliente::buscar(unsigned long clave, string& dni, Cliente* &cliente)
{
	if (clave != djb2(dni))
		throw std::invalid_argument("[THashCliente::buscar] La clave no coincide con el dni");
	int intento = 0;
	unsigned long key = hash(clave, intento);
	while (intento < tamatabla && (*buffer)[key].estado != libre) {
		if ((*buffer)[key].clave == clave) {
			cliente = &((*buffer)[key].cliente);
			return true;
		}
	}
	return false;
	//TODO: actualizar stats
}

/**
*@Brief Función de borrado de un cliente
*/
bool THashCliente::borrar(unsigned long clave, string& dni)
{
	if (clave != djb2(dni))
		throw std::invalid_argument("[THashCliente::borrar] La clave no coincide con el dni");
	int intento = 0;
	unsigned long key = hash(clave, intento);
	while (intento < tamatabla && (*buffer)[key].estado != libre) {
		if ((*buffer)[key].clave == clave) {
			(*buffer)[key].estado = borrado;
			return true;
		}
	}
	return false;
}

/**
*@Brief Devuelve el nº de clientes en la tabla
*/
unsigned int THashCliente::numCliente()
{
	return numclientes;
}

/**
*@Brief Función encargada de redispersar la tabla cuando se supere el valor de carga
*/
void THashCliente::redispersar(unsigned tama)
{
}

/**
*@Brief Devuelve el nº máximo de colisiones que se han tenido
*/
unsigned int THashCliente::maxColisiones()
{
	return maxCol;
}

/**
*@Brief Devuelve la media de colisiones por inserción
*/
unsigned int THashCliente::promedioColisiones()
{
	return numCol/numclientes;
}

/**
*@Brief Devuelve el factor de carga de la tabla
*/
float THashCliente::factorCarga()
{
	return numclientes/tamatabla;
}

/**
*@Brief Devuelve el tamaño de la tabla hash
*/
unsigned int THashCliente::tamaTabla()
{
	return tamatabla;
}

//TODO: borrar esto cuando funcione la tabla
void THashCliente::verTabla()
{
	for (size_t i = 0; i < tamatabla; i++) {
		if ((*buffer)[i].estado == ocupado) {
			std::cout << "Posicion " << i << ": " << (*buffer)[i].cliente.toCSV() << std::endl;
		}
		else {
			std::cout << "Posicion " << i << ": Vacio" << std::endl;
		}
	}
}
