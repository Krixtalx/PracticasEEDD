#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "EcoCityMoto.h"

using namespace std;

/**
	@brief Espacio de nombres que agrupa los distintos metodos para leer ficheros
*/
namespace leerFich {
	/**
		@brief Metodo encargado de cargar las motos de un fichero y almacenarlas
		@param fichMotos Fichero del que se leeran las motos
		@param app Puntero al objeto EcoCityMoto donde se almacenaran las motos
		@pre El fichero de motos debe tener formato CSV (Matricula;estado;latitud;longitud)
	*/
	void leeMotos(string fichMotos, EcoCityMoto* app);

	/**
		@brief Metodo encargado de leer un cliente de una linea de texto y almacenarlo
		@param csv Cadena de caracteres que almacena la informacion en formato CSV
		@param ecocity Puntero al objeto EcoCityMoto donde almacenar el Cliente
		@param cliactivo Puntero al cliente recien insertado
		@pre La cadena de caracteres debe tener formato CSV (nif;clave;nombreyapellidos;direccion;latitud;longitud)
	*/
	void leeLineaCliente(string& csv, EcoCityMoto* ecocity, Cliente*& cliActivo);

	/**
		@brief Metodo encargado de leer clientes e itinerarios de un fichero
		@param archivo Fichero del que leer la informacion
		@param ecocity Puntero al objeto EcoCityMoto donde se almacenaran los clientes
		@pre El fichero debe estar en formato CSV indicando con '-' el inicio de cada linea de cliente
	*/
	void leeItinerariosYClientes(string archivo, EcoCityMoto* ecocity);

	/**
		@brief Metodo encargado de leer clientes de un fichero
		@param archivo Fichero del que leer los clientes en formato CSV
		@param ecocity Puntero al objeto EcoCityMoto donde se almacenaran los clientes
		@pre El fichero debe estar en formato CSV (nif;clave;nombreyapellidos;direccion;latitud;longitud)
	*/
	void leeClientes(string archivo, EcoCityMoto* ecocity);

	std::vector<Cliente*>* ficheroaVector(string& fichero);
	void vectorClientes(string& archivo, std::vector<Cliente*>* v);
}