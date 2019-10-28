#pragma once

#include <iostream>
#include <fstream>
#include "AVL.h"
#include "Cliente.h"
#include "ListaDEnlazada.h"
#include "Itinerario.h"
#include "VDinamico.h"
#include "Moto.h"
#include "EcoCityMoto.h"

using namespace std;

bool windows = true;
string archivoClientes="clientes.csv";
string archivoMotos = "motos.txt";

bool menuPrincipal(EcoCityMoto& ecocity);
void leeClientes(string fileNameClientes, EcoCityMoto& ecocity);
void leeMotos(string fileNameMotos, EcoCityMoto& ecocity);

void clearScreen() {
	if (windows) {
		system("cls");
	}
	else {
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	}
}

void configuracion(EcoCityMoto& ecocity) {
	int opt = 0;
	cout << "1 - Modificar archivo CSV de Clientes" << endl;
	cout << "2 - Modificar archivo CSV de Motos" << endl;
	cout << "3 - Modificar configuración de Sistema Operativo" << endl;
	cout << "4 - Salir" << endl;
	cout << "Introduzca la opción: ";
	cin >> opt;
	
	switch (opt) {
		case 1:
			clearScreen();
			cout << "Nuevo archivo CSV de clientes: ";
			getline(cin>>ws, archivoClientes);
			break;
		case 2:
			clearScreen();
			cout << "Nuevo archivo CSV de Motos: ";
			getline(cin>>ws, archivoMotos);
			break;
		case 3:
			char opcion;
			clearScreen();
			cout << "¿Que sistema operativo usa?" << endl << "W para windows, L para otro" << endl;
			cin >> opcion;
			if (opcion == 'W') {
				windows = true;
			}
			else if (opcion == 'L') {
				windows = false;
			}
			clearScreen();
			break;

		case 4:
			clearScreen();
			return;
			break;
	}

	clearScreen();
}

void insertarCliente(EcoCityMoto& ecocity) {
	string nombre, apellidos, dni, pass, direccion;
	double longitud, latitud;
	cout << "Introduzca el nombre del cliente: ";
	getline(cin >> ws, nombre);
	cout << "Introduzca el apellido del cliente: ";
	getline(cin >> ws, apellidos);
	cout << "Introduzca el DNI del cliente: ";
	getline(cin >> ws, dni);
	cout << "Introduzca la pass del cliente: ";
	getline(cin >> ws, pass);
	cout << "Introduzca la dirección del cliente: ";
	getline(cin >> ws, direccion);

	cout << "Introduzca la latitud del cliente: ";
	cin >> latitud;
	cout << "Introduzca la longitud del cliente: ";
	cin >> longitud;

	Cliente cliente(dni, pass, nombre, apellidos, direccion, latitud, longitud);
	ecocity.insertaCliente(cliente);
}

Cliente& buscarCliente(EcoCityMoto& ecocity){
	string dni;
	bool encontrado;
	cout << "Introduzca el DNI del cliente a buscar: ";
	getline(cin >> ws, dni);
	Cliente aux(ecocity.buscaCliente(dni, encontrado));
	if (encontrado) {
		cout << "Cliente encontrado";
		return aux;
	}
	else
		cout << "Cliente no encontrado";
}

void clientetoCSV(EcoCityMoto& ecocity) {

}

void alturaArbol(EcoCityMoto& ecocity) {

}

void recorridoInorden(EcoCityMoto& ecocity) {

}

void visualizaArbol(EcoCityMoto& ecocity) {

}

void menuArbol(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Árbol" << endl << endl;
	cout << "1 - Ver altura del Árbol" << endl;
	cout << "2 - Recorrido en Inorden" << endl;
	cout << "3 - Visualiza Árbol en consola" << endl;
	cout << "4 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion) {
	case 1:
		clearScreen();
		alturaArbol(ecocity);
		break;

	case 2:
		clearScreen();
		recorridoInorden(ecocity);
		break;

	case 3:
		clearScreen();
		visualizaArbol(ecocity);
		break;

	case 4:
		clearScreen();
		return;
		break;
	}
}


void insertarItinerario(EcoCityMoto& ecocity) {

}

void borrarItinerario(EcoCityMoto& ecocity) {

}

void itinerariotoCSV(EcoCityMoto& ecocity) {

}

void menuItinerarios(EcoCityMoto& ecocity, Cliente& cliente) {
	int opcion;
	cout << endl << endl << "Submenu de Itinerario" << endl << endl;
	cout << "1 - Insertar itinerario" << endl;
	cout << "2 - Borrar itinerario" << endl;
	cout << "3 - Itinerario a CSV" << endl;
	cout << "4 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion) {
	case 1:
		clearScreen();
		insertarItinerario(ecocity);
		break;

	case 2:
		clearScreen();
		borrarItinerario(ecocity);
		break;

	case 3:
		clearScreen();
		itinerariotoCSV(ecocity);
		break;

	case 4:
		clearScreen();
		return;
		break;
	}
}

void accesoItinerarios(EcoCityMoto& ecocity) {
	Cliente cliente(buscarCliente(ecocity));
	menuItinerarios(ecocity, cliente);
}

void asignarMoto(EcoCityMoto& ecocity) {

}

void menuClientes(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Clientes" << endl << endl;
	cout << "1 - Insertar cliente" << endl;
	cout << "2 - Buscar cliente" << endl;
	cout << "3 - Cliente a CSV" << endl;
	cout << "4 - Ajustes del árbol" << endl;
	cout << "5 - Acceso a itinerarios de un cliente" << endl;
	cout << "6 - Asignar moto más cercana" << endl;
	cout << "7 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;

	switch (opcion) {
	case 1:
		clearScreen();
		insertarCliente(ecocity);
		break;

	case 2:
		clearScreen();
		buscarCliente(ecocity);
		break;

	case 3:
		clearScreen();
		clientetoCSV(ecocity);
		break;

	case 4:
		clearScreen();
		menuArbol(ecocity);
		break;

	case 5:
		clearScreen();
		accesoItinerarios(ecocity);
		break;

	case 6:
		clearScreen();
		asignarMoto(ecocity);
		break;

	case 7:
		clearScreen();
		return;
		break;
	}
}


void insertarMoto(EcoCityMoto& ecocity) {
	string matricula;
	UTM utm;
	int estado;
	Estado estadoMoto;
	cout << "Introduzca la matricula de la moto: ";
	getline(cin >> ws, matricula);
	cout << "Introduzca la latitud en la que se encuentra la moto: ";
	cin >> utm.latitud;
	cout << "Introduzca la longitud en la que se encuentra la moto: ";
	cin >> utm.longitud;
	cout << "Introduzca el estado en el que se encuentra la moto (1 para bloqueado, 2 para activado, 3 para sinBateria, 4 para roto): ";
	cin >> estado;
	switch (estado) {
	case 1:
		estadoMoto.bloqueada = true;
		break;
	case 2:
		estadoMoto.activa = true;
		break;
	case 3:
		estadoMoto.sinbateria = true;
		break;
	case 4:
		estadoMoto.roto = true;
	}
	Moto moto(matricula, utm, estadoMoto);
	//ecocity.insertaMoto(moto);
	
}

void buscarMoto(EcoCityMoto& ecocity) {

}

void borrarMoto(EcoCityMoto& ecocity) {

}

void menuMotos(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Motos" << endl << endl;
	cout << "1 - Insertar moto" << endl;
	cout << "2 - Buscar moto" << endl;
	cout << "3 - Borrar moto" << endl;
	cout << "4 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion) {
	case 1:
		clearScreen();
		insertarMoto(ecocity);
		break;

	case 2:
		clearScreen();
		buscarMoto(ecocity);
		break;

	case 3:
		clearScreen();
		borrarMoto(ecocity);
		break;

	case 4:
		clearScreen();
		return;
		break;
	}
}

void carga(EcoCityMoto& ecocity) {
	cout << "Comenzando carga de Clientes..." << endl;
	leeClientes(archivoClientes, ecocity);
	cout << "Finalizando carga de Clientes..." << endl;
	cout << "Comenzando carga de Motos..." << endl;
	leeMotos(archivoMotos, ecocity);
	cout << "Finalizando carga de Motos..." << endl;
	clearScreen();
}

bool menuPrincipal(EcoCityMoto& ecocity) {
	int opcion=0;
	while (opcion != 6) {
		cout << endl << endl << "Programa de Gestión de EcoCityMoto" << endl << endl;
		cout << "1 - Instrucciones" << endl;
		cout << "2 - Configuracion" << endl;
		cout << "3 - Clientes (AVL)" << endl;
		cout << "4 - Motos (VDinamico)" << endl;
		cout << "5 - Carga CSV" << endl;
		cout << "6 - Salir" << endl;
		cout << "¿Que desea hacer?: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			clearScreen();
			cout << "Cada opcion lleva a un submenu que se encarga donde habra nuevas opciones para realizar acciones relacionadas con el nombre del menu" << endl
				<< "En concreto, el submenu de Configuracion permite seleccionar el sistema operativo en el que se encuentra para la limpieza de la consola y los archivos de carga CSV" << endl;
			break;

		case 2:
			clearScreen();
			configuracion(ecocity);
			break;

		case 3:
			clearScreen();
			menuClientes(ecocity);
			break;

		case 4:
			clearScreen();
			menuMotos(ecocity);
			break;

		case 5:
			clearScreen();
			carga(ecocity);
			break;
		}
	}
	clearScreen();
	return true;
}

void leeClientes(string fileNameClientes, EcoCityMoto& ecocity) {
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
					//ecocity.insertaCliente(client);
				}
				catch (const std::bad_alloc & e) {
					std::cout << "bad_alloc: " << e.what() << '\n';
				}
			}
		}

		cout << "Total de clientes en el fichero: " << total << endl;
		fe.close(); //Cerramos el flujo de entrada
	}
	else {
		cerr << "No se puede abrir el fichero" << endl;
	}
}

void leeMotos(string fileNameMotos, EcoCityMoto& ecocity) {
	ifstream fe; //Flujo de entrada
	string linea; //Cada línea tiene un clienete
	int total = 0; //Contador de líneas o clientes

	//Variables auxiliares para almacenar los valores leídos
	string matricula, estado, latitud, longitud;
	int iestado;
	double dlat, dlon;

	//Asociamos el flujo al fichero
	fe.open(fileNameMotos);

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

				//Leemos la matricula
				getline(ss, matricula, ';'); //El carácter ; se lee y se elimina de ss

				//Leemos el estado
				getline(ss, estado, ';'); //El caráter ; se lee y se elimina de ss
				iestado = stoi(estado);

				//Leemos la latitud y longitud
				getline(ss, latitud, ';'); //El caráter ; se lee y se elimina de ss
				getline(ss, longitud, ';'); //El caráter ; se lee y se elimina de ss
				
				dlat = stod(latitud);
				dlon = stod(longitud);

				//con todos los atributos leídos, se crea el cliente
				Estado estadoMoto;
				switch (iestado) {
				case 1:
					estadoMoto.bloqueada = true;
					break;
				case 2:
					estadoMoto.activa = true;
					break;
				case 3:
					estadoMoto.sinbateria = true;
					break;
				case 4:
					estadoMoto.roto = true;
				}

				UTM utm(dlat, dlon);

				Moto moto(matricula, utm, estadoMoto);
				try {
					//ecocity.insertaMoto(moto);
				}
				catch (const std::bad_alloc & e) {
					std::cout << "bad_alloc: " << e.what() << '\n';
				}
			}
		}

		cout << "Total de Motos en el fichero: " << total << endl;
		fe.close(); //Cerramos el flujo de entrada
	}
	else {
		cerr << "No se puede abrir el fichero" << endl;
	}
}