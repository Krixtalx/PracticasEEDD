#include "THashCliente.h"
#include <iostream>

//====================IMPLEMENTACIÓN DE LA CLASE ENTRADA====================

Entrada::Entrada() : cliente(), clave(0)
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
*@Brief Calcula y devuelve el hash 1
*/
unsigned int THashCliente::hash1(unsigned long clave, int intento)
{
	return (clave + intento*intento) % tamatabla;
}

/**
*@Brief Calcula y devuelve el hash 2
*/
unsigned int THashCliente::hash2(unsigned long clave, int intento)
{
	return ( clave + ( (intento * intento) * ( (clave / (intento+sumHash2)) % primoHash2 ) ) ) % tamatabla;
}

/**
*@Brief Calcula y devuelve el hash 3
*/
unsigned int THashCliente::hash3(unsigned long clave, int intento)
{
	return (hash1(clave,intento) + hash2(clave, intento)) % tamatabla;
}

/**
*@Brief Calcula y devuelve el hash 4
*/
unsigned int THashCliente::hash4(unsigned long clave, int intento)
{
	//Cuidado, esto es muy eficiente y puede explotar su CPU: ((((clave << 5 ^ intento * clave) / (intento + 7) % tamatabla) + intento * intento) >> 2) % tamatabla
	return (((((clave << 5 ^ intento) * clave) / (intento + 7) ^ clave >> 3) + intento * intento) >> 2) % tamatabla;
}

/**
*@Brief Calcula y devuelve el hash 5
*/
unsigned int THashCliente::hash5(unsigned long clave, int intento)
{
	return (((clave << 3) * intento * intento) ^ (clave >> 2 / (intento + 1))) % tamatabla;
}

/**
*@Brief Calcula y devuelve el hash 6
*/
unsigned int THashCliente::hash6(unsigned long clave, int intento)
{
	//return (((hash5(clave, intento) ^ (clave << 2 * intento)) / (intento + 1 + hash4(clave, intento))) + intento * intento) % tamatabla;
	return (((hash5(clave, intento) * (clave >> 1 * intento)<<2) ^ (intento + 1 + hash4(clave, intento))) + intento * intento) % tamatabla;
}
/**
*@brief Devuelve el primer número primo mayor que el valor indicado
*/
unsigned THashCliente::siguientePrimo(int x) {
	if (x <= 1)
		return 2;
	if (x == 2)
		return 3;
	if (x == 3)
		return 5;
	unsigned primo = x + 1;
	if (primo % 2 == 0)
		primo++;
	while (true) {
		bool hayDivisor = false;
		for (int i = 3; i <= floor(sqrt(primo)); i += 2) {
			if (primo % i == 0) {
				hayDivisor = true;
				break;
			}
		}
		if (!hayDivisor)
			return primo;
		else
			primo += 2;
	}
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
	tamInicial = tamTabla;
}

/**
*@Brief Constructor de copia
*/
THashCliente::THashCliente(THashCliente& orig) : numclientes(orig.numclientes), tamatabla(orig.tamatabla), maxCol(orig.maxCol), numCol(orig.numCol),primoHash2(orig.primoHash2)
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
*@Brief Implementación del algoritmo djb2 para el calculo del hash con const string
*/
unsigned long THashCliente::djb2(const string& palabra) {
	unsigned long hash = 5381;
	int c;

	for (unsigned i = 0; i < palabra.length(); i++) {
		c = (unsigned long)palabra[i];
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

/**
*@brief Inserta un cliente en la tabla
*@param clave Clave asociada al dni del cliente
*@param dni Atributo dni del cliente a insertar
*@param cliente Cliente a insertar
*@pre La clave debe coincidir con la codificación djb2 del dni, el dni debe ser una constante
*@throws std::invalid_argument si la clave no coincide con djb2(dni)
*/
bool THashCliente::insertar(unsigned long clave, const string& dni, Cliente& cliente) {
	if (clave != djb2(dni))
		throw std::invalid_argument("[THashCliente::insertar] La clave no coincide con el dni");
	unsigned int intento = 0;
	unsigned int key = hash2(clave, intento);
	while (intento < tamatabla && (*buffer)[key].estado == ocupado) {
		intento++;
		key = hash2(clave, intento);
	}
	if (intento >= tamatabla) {
		return false;
	}
	/*if ((*buffer)[key].estado == borrado) {
		Entrada temp(cliente, clave, borrado);
		(*buffer)[key] = temp;
	}
	else {
		Entrada temp(cliente, clave, ocupado);
		(*buffer)[key] = temp;
	}*/
	Entrada temp(cliente, clave, ocupado);
	(*buffer)[key] = temp;
	numclientes++;
	numCol += intento;
	if (intento > maxCol)
		maxCol = intento;
	colUltimo = intento;
	if (factorCarga() > 0.7)
		redispersar(numclientes/pNuevaTabla);
	return true;

}

/**
*@brief Busca un cliente en la tabla
*@param clave Clave asociada al dni del cliente
*@param dni Atributo dni del cliente a buscar
*@param cliente Cliente a buscar
*@pre La clave debe coincidir con la codificación djb2 del dni
*@throws std::invalid_argument si la clave no coincide con djb2(dni)
*/
bool THashCliente::buscar(unsigned long clave, string& dni, Cliente* &cliente)
{
	if (clave != djb2(dni))
		throw std::invalid_argument("[THashCliente::buscar] La clave no coincide con el dni");
	unsigned int intento = 0;
	unsigned long key = hash2(clave, intento);
	while (intento < tamatabla && (*buffer)[key].estado != libre) {
		if ((*buffer)[key].estado != borrado) {
			if ((*buffer)[key].clave == clave) {
				cliente = &((*buffer)[key].cliente);
				return true;
			}
		}
		intento++;
		key = hash2(clave, intento);
	}
	return false;
}

/**
*@Brief Borra un cliente de la tabla
*@param clave Clave asociada al dni del cliente
*@param dni Atributo dni del cliente a borrar
*@pre La clave debe coincidir con la codificación djb2 del dni
*@post La entrada correspodiente a la clave se marca como borrada
*@throws std::invalid_argument si la clave no coincide con djb2(dni)
*/
bool THashCliente::borrar(unsigned long clave, string& dni)
{
	if (clave != djb2(dni))
		throw std::invalid_argument("[THashCliente::borrar] La clave no coincide con el dni");
	unsigned int intento = 0;
	unsigned long key = hash2(clave, intento);

	while (intento < tamatabla && (*buffer)[key].estado != libre) {
		if ((*buffer)[key].estado == ocupado && (*buffer)[key].clave == clave) {
			(*buffer)[key].estado = borrado;
			numclientes--;
			if (factorCarga() < 0.6) {
				redispersar(numclientes / 0.61);
			}
			return true;
		}
		intento++;
		key = hash2(clave, intento);
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
void THashCliente::redispersar(unsigned tama){
	if (tama < 0)
		throw std::invalid_argument("[THashCliente::redispersar] El tam no puede ser negativo");
	cout << endl << "REDISPERSANDO A " << tama << endl;
	unsigned nuevoTam = siguientePrimo(tama);
	THashCliente* aux = new THashCliente(nuevoTam);
	for (unsigned i = 0; i < this->tamatabla; i++) {
		if ((*buffer)[i].estado == EstadoHash::ocupado) {
			aux->insertar((*buffer)[i].clave, (*buffer)[i].cliente.getDni(), (*buffer)[i].cliente);
		}
	}
	*this = *aux;
	delete aux;
}

void THashCliente::recalcular()
{
	THashCliente* aux = new THashCliente(tamatabla);
	for (unsigned i = 0; i < this->tamatabla; i++) {
		if ((*buffer)[i].estado == EstadoHash::ocupado) {
			aux->insertar((*buffer)[i].clave, (*buffer)[i].cliente.getDni(), (*buffer)[i].cliente);
		}
	}
	*this = *aux;
	delete aux;
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
float THashCliente::promedioColisiones()
{
	return (float)numCol/numclientes;
}

/**
*@Brief Devuelve el factor de carga de la tabla
*/
float THashCliente::factorCarga()
{
	return (float)numclientes/tamatabla;
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
			std::cout << "Posicion " << i << ": " << (*buffer)[i].clave << " " << (*buffer)[i].cliente.toCSV() << std::endl;
		}
		else {
			std::cout << "Posicion " << i << ": Vacio" << std::endl;
		}
	}
}

vector<Entrada>::iterator THashCliente::iteradorInicio()
{
	return buffer->begin();
}

vector<Entrada>::iterator THashCliente::iteradorFinal()
{
	return buffer->end();
}

unsigned THashCliente::ultimasColisiones()
{
	return colUltimo;
}
