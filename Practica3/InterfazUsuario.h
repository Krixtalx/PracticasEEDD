#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "AVL.h"
#include "Cliente.h"
#include "ListaDEnlazada.h"
#include "Itinerario.h"
#include "VDinamico.h"
#include "Moto.h"
#include "EcoCityMoto.h"

using namespace std;

//Variables globales de configuracion
bool windows = true;
string archivoClientes="clientes.csv";
string archivoMotos = "motos.txt";

//Forward declaration
bool menuPrincipal(EcoCityMoto& ecocity);
void leeClientes(string fileNameClientes, EcoCityMoto& ecocity);
void leeMotos(string fileNameMotos, EcoCityMoto& ecocity);

/*
*@Brief funcion encargada de limpiar la pantalla
*/
void clearScreen() {
	if (windows) {
		system("cls");
	}
	else {
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	}
}

/*
*@Brief Submenú encargado de manejar la configuracion modificando las variables globales
*/
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

/*
*@Brief función encargada de recoger los datos para insertar un nuevo Cliente en el sistema
*/
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
	clearScreen();
}

/*
*@Brief Busca un cliente en el sistema a partir de su DNI 
*/
bool buscarCliente(EcoCityMoto& ecocity, Cliente& clienteEncontrado){
	string dni;
	cout << "Introduzca el DNI del cliente a buscar: ";
	getline(cin >> ws, dni);
	if (ecocity.buscaCliente(dni, clienteEncontrado)) {
		cout << "Cliente encontrado: "<<clienteEncontrado.GetNombreCompleto()<< "    UTM: "<<clienteEncontrado.getPosicion().toCSV();
		return true;
	}
	else
		cout << "Cliente no encontrado";
	return false;
}

/*
*@Brief Devuelve la altura del árbol AVL en el que están los clientes
*/
void alturaArbol(EcoCityMoto& ecocity) {
	cout << "La altura del árbol es " << ecocity.getAlturaAVL();
}

/*
*@Brief Muestra por consola el recorrido en Inorden del Arbol AVL en el que se encuentran los clientes
*/
void recorridoInorden(EcoCityMoto& ecocity) {
	char yon;
	cout << "Este recorrido puede generar una salida muy grande" << endl << "¿Está seguro de que quiere hacerlo?   S/n"<<endl;
	cin >> yon;
	if (yon == 'S') {
		clearScreen();
		cout << "Comenzando recorrido en Inorden del árbol..." << endl;
		ecocity.recorreAVLInorden();
	}
	else {
		clearScreen();
	}
}

/*
*@Brief Genera el arbol AVL formado por clientes en la consola. No sirve para un arbol AVL muy grande
*/
void visualizaArbol(EcoCityMoto& ecocity) {
	char yon;
	cout << "Esta función no funcionará correctamente con un gran número de Clientes" << endl << "¿Está seguro de que quiere hacerlo?   S/n" << endl;
	cin >> yon;
	if (yon == 'S') {
		clearScreen();
		ecocity.verArbolCliente();
	}
	else {
		clearScreen();
	}
}

/*
*@Brief Submenu de opciones del Arbol AVL de clientes
*/
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

/*
*@Brief Permite ver por consola los itinerarios que tiene un cliente
*/
void verItinerario(EcoCityMoto& ecocity, Cliente& cliente) {
	cout << "Itinerarios: " << endl;
	try {
		cout << ecocity.verItinerario(cliente);
	}
	catch (logic_error & e) {
		cerr << e.what();
	}
}

/*
*@Brief Permite borrar el ultimo itinerario del cliente
*/
void borrarItinerario(EcoCityMoto& ecocity, Cliente& cliente) {
	char yon;
	cout << "Se borrará el ultimo itinerario de cliente si tiene alguno" << " ¿Está seguro?      S/n" << endl;
	cin >> yon;
	if (yon == 'S') {
		clearScreen();
		if (cliente.getItinerarios().getTam() > 0) {
			cliente.getItinerarios().borrarFinal();
			cout << "Itinerario borrado";
		}
		else
			cout << "No tiene ningún itinerario";
	}
	else {
		clearScreen();
	}
}

/*
*@Brief Submenú para el manejo de itinerarios asociados a un cliente
*/
void menuItinerarios(EcoCityMoto& ecocity, Cliente& cliente) {
	int opcion;
	cout << endl << endl << "Submenu de Itinerario" << endl << endl;
	cout << "1 - Ver itinerarios" << endl;
	cout << "2 - Borrar último itinerario" << endl;
	cout << "3 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion) {
	case 1:
		clearScreen();
		verItinerario(ecocity, cliente);
		break;

	case 2:
		clearScreen();
		borrarItinerario(ecocity, cliente);
		break;

	case 3:
		clearScreen();
		return;
		break;
	}
}

/*
*@Brief Función encargada de garantizar el acceso a los Itinerarios de un cliente
*/
void accesoItinerarios(EcoCityMoto& ecocity) {
	Cliente cliente;
	if(buscarCliente(ecocity, cliente))
		menuItinerarios(ecocity, cliente);
}

/*
*@Brief Metodo encargado de asignar la motocicleta mas cercana al cliente introducido por DNI
*/
void asignarMoto(EcoCityMoto& ecocity) {
	string dni;
	Cliente cliente;
	Moto motoCercana;
	cout << "Introduzca el DNI del cliente al que se le asignará la moto: ";
	getline(cin >> ws, dni);
	if (ecocity.buscaCliente(dni, cliente)){
		clearScreen();
		cout << "Buscando moto más cercana a "<<cliente.getPosicion().toCSV()<<" ...";
		motoCercana = ecocity.localizaMotoCercana(cliente);
		motoCercana.seActiva(cliente);
		cliente.creaItinerario(motoCercana);
		cout <<endl<< "Moto encontrada y activada: "<<motoCercana.getId()<<"  -  "<<motoCercana.getUTM().toCSV();
	}
	else {
		clearScreen();
		cout << "DNI no encontrado";
	}
}

void bloquearMoto(EcoCityMoto& ecocity) {
	string dni;
	Cliente cliente;
	cout << "Introduzca el DNI del cliente al que se le bloqueará la moto: ";
	getline(cin >> ws, dni);
	if (ecocity.buscaCliente(dni, cliente)) {
		clearScreen();
		try {
			cliente.terminarTrayecto();
		}
		catch (std::runtime_error & e) {
			cerr << e.what();
			return;
		}
		cout << "Moto bloqueada";
	}
	else {
		clearScreen();
		cout << "DNI no encontrado";
	}
}

/*
*@Brief Submenu de Clientes
*/
void menuClientes(EcoCityMoto& ecocity) {
	int opcion;
	Cliente null;
	cout << endl << endl << "Submenu de Clientes" << endl << endl;
	cout << "1 - Insertar cliente" << endl;
	cout << "2 - Buscar cliente" << endl;
	cout << "3 - Ajustes del árbol" << endl;
	cout << "4 - Acceso a itinerarios de un cliente" << endl;
	cout << "5 - Asignar moto más cercana" << endl;
	cout << "6 - Bloquear moto de un cliente" << endl;
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
		buscarCliente(ecocity,null);
		break;

	case 3:
		clearScreen();
		menuArbol(ecocity);
		break;

	case 4:
		clearScreen();
		accesoItinerarios(ecocity);
		break;

	case 5:
		clearScreen();
		asignarMoto(ecocity);
		break;

	case 6:
		clearScreen();
		bloquearMoto(ecocity);
		break;

	case 7:
		clearScreen();
		return;
		break;
	}
}

/*
*@Brief Inserta una motocicleta en el vector dinámico de Motos con los datos introducidos por consola
*/
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
	ecocity.insertaMoto(moto);
	
}

/*
*@Brief Busca la moto atraves del ID introducido 
*/
void buscarMoto(EcoCityMoto& ecocity) {
	string matricula;
	cout << "Introduzca la matricula de la motocicleta: ";
	getline(cin >> ws, matricula);
	Moto moto;
	if (ecocity.buscaMoto(matricula, moto)) {
		cout << "Moto encontrada: " << moto.getId() << "    UTM: " << moto.getUTM().toCSV()<<endl;
		cout << "Estado de la moto: " << moto.getEstado();

	}
	else {
		cout << "Moto no encontrada.";
	}
}


/*
*@Brief Submenu de motos
*/
void menuMotos(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Motos" << endl << endl;
	cout << "1 - Insertar moto" << endl;
	cout << "2 - Buscar moto" << endl;
	cout << "3 - Salir" << endl;
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
		return;
		break;
	}
}

/*
*@Brief Funcion encargada de cargar los CSVs en memoria. Utiliza los nombres incluidos en las variables globales
*/
void carga(EcoCityMoto& ecocity) {
	cout << "Comenzando carga de Clientes..." << endl;
	leeClientes(archivoClientes, ecocity);
	cout << "Finalizando carga de Clientes..." << endl;
	cout << "Comenzando carga de Motos..." << endl;
	leeMotos(archivoMotos, ecocity);
	cout << "Finalizando carga de Motos..." << endl;
	//clearScreen();
}

/*
*@Brief Menu principal
*/
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

/*
*@Brief Metodo encargado de leer clientes de un CSV
*/
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
				
				setlocale(LC_ALL, "english");
				dlat = std::stod(latitud);
				dlon = std::stod(longitud);
				setlocale(LC_ALL, "spanish");
				//con todos los atributos leídos, se crea el cliente
				Cliente client(dni, pass, nombre, apellido, direccion, dlat, dlon);
				client.setAplicacion(&ecocity);
				try {
					ecocity.insertaCliente(client);
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

/*
*@Brief Metodo encargado de leer el CSV de motos
*/
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
				
				setlocale(LC_ALL, "english");
				dlat = stod(latitud);
				dlon = stod(longitud);
				setlocale(LC_ALL, "spanish");
				//con todos los atributos leídos, se crea el cliente
				Estado estadoMoto;
				switch (iestado) {
				case 0:
					estadoMoto.bloqueada = true;
					break;
				case 1:
					estadoMoto.activa = true;
					break;
				case 2:
					estadoMoto.sinbateria = true;
					break;
				case 3:
					estadoMoto.roto = true;
				}

				UTM utm(dlat, dlon);

				Moto moto(matricula, utm, estadoMoto);
				try {
					ecocity.insertaMoto(moto);
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