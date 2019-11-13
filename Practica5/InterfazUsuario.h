#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "Cliente.h"
#include "Itinerario.h"
#include "Moto.h"
#include "EcoCityMoto.h"
#include "leerFich.h"

using namespace std;

//Variables globales de configuracion
bool windows = true;
string archivoClientes="clientes.csv";
string archivoMotos = "motos.txt";
string archivoItinerarios = "itinerarios.txt";
Cliente* clienteActivo = 0;

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

		default:
			clearScreen();
			cout << "Opción invalida";
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
	cliente.setAplicacion(&ecocity);
	cout << "¿Quiere emplear el cliente recién insertado para operaciones futuras? [S/n] ";
	char opcion = 'S';
	cin >> opcion;
	if(opcion == 'S' || opcion == 's')
		clienteActivo = ecocity.insertaCliente(cliente);
	else
		ecocity.insertaCliente(cliente);
	clearScreen();
}

/*
*@Brief Busca un cliente en el sistema a partir de su DNI 
*/
bool buscarCliente(EcoCityMoto& ecocity){
	Cliente* antiguo = clienteActivo;
	string dni;
	cout << "Introduzca el DNI del cliente a buscar: ";
	getline(cin >> ws, dni);
	if (ecocity.buscaCliente(dni, clienteActivo)) {
		cout << "Cliente encontrado: " << clienteActivo->GetNombreCompleto() << "    UTM: " << clienteActivo->getPosicion().toCSV();
		return true;
	}
	else {
		cout << "Cliente no encontrado";
		clienteActivo = antiguo;
	}
	return false;
}

/*
*@Brief Muestra por consola el recorrido en Inorden del Arbol AVL en el que se encuentran los clientes
*/
void recorridoInorden(EcoCityMoto& ecocity) {
	char yon;
	cout << "Este recorrido puede generar una salida muy grande" << endl << "¿Está seguro de que quiere hacerlo? [S/n] ";
	cin >> yon;
	if (yon == 'S') {
		clearScreen();
		cout << "Comenzando recorrido en Inorden del árbol..." << endl;
		ecocity.recorreMapa();
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
	cout << endl << endl << "Submenu del mapa STL" << endl << endl;
	cout << "1 - Recorrido en Inorden" << endl;
	cout << "2 - Numero de elementos" << endl;
	cout << "3 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion) {
	case 1:
		clearScreen();
		recorridoInorden(ecocity);
		break;
	case 2:
		clearScreen();
		cout << ecocity.getNumClientes() << " clientes almacenados" << endl;
		break;
	case 3:
		clearScreen();
		return;
		break;
	default:
		clearScreen();
		cout << "Opción invalida";
		break;
	}
}

/*
*@Brief Permite ver por consola los itinerarios que tiene un cliente
*/
void verItinerario(EcoCityMoto& ecocity, Cliente& cliente) {
	cout << "Itinerarios: " << endl;
	cout << "ID;Duración;UTM Inicio;UTM Final;Fecha;IDMoto" << endl;
	try {
		cout << ecocity.verItinerario(cliente);
	}
	catch (logic_error & e) {
		cerr << "El cliente no tiene itinerarios" << endl;
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
		try {
			if (cliente.getItinerarios().size()) {
				cliente.getItinerarios().pop_back();
				cout << "Itinerario borrado";
			}
		}
		catch (std::logic_error &e) {
			cerr << endl << e.what();
		}
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
	if (clienteActivo) {
		cout << "Cliente seleccionado: " << clienteActivo->getDni() << endl;
	}
	else
		cout << "Actualmente no hay cliente seleccionado" << endl;
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

	default:
		clearScreen();
		cout << "Opción invalida";
		break;
	}
}

/*
*@Brief Función encargada de garantizar el acceso a los Itinerarios de un cliente
*/
void accesoItinerarios(EcoCityMoto& ecocity) {
	char opcion = 'n';
	if (clienteActivo) {
		cout << "¿Quiere usar el cliente activo? (DNI: " << clienteActivo->getDni() << ") [S/n]: ";
		cin >> opcion;
	}
	if (opcion != 'S' && opcion != 's') {
		if (buscarCliente(ecocity))
			menuItinerarios(ecocity, *clienteActivo);
		else
			return;
	}
	else
	{
		menuItinerarios(ecocity, *clienteActivo);
	}
}

/*
*@Brief Función encargada de generar aleatoriamente itinerarios para todos los clientes
*/
void generaItinerarios(EcoCityMoto& ecocity) {
	if (!ecocity.getNumClientes()) {
		cout << "No hay clientes cargados en la aplicacion." << endl;
		return;
	}
	double min1, min2, max1, max2;
	cout << "Latitud mínima: ";
	cin >> min1;
	cout << endl << "Latitud máxima: ";
	cin >> max1;
	cout << endl << "Longitud mínima: ";
	cin >> min2;
	cout << endl << "Longitud máxima: ";
	cin >> max2;
	UTM minimo(min1, max2), maximo(max1, min2);
	try {
		ecocity.crearItinerarios(minimo, maximo);
	}
	catch (range_error & e) {
		cout << e.what() << endl;
		return;
	}
	cout << endl << "Se han generado itinerarios para todos los clientes" << endl;
}

/*
*@Brief Metodo encargado de asignar la motocicleta mas cercana al cliente introducido por DNI
*/
void asignarMoto(EcoCityMoto& ecocity) {
	char opcion = 'n';
	if (clienteActivo) {
		cout << "¿Quiere usar el cliente activo? (DNI: " << clienteActivo->getDni() << ") [S/n]: ";
		cin >> opcion;
	}
	if (opcion != 'S' && opcion != 's') {
		Cliente* antiguo = clienteActivo;
		string dni;
		cout << "Introduzca el DNI del cliente al que se le asignará la moto: ";
		getline(cin >> ws, dni);
		if (!ecocity.buscaCliente(dni, clienteActivo)) {
			cout << "No se ha encontrado el cliente" << endl;
			clienteActivo = antiguo;
			return;
		}
	}
	Moto* motoCercana;
	clearScreen();
	cout << "Buscando moto más cercana a " << clienteActivo->getPosicion().toCSV() << " ..." << endl;
	try {
		motoCercana = &ecocity.localizaMotoCercana(*clienteActivo);
		motoCercana->seActiva(*clienteActivo);
		clienteActivo->creaItinerario(*motoCercana);
		cout << "Moto encontrada y activada: " << motoCercana->getId() << "  -  " << motoCercana->getUTM().toCSV();
	}
	catch (std::runtime_error & e) {
		cerr << e.what();
	}
}

/*
*@Brief Metodo encargado de bloquear la motocicleta de un cliente introducido por DNI
*/
void bloquearMoto(EcoCityMoto& ecocity) {
	char opcion = 'n';
	if (clienteActivo) {
		cout << "¿Quiere usar el cliente activo? (DNI: " << clienteActivo->getDni() << ") [S/n]: ";
		cin >> opcion;
	}
	if (opcion != 'S' && opcion != 's') {
		Cliente* antiguo = clienteActivo;
		string dni;
		cout << "Introduzca el DNI del cliente al que se le bloqueará la moto: ";
		getline(cin >> ws, dni);
		if (!ecocity.buscaCliente(dni, clienteActivo)) {
			cout << "No se encontró al cliente";
			clienteActivo = antiguo;
			return;
		}
	}
	clearScreen();
	try {
		clienteActivo->terminarTrayecto();
	}
	catch (std::runtime_error & e) {
		cerr << e.what();
		return;
	}
	cout << "Moto bloqueada";
}

void borrarCliente(EcoCityMoto& ecocity) {
	char opcion = 'n';
	if (clienteActivo) {
		cout << "¿Quiere usar el cliente activo? (DNI: " << clienteActivo->getDni() << ") [S/n]: ";
		cin >> opcion;
	}
	if (opcion != 'S' && opcion != 's') {
		Cliente* antiguo = clienteActivo;
		string dni;
		cout << "Introduzca el DNI del cliente a borrar: ";
		getline(cin >> ws, dni);
		if (!ecocity.buscaCliente(dni, clienteActivo)) {
			cout << "No se encontró al cliente";
			clienteActivo = antiguo;
			return;
		}
	}
	clearScreen();
	if (ecocity.eliminarCliente(clienteActivo->getDni())) {
		cout << "Cliente eliminado";
		clienteActivo = 0;
	}
	else
		cout << "No se pudo eliminar al cliente indicado";
}

/*
*@Brief Submenu de Clientes
*/
void menuClientes(EcoCityMoto& ecocity) {
	if (clienteActivo) {
		cout << "Cliente seleccionado: " << clienteActivo->getDni() << endl;
	}
	else
		cout << "Actualmente no hay cliente seleccionado" << endl;
	int opcion;
	cout << endl << endl << "Submenu de Clientes" << endl << endl;
	cout << "1 - Insertar cliente" << endl;
	cout << "2 - Buscar cliente" << endl;
	cout << "3 - Borrar cliente" << endl;
	cout << "4 - Ajustes del mapa STL" << endl;
	cout << "5 - Acceso a itinerarios de un cliente" << endl;
	cout << "6 - Asignar moto más cercana" << endl;
	cout << "7 - Bloquear moto de un cliente" << endl;
	cout << "8 - Generar itinerarios aleatorios" << endl;
	cout << "9 - Salir" << endl;
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
		bloquearMoto(ecocity);
		break;

	case 8:
		clearScreen();
		generaItinerarios(ecocity);
		break;
	case 9:
		clearScreen();
		return;
		break;

	default:
		clearScreen();
		cout << "Opción invalida";
		break;
	}
}

/*
*@Brief Inserta una motocicleta en el vector dinámico de Motos con los datos introducidos por consola
*/
void insertarMoto(EcoCityMoto& ecocity) {
	string matricula;
	UTM utm;
	int estado, bateria = -1;
	estatus estadoMoto;
	cout << "Introduzca la matricula de la moto: ";
	getline(cin >> ws, matricula);
	cout << "Introduzca la latitud en la que se encuentra la moto: ";
	cin >> utm.latitud;
	cout << "Introduzca la longitud en la que se encuentra la moto: ";
	cin >> utm.longitud;
	while (bateria < 0 || bateria > 100) {
		cout << "Introduzca el porcentaje de batería de la moto (valor entre 0 y 100): ";
		cin >> bateria;
	}
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
			cout << "Opción invalida";
			break;
		}
	}
	Moto* moto = new Moto(matricula, utm, estadoMoto, bateria);
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
		cout << "Estado de la moto: " << moto->getEstado()<<endl;
		if (moto->getEstado() != estatus::sinbateria)
			cout << "Porcentaje de batería restante: " << moto->getPorcentajeBateria() <<"%"<< endl;
		else {
			cout << "Sin bateria" << endl;
			cout << "Porcentaje de batería restante: " << moto->getPorcentajeBateria() <<"%"<< endl;

		}
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

void buscarSinBateria(EcoCityMoto& ecocity) {
	int opcion = -1;
	while (opcion < 0 || opcion > 2) {
		cout << endl << "¿Quiere buscar una moto específica (1) o ver un listado completo (2)? (0 para volver): ";
		cin >> opcion;
	}
	switch (opcion)
	{
	case 0:
	{
		clearScreen();
		cout << "Opción inválida";
		return;
	}

	case 1:
	{
		clearScreen();
		cout << "Introduzca el ID de la moto a buscar: ";
		string idBusca;
		cin >> idBusca;
		vector<Moto*>* sinBateria = ecocity.localizaMotoSinBateria();
		Moto* encontrada = 0;
		for (vector<Moto*>::iterator it = sinBateria->begin(); it != sinBateria->end(); it++) {
			if ((*it)->getId() == idBusca) {
				encontrada = (*it);
				break;
			}
		}
		if (encontrada->getEstado()!=estatus::sinbateria) {
			cout << "Moto encontrada: " << encontrada->getId() << endl;
			cout << "Posición: " << encontrada->getUTM().toCSV() << endl;
		}
		else
			cout << "No se encontró la moto sin bateria" << endl;
		break;
	}

	case 2:
	{
		clearScreen();
		vector<Moto*>* sinBateria = ecocity.localizaMotoSinBateria();
		for (vector<Moto*>::iterator it = sinBateria->begin(); it != sinBateria->end(); it++) {
			cout << "ID: " << (*it)->getId() << "     Posición: " << (*it)->getUTM().toCSV() <<"     Bateria: "<<(*it)->getPorcentajeBateria()<<"%"<< endl;
		}
		delete sinBateria;
		break;
	}

	default:
		break;
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
	cout << "3 - Motos sin bateria" << endl;
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
		buscarSinBateria(ecocity);
		break;
	case 4:
		clearScreen();
		return;
		break;

	default:
		clearScreen();
		cout << "Opción inválida";
		break;
	}
	menuMotos(ecocity);
}

void mostrarEstado(EcoCityMoto& ecocity) {
	cout << ecocity.getNumClientes() << " clientes almacenados en la aplicación" << endl;
	cout << ecocity.getNumMotos() << " motos almacenadas en la aplicación" << endl;
	int idTemp = ecocity.idItinerario();
	ecocity.setIdUltimo(idTemp);
	if (!idTemp) {
		idTemp = 1;
	}
	cout << "El ID del último itinerario creado es: " << idTemp - 1 << endl;
}

/*
*@Brief Funcion encargada de cargar los CSVs en memoria. Utiliza los nombres incluidos en las variables globales
*/
void carga(EcoCityMoto& ecocity) {
	char confMotos = 'S', confCli = 'S';
	if (ecocity.getNumMotos()) {
		cout << "Se eliminará la información actual sobre motos de la aplicación y comenzará la carga desde fichero. ¿Quiere continuar la operación? [S/n]: ";
		cin >> confMotos;
	}
	if (ecocity.getNumClientes()) {
		cout << "Se eliminará la información actual sobre clientes e itinerarios de la aplicación y comenzará la carga desde fichero. ¿Quiere continuar la operación? [S/n]: ";
		cin >> confCli;
	}
	if (confMotos == 'S' || confMotos == 's') {
		cout << "Borrando información de motos..." << endl;
		ecocity.borraMotos();
		leerFich::leeMotos(archivoMotos, &ecocity);
	}
	if (confCli == 'S' || confCli == 's') {
		cout << "Borrando información de clientes e itinerarios..." << endl;
		ecocity.borraClientes();
		leerFich::leeItinerariosYClientes(archivoItinerarios, &ecocity);
	}
	clearScreen();
}

void cargaParcial(EcoCityMoto& ecocity) {
	char confMotos = 's', confCli = 's';
	if (ecocity.getNumClientes()) {
		cout << "Se eliminará la información actual sobre clientes de la aplicación y comenzará la carga desde fichero. ¿Quiere continuar la operación? [S/n]: ";
		cin >> confCli;
	}
	if (ecocity.getNumMotos()) {
		cout << "Se eliminará la información actual sobre motos de la aplicación y comenzará la carga desde fichero. ¿Quiere continuar la operación? [S/n]: ";
		cin >> confMotos;
	}
	if (confMotos == 'S' || confMotos == 's') {
		cout << "Borrando información de motos..." << endl;
		ecocity.borraMotos();
		leerFich::leeMotos(archivoMotos, &ecocity);
	}
	if (confCli == 'S' || confCli == 's') {
		cout << "Borrando información de clientes..." << endl;
		ecocity.borraClientes();
		leerFich::leeClientes(archivoClientes, &ecocity);
	}
}

void cargaUnica(EcoCityMoto& ecocity) {
	char opcionInicio;
	cout << "El uso de este menú podría eliminar cualquier información previa almacenada en las EEDD de la aplicación, ¿desea continuar? [S/n]: ";
	cin >> opcionInicio;
	if (opcionInicio != 'S' && opcionInicio != 's')
		return;

	int opcion;
	cout << endl << endl << "Cargas desde fichero disponibles: " << endl;
	cout << "1 - Clientes" << endl;
	cout << "2 - Motos" << endl;
	cout << "3 - Clientes + Itinerarios" << endl;
	cout << "4 - Salir" << endl;
	cout << "¿Qué desea hacer?: ";
	cin >> opcion;
	switch (opcion)
	{
	case 1:
		clearScreen();
		leerFich::leeClientes(archivoClientes, &ecocity);
		break;
	case 2:
		clearScreen();
		leerFich::leeMotos(archivoMotos, &ecocity);
		break;
	case 3:
		clearScreen();
		if (ecocity.getNumMotos()) {
			try {
				leerFich::leeItinerariosYClientes(archivoItinerarios, &ecocity);
			}
			catch (std::runtime_error & e) {
				cerr << e.what();
			}
		}
		else
			cout << "No hay motos cargadas, por favor, cargue primero las motos en la aplicación" << endl;
		break;
	case 4:
		clearScreen();
		return;
	default:
		cout << "Opción inválida" << endl;
		break;
	}
}

void menuCarga(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de Carga" << endl << endl;
	cout << "1 - Carga completa (Clientes, itinerarios y motos)" << endl;
	cout << "2 - Carga parcial (Clientes y motos)" << endl;
	cout << "3 - Carga unica" << endl;
	cout << "4 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion)
	{
	case 1:
		clearScreen();
		carga(ecocity);
		break;
	case 2:
		clearScreen();
		cargaParcial(ecocity);
		break;
	case 3:
		clearScreen();
		cargaUnica(ecocity);
		break;
	case 4:
		clearScreen();
		return;
	default:
		cout << "Opción inválida";
		break;
	}
}

void reiniciarApp(EcoCityMoto* ecocity) {
	char opcion;
	cout << "¿Desea eliminar toda la información actual? Será necesario volver a cargar la información [S/n]: ";
	cin >> opcion;
	if (opcion == 'S' || opcion == 's') {
		ecocity->borrarEEDD();
		ecocity->setIdUltimo(0);
	}
}

/*
*@Brief Menu principal
*/
bool menuPrincipal(EcoCityMoto& ecocity) {
	int opcion=0;
	while (opcion != 8) {
		cout << endl << endl << "Programa de Gestión de EcoCityMoto" << endl << endl;
		cout << "1 - Instrucciones" << endl;
		cout << "2 - Configuracion" << endl;
		cout << "3 - Clientes (STL Map)" << endl;
		cout << "4 - Motos (STL Vector)" << endl;
		cout << "5 - Cargar datos" << endl;
		cout << "6 - Estado actual" << endl;
		cout << "7 - Reiniciar información" << endl;
		cout << "8 - Salir" << endl;
		cout << "¿Que desea hacer?: ";
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
			menuCarga(ecocity);
			break;

		case 6:
			clearScreen();
			mostrarEstado(ecocity);
			break;

		case 7:
			clearScreen();
			reiniciarApp(&ecocity);
			break;

		case 8:
			clearScreen();
			return true;
			break;

		default:
			clearScreen();
			cout << "Opción invalida";
			break;
		}
	}
	clearScreen();
	return true;
}
