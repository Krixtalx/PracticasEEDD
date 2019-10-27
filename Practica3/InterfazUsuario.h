#pragma once

#include <iostream>
#include "AVL.h"
#include "Cliente.h"
#include "ListaDEnlazada.h"
#include "Itinerario.h"
#include "VDinamico.h"
#include "Moto.h"
#include "EcoCityMoto.h"

using namespace std;

bool windows = false;

void menuPrincipal(EcoCityMoto& ecocity);

void clearScreen() {
	if (windows) {
		system("cls");
	}
	else {
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	}
}

void configuracion() {
	char opcion;
	cout << "¿Que sistema operativo usa?" << endl << "W para windows, L para otro"<<endl;
	cin >> opcion;
	if (opcion == 'W') {
		windows = true;
	}
	else if (opcion == 'L') {
		windows = false;
	}
	else
		configuracion;
}

void insertarCliente(EcoCityMoto& ecocity) {

}

void buscarCliente(EcoCityMoto& ecocity) {

}

void borrarCliente(EcoCityMoto& ecocity) {

}

void clientetoCSV(EcoCityMoto& ecocity) {

}

void menuClientes(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Clientes" << endl << endl;
	cout << "1 - Insertar cliente" << endl;
	cout << "2 - Buscar cliente" << endl;
	cout << "3 - Borrar cliente" << endl;
	cout << "4 - Cliente a CSV" << endl;
	cout << "5 - Salir" << endl;
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
		borrarCliente(ecocity);
		break;

	case 4:
		clearScreen();
		clientetoCSV(ecocity);
		break;

	case 5:
		clearScreen();
		menuPrincipal(ecocity);
		break;
	}
}

void insertarItinerario(EcoCityMoto& ecocity) {

}

void buscarItinerario(EcoCityMoto& ecocity) {

}

void borrarItinerario(EcoCityMoto& ecocity) {

}

void itinerariotoCSV(EcoCityMoto& ecocity) {

}

void menuItinerarios(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Itinerario" << endl << endl;
	cout << "1 - Insertar itinerario" << endl;
	cout << "2 - Buscar itinerario" << endl;
	cout << "3 - Borrar itinerario" << endl;
	cout << "4 - Itinerario a CSV" << endl;
	cout << "5 - Salir" << endl;
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
		borrarCliente(ecocity);
		break;

	case 4:
		clearScreen();
		clientetoCSV(ecocity);
		break;

	case 5:
		clearScreen();
		menuPrincipal(ecocity);
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
		insertarCliente(ecocity);
		break;

	case 2:
		clearScreen();
		buscarCliente(ecocity);
		break;

	case 3:
		clearScreen();
		borrarCliente(ecocity);
		break;

	case 4:
		clearScreen();
		menuPrincipal(ecocity);
		break;
	}
}

void carga() {

}

void menuPrincipal(EcoCityMoto& ecocity) {
	int opcion;
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
			menuPrincipal(ecocity);
		break;

		case 2: 
			clearScreen();
			configuracion();
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
			carga();
			menuPrincipal(ecocity);
		break;

		case 7:
			clearScreen();
			return;
		break;
	}
}

