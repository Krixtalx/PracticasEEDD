#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Cliente.h"
#include "Itinerario.h"
#include "Moto.h"
#include "EcoCityMoto.h"

using namespace std;

//Variables globales de configuracion
bool windows = true;
string archivoClientes="clientes.csv";
string archivoMotos = "motos.txt";
string archivoItinerarios = "itinerarios.txt";
Cliente* clienteaux= new Cliente;

//Forward declaration
bool menuPrincipal(EcoCityMoto& ecocity);
void leeClientes(string fileNameClientes, EcoCityMoto& ecocity);
void leeMotos(string fileNameMotos, EcoCityMoto& ecocity);
void leeItinerariosYClientes(string archivo, EcoCityMoto& ecocity);

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
*@Brief Submen� encargado de manejar la configuracion modificando las variables globales
*/
void configuracion(EcoCityMoto& ecocity) {
	int opt = 0;
	cout << "1 - Modificar archivo CSV de Clientes" << endl;
	cout << "2 - Modificar archivo CSV de Motos" << endl;
	cout << "3 - Modificar configuraci�n de Sistema Operativo" << endl;
	cout << "4 - Salir" << endl;
	cout << "Introduzca la opci�n: ";
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
			cout << "�Que sistema operativo usa?" << endl << "W para windows, L para otro" << endl;
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

		default:
			clearScreen();
			cout << "Opci�n invalida";
			break;
	}

	clearScreen();
}

/*
*@Brief funci�n encargada de recoger los datos para insertar un nuevo Cliente en el sistema
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
	cout << "Introduzca la direcci�n del cliente: ";
	getline(cin >> ws, direccion);

	cout << "Introduzca la latitud del cliente: ";
	cin >> latitud;
	cout << "Introduzca la longitud del cliente: ";
	cin >> longitud;

	Cliente cliente(dni, pass, nombre, apellidos, direccion, latitud, longitud);
	cliente.setAplicacion(&ecocity);
	ecocity.insertaCliente(cliente);
	clearScreen();
}

/*
*@Brief Busca un cliente en el sistema a partir de su DNI 
*/
bool buscarCliente(EcoCityMoto& ecocity, Cliente* &clienteEncontrado){
	string dni;
	cout << "Introduzca el DNI del cliente a buscar: ";
	getline(cin >> ws, dni);
	if (ecocity.buscaCliente(dni, clienteEncontrado)) {
		cout << "Cliente encontrado: "<<clienteEncontrado->GetNombreCompleto()<< "    UTM: "<<clienteEncontrado->getPosicion().toCSV();
		return true;
	}
	else
		cout << "Cliente no encontrado";
	return false;
}

//TODO: borrar esto :(
/*
*@Brief Devuelve la altura del �rbol AVL en el que est�n los clientes
*/
void alturaArbol(EcoCityMoto& ecocity) {
	//cout << "La altura del �rbol es " << ecocity.getAlturaAVL();
}

/*
*@Brief Muestra por consola el recorrido en Inorden del Arbol AVL en el que se encuentran los clientes
*/
void recorridoInorden(EcoCityMoto& ecocity) {
	char yon;
	cout << "Este recorrido puede generar una salida muy grande" << endl << "�Est� seguro de que quiere hacerlo?   S/n"<<endl;
	cin >> yon;
	if (yon == 'S') {
		clearScreen();
		cout << "Comenzando recorrido en Inorden del �rbol..." << endl;
		ecocity.recorreMapa();
	}
	else {
		clearScreen();
	}
}

//TODO: borrar esto tambien :(
/*
*@Brief Genera el arbol AVL formado por clientes en la consola. No sirve para un arbol AVL muy grande
*/
void visualizaArbol(EcoCityMoto& ecocity) {
	char yon;
	cout << "Esta funci�n no funcionar� correctamente con un gran n�mero de Clientes" << endl << "�Est� seguro de que quiere hacerlo?   S/n" << endl;
	cin >> yon;
	if (yon == 'S') {
		clearScreen();
		//ecocity.verArbolCliente();
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
	cout << endl << endl << "Submenu de �rbol" << endl << endl;
	cout << "1 - Ver altura del �rbol" << endl;
	cout << "2 - Recorrido en Inorden" << endl;
	cout << "3 - Visualiza �rbol en consola" << endl;
	cout << "4 - Salir" << endl;
	cout << "�Que desea hacer?: ";
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

	default:
		clearScreen();
		cout << "Opci�n invalida";
		break;
	}
}

/*
*@Brief Permite ver por consola los itinerarios que tiene un cliente
*/
void verItinerario(EcoCityMoto& ecocity, Cliente& cliente) {
	cout << "Itinerarios: " << endl;
	cout << "ID ; Duraci�n ; UTM Inicio ; UTM Final ; Fecha" << endl;
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
	cout << "Se borrar� el ultimo itinerario de cliente si tiene alguno" << " �Est� seguro?      S/n" << endl;
	cin >> yon;
	if (yon == 'S') {
		clearScreen();
		try {
			if (cliente.getItinerarios().size()) {
				cliente.getItinerarios().pop_back();
				cout << "Itinerario borrado";
			}
		}
		catch (std::logic_error & e) {
			cerr << endl << "No tiene ning�n itinerario para borrar";
		}
	}
	else {
		clearScreen();
	}
}

/*
*@Brief Submen� para el manejo de itinerarios asociados a un cliente
*/
void menuItinerarios(EcoCityMoto& ecocity, Cliente& cliente) {
	int opcion;
	cout << endl << endl << "Submenu de Itinerario" << endl << endl;
	cout << "1 - Ver itinerarios" << endl;
	cout << "2 - Borrar �ltimo itinerario" << endl;
	cout << "3 - Salir" << endl;
	cout << "�Que desea hacer?: ";
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

	default:
		clearScreen();
		cout << "Opci�n invalida";
		break;
	}
}

/*
*@Brief Funci�n encargada de garantizar el acceso a los Itinerarios de un cliente
*/
void accesoItinerarios(EcoCityMoto& ecocity) {
	Cliente* cliente;
	if(buscarCliente(ecocity, cliente))
		menuItinerarios(ecocity, *cliente);
}

/*
*@Brief Funci�n encargada de generar aleatoriamente itinerarios para todos los clientes
*/
void generaItinerarios(EcoCityMoto& ecocity) {
	if (!ecocity.numeroClientes()) {
		cout << "No hay clientes cargados en la aplicacion." << endl;
		return;
	}
	double min1, min2, max1, max2;
	cout << "Latitud m�nima: ";
	cin >> min1;
	cout << endl << "Latitud m�xima: ";
	cin >> max1;
	cout << endl << "Longitud m�nima: ";
	cin >> min2;
	cout << endl << "Longitud m�xima: ";
	cin >> max2;
	UTM minimo(min1, max2), maximo(max1, min2);
	ecocity.crearItinerarios(minimo, maximo);
	cout << endl << "Se han generado itinerarios para todos los clientes" << endl;
}

/*
*@Brief Metodo encargado de asignar la motocicleta mas cercana al cliente introducido por DNI
*/
void asignarMoto(EcoCityMoto& ecocity) {
	string dni;
	Moto* motoCercana;
	cout << "Introduzca el DNI del cliente al que se le asignar� la moto: ";
	getline(cin >> ws, dni);
	if (ecocity.buscaCliente(dni, clienteaux)){
		clearScreen();
		cout << "Buscando moto m�s cercana a "<<clienteaux->getPosicion().toCSV()<<" ..." << endl;
		try {
			motoCercana = &ecocity.localizaMotoCercana(*clienteaux);
			motoCercana->seActiva(*clienteaux);
			clienteaux->creaItinerario(*motoCercana);
			cout  << "Moto encontrada y activada: " << motoCercana->getId() << "  -  " << motoCercana->getUTM().toCSV();
		}
		catch (std::runtime_error & e) {
			cerr << e.what();
		}
		
	}
	else {
		clearScreen();
		cout << "DNI no encontrado";
	}
}

/*
*@Brief Metodo encargado de bloquear la motocicleta de un cliente introducido por DNI
*/
void bloquearMoto(EcoCityMoto& ecocity) {
	string dni;
	Cliente* cliente;
	cout << "Introduzca el DNI del cliente al que se le bloquear� la moto: ";
	getline(cin >> ws, dni);
	if (ecocity.buscaCliente(dni, cliente)) {
		clearScreen();
		try {
			cliente->terminarTrayecto();
			cliente->getItinerarios().back()->getVehiculo()->seDesactiva();
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
	cout << "3 - Ajustes del �rbol" << endl;
	cout << "4 - Acceso a itinerarios de un cliente" << endl;
	cout << "5 - Asignar moto m�s cercana" << endl;
	cout << "6 - Bloquear moto de un cliente" << endl;
	cout << "7 - Generar itinerarios aleatorios" << endl;
	cout << "8 - Salir" << endl;
	cout << "�Que desea hacer?: ";
	cin >> opcion;

	switch (opcion) {
	case 1:
		clearScreen();
		insertarCliente(ecocity);
		break;

	case 2:
		clearScreen();
		Cliente* temp;
		buscarCliente(ecocity,temp);
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
		generaItinerarios(ecocity);
		break;
	case 8:
		clearScreen();
		return;
		break;

	default:
		clearScreen();
		cout << "Opci�n invalida";
		break;
	}
}

/*
*@Brief Inserta una motocicleta en el vector din�mico de Motos con los datos introducidos por consola
*/
void insertarMoto(EcoCityMoto& ecocity) {
	string matricula;
	UTM utm;
	int estado;
	estatus estadoMoto;
	cout << "Introduzca la matricula de la moto: ";
	getline(cin >> ws, matricula);
	cout << "Introduzca la latitud en la que se encuentra la moto: ";
	cin >> utm.latitud;
	cout << "Introduzca la longitud en la que se encuentra la moto: ";
	cin >> utm.longitud;
	cout << "Introduzca el estado en el que se encuentra la moto (1 para bloqueado, 2 para activado, 3 para sinBateria, 4 para roto): ";
	cin >> estado;
	bool cinCorrecto = false;
	while (!cinCorrecto) {
		switch (estado) {
		case 1:
			estadoMoto = estatus::bloqueada;
			cinCorrecto = true;
			break;
		case 2:
			estadoMoto = estatus::activa;
			cinCorrecto = true;
			break;
		case 3:
			estadoMoto = estatus::sinbateria;
			cinCorrecto = true;
			break;
		case 4:
			estadoMoto = estatus::rota;
			cinCorrecto = true;
			break;
		default:
			cout << "Opci�n invalida";
			break;
		}
	}
	Moto* moto = new Moto(matricula, utm, estadoMoto, 1 + (rand() % 100));
	ecocity.insertaMoto(moto);
	
}

/*
*@Brief Busca la moto atraves del ID introducido 
*/
void buscarMoto(EcoCityMoto& ecocity) {
	string matricula;
	cout << "Introduzca la matricula de la motocicleta: ";
	getline(cin >> ws, matricula);
	Moto* moto = new Moto;
	if (ecocity.buscaMoto(matricula, moto)) {
		cout << "Moto encontrada: " << moto->getId() << "    UTM: " << moto->getUTM().toCSV()<<endl;
		cout << "Estado de la moto: " << moto->getEstado();
		try {
			if (moto->getEstado() == estatus::activa)
				cout << endl << moto->getDatosCliente();
		}
		catch (std::exception & e) {
			cerr << endl << e.what();
		}
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
	cout << "�Que desea hacer?: ";
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

	default:
		clearScreen();
		cout << "Opci�n invalida";
		break;
	}
}

/*
*@Brief Funcion encargada de cargar los CSVs en memoria. Utiliza los nombres incluidos en las variables globales
*/
void carga(EcoCityMoto& ecocity) {
	/*cout << "Comenzando carga de Clientes..." << endl;
	leeClientes(archivoClientes, ecocity);
	cout << "Finalizando carga de Clientes..." << endl;
	cout << "Comenzando carga de Motos..." << endl;
	leeMotos(archivoMotos, ecocity);
	cout << "Finalizando carga de Motos..." << endl;
	cout << "Comenzando carga de Itinerarios..." << endl;
	leeItinerarios(archivoItinerarios, ecocity);
	cout << "Finalizando carga de Itinerarios..." << endl;*/
	//clearScreen();
	cout << "Comenzando carga de Clientes e Itinerarios..." << endl;
	leeItinerariosYClientes(archivoItinerarios, ecocity);
	cout << "Finalizando carga de Clientes e Itinerarios..." << endl;
	cout << "Comenzando carga de Motos..." << endl;
	leeMotos(archivoMotos, ecocity);
	cout << "Finalizando carga de Motos..." << endl;
}

/*
*@Brief Menu principal
*/
bool menuPrincipal(EcoCityMoto& ecocity) {
	std::ifstream cargaItinerarios;
	cargaItinerarios.open("itinerarios.txt");
	if (cargaItinerarios.good()) {
		//TODO: cargar itinerarios en cada cliente
	}
	int opcion=0;
	while (opcion != 6) {
		cout << endl << endl << "Programa de Gesti�n de EcoCityMoto" << endl << endl;
		cout << "1 - Instrucciones" << endl;
		cout << "2 - Configuracion" << endl;
		cout << "3 - Clientes (AVL)" << endl;
		cout << "4 - Motos (VDinamico)" << endl;
		cout << "5 - Carga CSV" << endl;
		cout << "6 - Salir" << endl;
		cout << "�Que desea hacer?: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			clearScreen();
			cout << "Cada opcion lleva a un submenu donde habra nuevas opciones para realizar acciones relacionadas con el nombre del menu" << endl
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

		case 6:
			clearScreen();
			return true;
			break;

		default:
			clearScreen();
			cout << "Opci�n invalida";
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
	string linea; //Cada l�nea tiene un clienete
	int total = 0; //Contador de l�neas o clientes

	//Variables auxiliares para almacenar los valores le�dos
	string dni, nombre, apellido, pass, direccion, latitud, longitud;
	double dlat, dlon;

	//Asociamos el flujo al fichero
	fe.open(fileNameClientes);

	if (fe.good()) {
		//Mientras no se haya llegado al final del fichero
		while (!fe.eof()) {
			getline(fe, linea); //Toma una l�nea del fichero
			stringstream ss; //Stream que trabaja sobre buffer interno

			if (linea != "") {
				++total;
			}

			if (total > 1) {
				//Inicializamos el contenido de ss
				ss << linea;

				//Leemos el NIF
				getline(ss, dni, ';'); //El car�cter ; se lee y se elimina de ss

				//Leemos el pass
				getline(ss, pass, ';'); //El car�ter ; se lee y se elimina de ss

				//Leemos el nombre
				getline(ss, nombre, ' '); //El car�ter ' ' se lee y se elimina de ss

				//Leemos el apellido
				getline(ss, apellido, ';'); //El car�cter ; se lee y se elimina de ss

				//Leemos la direcci�n
				getline(ss, direccion, ';'); //El car�ter ; se lee y se elimina de ss

				//Leemos la latitud y longitud
				getline(ss, latitud, ';'); //El car�ter ; se lee y se elimina de ss
				getline(ss, longitud, ';'); //El car�ter ; se lee y se elimina de ss
				
				setlocale(LC_ALL, "english");
				dlat = std::stod(latitud);
				dlon = std::stod(longitud);
				setlocale(LC_ALL, "spanish");
				//con todos los atributos le�dos, se crea el cliente
				Cliente client(dni, pass, nombre, apellido, direccion, dlat, dlon);
				client.setAplicacion(&ecocity);
				try {
					ecocity.insertaCliente(client);
				}
				catch (const std::runtime_error & e) {
					std::cout << e.what() << '\n';
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
	string linea; //Cada l�nea tiene un clienete
	int total = 0; //Contador de l�neas o clientes

	//Variables auxiliares para almacenar los valores le�dos
	string matricula, estado, latitud, longitud;
	int iestado;
	double dlat, dlon;

	//Asociamos el flujo al fichero
	fe.open(fileNameMotos);

	if (fe.good()) {
		//Mientras no se haya llegado al final del fichero
		while (!fe.eof()) {
			getline(fe, linea); //Toma una l�nea del fichero
			stringstream ss; //Stream que trabaja sobre buffer interno

			if (linea != "") {
				++total;
			}

			if (total > 1) {
				//Inicializamos el contenido de ss
				ss << linea;

				//Leemos la matricula
				getline(ss, matricula, ';'); //El car�cter ; se lee y se elimina de ss

				//Leemos el estado
				getline(ss, estado, ';'); //El car�ter ; se lee y se elimina de ss
				iestado = stoi(estado);

				//Leemos la latitud y longitud
				getline(ss, latitud, ';'); //El car�ter ; se lee y se elimina de ss
				getline(ss, longitud, ';'); //El car�ter ; se lee y se elimina de ss
				
				setlocale(LC_ALL, "english");
				dlat = stod(latitud);
				dlon = stod(longitud);
				setlocale(LC_ALL, "spanish");
				//con todos los atributos le�dos, se crea el cliente
				estatus estadoMoto;
				switch (iestado) {
				case 0:
					estadoMoto = estatus::bloqueada;
					break;
				case 1:
					estadoMoto = estatus::activa;
					break;
				case 2:
					estadoMoto = estatus::sinbateria;
					break;
				case 3:
					estadoMoto = estatus::rota;
				}

				UTM utm(dlat, dlon);

				Moto* moto = new Moto(matricula, utm, estadoMoto, 1 + (rand() % 100));
				ecocity.insertaMoto(moto);
			}
		}

		cout << "Total de Motos en el fichero: " << total << endl;
		fe.close(); //Cerramos el flujo de entrada
	}
	else {
		cerr << "No se puede abrir el fichero" << endl;
	}
}

void leeLineaCliente(string& csv, EcoCityMoto& ecocity, Cliente* &cliActivo) {
	stringstream ss;
	string dni, pass, nombre, apellido, direccion, latitud, longitud;
	float dlat, dlon;
	//Inicializamos el contenido de ss
	ss << csv;

	//Leemos el NIF
	getline(ss, dni, ';'); //El car�cter ; se lee y se elimina de ss

	//Leemos el pass
	getline(ss, pass, ';'); //El car�ter ; se lee y se elimina de ss

	//Leemos el nombre
	getline(ss, nombre, ' '); //El car�ter ' ' se lee y se elimina de ss

	//Leemos el apellido
	getline(ss, apellido, ';'); //El car�cter ; se lee y se elimina de ss

	//Leemos la direcci�n
	getline(ss, direccion, ';'); //El car�ter ; se lee y se elimina de ss

	//Leemos la latitud y longitud
	getline(ss, latitud, ';'); //El car�ter ; se lee y se elimina de ss
	getline(ss, longitud, ';'); //El car�ter ; se lee y se elimina de ss

	setlocale(LC_ALL, "english");
	dlat = std::stod(latitud);
	dlon = std::stod(longitud);
	setlocale(LC_ALL, "spanish");
	//con todos los atributos le�dos, se crea el cliente
	Cliente client(dni, pass, nombre, apellido, direccion, dlat, dlon);
	client.setAplicacion(&ecocity);
	try {
		cliActivo = ecocity.insertaCliente(client);
	}
	catch (const std::runtime_error & e) {
		std::cout << e.what() << '\n';
	}
}

void leeItinerariosYClientes(string archivo, EcoCityMoto& ecocity) {
	ifstream fichero;
	fichero.open(archivo);
	if (fichero.good()) {
		string linea;
		Cliente* clienteActivo = 0;
		while (!fichero.eof()) {
			stringstream ss;
			getline(fichero, linea);
			if (linea == "")
				continue;
			if (linea[0] == '-') {
				string temp = linea.substr(1);
				try {
					leeLineaCliente(temp, ecocity, clienteActivo);
				}
				catch (std::runtime_error & e) {
					cout << e.what() << endl;
				}/*
				if (!ecocity.buscaCliente(temp, clienteActivo)){
					cerr << "Erorr al cargar datos del cliente " << temp << endl;
					break;
				}*/
			}
			else {
				if (!clienteActivo)
					throw std::runtime_error("[leeItinerariosYClientes] Error al buscar cliente");
				ss << linea;
				string id, minutos;
				string latInicio, lonInicio, latFinal, lonFinal;
				string dia, mes, anio, hora, minuto;
				getline(ss, id, ';');
				getline(ss, minutos, ';');
				getline(ss, latInicio, ':');
				getline(ss, lonInicio, ';');
				getline(ss, latFinal, ':');
				getline(ss, lonFinal, ';');
				getline(ss, dia, '/');
				getline(ss, mes, '/');
				getline(ss, anio, ' ');
				getline(ss, hora, ':');
				getline(ss, minuto);
				UTM inicio(stod(latInicio), stod(lonInicio)), fin(stod(latFinal), stod(lonFinal));
				Fecha fecha(stoi(dia), stoi(mes), stoi(anio), stoi(hora), stoi(minuto));
				Itinerario* iti = new Itinerario(stoi(id), stoi(minutos), inicio, fin, fecha);
				clienteActivo->addItinerario(iti);
				ecocity.setIdUltimo(stoi(id));
			}
		}
	}
	else {
		cerr << "No se pudo cargar los itinerarios" << endl;
	}

}