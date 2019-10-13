#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <exception>

#include "VDinamico.h"
#include "Cliente.h"
#include "ListaDEnlazada.h"
#include "Fecha.h"

using namespace std;

/**
 * @brief Muestra el tamaño del vector Dinamico
 * @param vD: Vector dinamico del que mostrar el tamaño
 */
void mostrarVDinCliente(VDinamico<Cliente>& vD) {
	cout << "tamF: " << vD.getTamF() << " tamL:" << vD.getTamL() << endl;
}

/**
 * @brief Calcula la mayor distancia entre los elementos del vector Dinamico
 * @param vD: Vector dinamico de clientes del que se calcularan las distancias
 * @param pos1: Donde se almacenará la posición del primer cliente
 * @param pos2: Donde se almacenará la posicion del segundo cliente
 * @param distancia: Donde se almacenará la distancia entre los 2
 */
void CalcularMayorDistancia(VDinamico<Cliente>& vD, int& pos1, int& pos2, double& distancia) {
	double max = -1;

	for (int i = 0; i < vD.getTamL(); i++) {
		for (int j = i + 1; j < vD.getTamL(); j++) {
			distancia = vD[i].DistanciaCliente(vD[j]);
			if (distancia > max) {
				max = distancia;
				pos1 = i;
				pos2 = j;
			}
		}
	}
	distancia = max;
}

void leeClientes(string fileNameClientes, VDinamico<Cliente>* vector) {
	ifstream fe; //Flujo de entrada
	string linea; //Cada línea tiene un clienete
	int total = 0; //Contador de líneas o clientes

	//Variables auxiliares para almacenar los valores leídos
	string dni, nombre, apellido, pass, direccion, latitud, longitud;
	double dlat, dlon;

	//Asociamos el flujo al fichero
	fe.open(fileNameClientes);

	if (fe.good()) {
		//Mientras no se haya llegado al final del fichero
		while (!fe.eof()) {
			getline(fe, linea); //Toma una línea del fichero
			stringstream ss; //Stream que trabaja sobre buffer interno

			if (linea != "") {
				++total;
			}

			if (total > 1) {
				//Inicializamos el contenido de ss
				ss << linea;

				//Leemos el NIF
				getline(ss, dni, ';'); //El carácter ; se lee y se elimina de ss

				//Leemos el pass
				getline(ss, pass, ';'); //El caráter ; se lee y se elimina de ss

				//Leemos el nombre
				getline(ss, nombre, ' '); //El caráter ' ' se lee y se elimina de ss

				//Leemos el apellido
				getline(ss, apellido, ';'); //El carácter ; se lee y se elimina de ss

				//Leemos la dirección
				getline(ss, direccion, ';'); //El caráter ; se lee y se elimina de ss

				//Leemos la latitud y longitud
				getline(ss, latitud, ';'); //El caráter ; se lee y se elimina de ss
				getline(ss, longitud, ';'); //El caráter ; se lee y se elimina de ss

				dlat = stod(latitud);
				dlon = stod(longitud);

				//con todos los atributos leídos, se crea el cliente
				Cliente client(dni, pass, nombre, apellido, direccion, dlat, dlon);
				try {
					vector->insertarDato(client);
				}
				catch (const std::bad_alloc & e) {
					std::cout << "bad_alloc: " << e.what() << '\n';
				}
				//cout << "leido e insertado cliente " << total << "  ";
			}
		}

		cout << "Total de clientes en el fichero: " << total << endl;
		fe.close(); //Cerramos el flujo de entrada
	}
	else {
		cerr << "No se puede abrir el fichero" << endl;
	}
}

int main(int argc, char** argv) {
/*
	VDinamico<Cliente>* vClientes = new VDinamico<Cliente>;

	cout << "Comienzo de lectura de un fichero " << endl;
	leeClientes("clientes_v2.csv", vClientes);

	delete vClientes;
	*/

	ListaDEnlazada<int> test;
	int a = 6, b = 2, c = 10, d = 4;
	test.insertaFinal(a).insertaFinal(b).insertaFinal(c);
	Iterador<int> ite = test.iterador();
	ite++;
	test.inserta(ite, d);
	test.borra(ite);
	ite = test.iterador();
	while(!ite.final()) {
		cout << ite.getNodo()->GetDato() << endl;
		ite++;
	}
	return 0;
}

