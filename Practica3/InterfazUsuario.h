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
	}
	clearScreen();
}

void insertarCliente(EcoCityMoto& ecocity) {

}

void buscarCliente(EcoCityMoto& ecocity) {

}

void clientetoCSV(EcoCityMoto& ecocity) {

}

void menuArbol(EcoCityMoto& ecocity) {

}

void menuClientes(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Clientes" << endl << endl;
	cout << "1 - Insertar cliente" << endl;
	cout << "2 - Buscar cliente" << endl;
	cout << "3 - Cliente a CSV" << endl;
	cout << "4 - Ajustes del arbol" << endl;
	cout << "5- Salir" << endl;
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

void menuItinerarios(EcoCityMoto& ecocity) {
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

void insertarMoto(EcoCityMoto& ecocity) {

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
	while (opcion != 7) {
		cout << endl << endl << "Programa de Gestión de EcoCityMoto" << endl << endl;
		cout << "1 - Instrucciones" << endl;
		cout << "2 - Configuracion" << endl;
		cout << "3 - Clientes" << endl;
		cout << "4 - Itinerarios" << endl;
		cout << "5 - Motos" << endl;
		cout << "6 - Carga CSV" << endl;
		cout << "7 - Salir" << endl;
		cout << "¿Que desea hacer?: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			clearScreen();
			cout << "Cada opcion lleva a un submenu que se encarga donde habra nuevas opciones para realizar acciones relacionadas con el nombre del menu" << endl
				<< "En concreto, el submenu de Configuracion permite seleccionar el sistema operativo en el que se encuentra para la limpieza de la consola" << endl;
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
			menuItinerarios(ecocity);
			break;

		case 5:
			clearScreen();
			menuMotos(ecocity);
			break;

		case 6:
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