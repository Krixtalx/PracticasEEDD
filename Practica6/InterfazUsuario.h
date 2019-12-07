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
	int opt = -1;
	cout << "1 - Modificar archivo CSV de Clientes" << endl;
	cout << "2 - Modificar archivo CSV de Motos" << endl;
	cout << "3 - Modificar configuración de Sistema Operativo" << endl;
	cout << "0 - Salir" << endl;
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

		case 0:
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

//===========================================CLIENTES===========================================

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
	{
		clienteActivo = ecocity.insertaCliente(cliente);
		if (!clienteActivo) {
			clearScreen();
			cout << "No se pudo insertar" << endl;
			return;
		}
	}
	else
	{
		if (!ecocity.insertaCliente(cliente)) {
			clearScreen();
			cout << "No se pudo insertar" << endl;
			return;
		}
	}
	clearScreen();
	cout << "Inserción sin problemas (" << ecocity.ultimasColisiones() << " colisiones)" << endl;
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
		//cout << "Cliente encontrado: " << clienteActivo->GetNombreCompleto() << "    UTM: " << clienteActivo->getPosicion().toCSV();
		cout << "Cliente encontrado" << endl;
		stringstream ss;
		ss << clienteActivo->toCSV();
		string dniCli, passCli, nombreCli, dirCli, latCli, lonCli, puntosCli;
		getline(ss, dniCli, ';');
		getline(ss, passCli, ';');
		getline(ss, nombreCli, ';');
		getline(ss, dirCli, ';');
		getline(ss, latCli, ';');
		getline(ss, lonCli, ';');
		getline(ss, puntosCli);
		cout << "DNI: " << dniCli << endl << "Pass: " << passCli << endl << "Nombre: " << nombreCli << endl << "Direccion: " << dirCli << endl << "Posicion: " << latCli << " " << lonCli << endl << "Puntos: " << puntosCli << endl;
		return true;
	}
	else {
		cout << "Cliente no encontrado";
		clienteActivo = antiguo;
	}
	return false;
}

//=================================ITINERARIOS=================================

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
		cout << "Moto encontrada: " << motoCercana->getId() << " (" << motoCercana->getUTM().toCSV() << "), ";
		switch (motoCercana->getEstado())
		{
		case estatus::activa:
			cout << "activa (" << motoCercana->getPorcentajeBateria() << "% de batería restante)" << endl;
			break;
		case estatus::bloqueada:
			cout << "bloqueada (" << motoCercana->getPorcentajeBateria() << "% de batería restante)" << endl;
			break;
		case estatus::rota:
			cout << "rota (" << motoCercana->getPorcentajeBateria() << "% de batería restante)" << endl;
			break;
		default:
			cout << "sin batería" << endl;
		}
		cout << "¿Quiere activar la moto encontrada? [S/n]: ";
		string opcs;
		cin >> opcs;
		if (opcs[0] != 'S' && opcs[0] != 's') {
			return;
		}
		motoCercana->seActiva(*clienteActivo);
		clienteActivo->creaItinerario(*motoCercana);
		//clienteActivo->terminarTrayecto();
		cout << "Se ha creado un nuevo itinerario con la moto" << endl;
	}
	catch (std::runtime_error & e) {
		cerr << e.what();
	}
}

void bloquearMoto(EcoCityMoto& ecocity) {
	string opcion = "n";
	Cliente* antiguo = clienteActivo;
	if (clienteActivo) {
		cout << "¿Quiere usar el cliente activo? (DNI: " << clienteActivo->getDni() << ") [S/n]: ";
		cin >> opcion;
	}
	if (opcion[0] != 'S' && opcion[0] != 's') {
		string dni;
		cout << "Introduzca el DNI del cliente al que se bloqueará la moto: ";
		cin >> dni;
		if (!ecocity.buscaCliente(dni, clienteActivo)) {
			cout << "No se encontró al cliente" << endl;
			clienteActivo = antiguo;
			return;
		}
	}
	clienteActivo->terminarTrayecto();
	Moto* vehiculo = clienteActivo->getItinerarios().back()->getVehiculo();
	cout << "Se ha bloqueado la moto " << vehiculo->getId() << endl;
	if (vehiculo->getPorcentajeBateria() < ecocity.getLimiteBateria()) {
		cout << "Es necesario recargar la moto, ¿buscar el punto de recarga más cercano? [S/n]: ";
		string opcionRecarga;
		cin >> opcionRecarga;
		if (opcionRecarga[0] == 'S' || opcionRecarga[0] == 's') {
			cout << "Buscando posicion mas cercana a" << vehiculo->getUTM().toCSV() << "..." << endl;
			PuntoRecarga* cercano = ecocity.buscarCercano(vehiculo->getUTM().latitud, vehiculo->getUTM().longitud);
			if (!cercano) {
				clienteActivo = antiguo;
				cout << "No se pudo encontrar ningun punto de recarga" << endl;
				return;
			}
			cout << "El punto de recarga mas cercano se encuentra en " << cercano->getX() << " " << cercano->getY() << endl << "Moviendo la moto..." << endl;
			UTM nuevaPos(cercano->getX(), cercano->getY());
			vehiculo->setUTM(nuevaPos);
			vehiculo->setPorcentajeBateria(100, ecocity.getLimiteBateria());
			if (clienteActivo->getPuntos() < 10)
				clienteActivo->setPuntos(clienteActivo->getPuntos() + 1);
			cout << "El cliente " << clienteActivo->getDni() << " tiene " << clienteActivo->getPuntos() << " puntos." << endl;

		}
		else {
			cout << "Decrementando puntos del cliente..." << endl;
			clienteActivo->setPuntos(clienteActivo->getPuntos() - 1);
			if (clienteActivo->getPuntos() == 0) {
				if (ecocity.eliminarCliente(clienteActivo->getDni())) {
					cout << "Se ha eliminado al cliente por alcanzar el mínimo de puntos." << endl;
				}
				else {
					cerr << "[bloquearMoto]No se pudo borrar" << endl;
				}
				clienteActivo = 0;
			}
			else {
				cout << "El cliente " << clienteActivo->getDni() << " tiene " << clienteActivo->getPuntos() << " puntos." << endl;
			}
		}
	}
	clienteActivo = antiguo;
}

void gestionItinerarios(EcoCityMoto& ecocity) {
	if (clienteActivo) {
		cout << "Cliente seleccionado: " << clienteActivo->getDni() << endl << clienteActivo->getDisplay() << endl;
	}
	else
		cout << "Actualmente no hay cliente seleccionado" << endl;
	int opcion;
	cout << endl << endl << "Gestión de itinerarios" << endl << endl;
	cout << "1 - Acceso a itinerarios de un cliente" << endl;
	cout << "2 - Buscar y activar moto más cercana" << endl;
	cout << "3 - Bloquear moto" << endl;
	cout << "4 - Generar itinerarios aleatorios" << endl;
	cout << "0 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion)
	{
	case 1:
		clearScreen();
		accesoItinerarios(ecocity);
		break;

	case 2:
		clearScreen();
		asignarMoto(ecocity);
		break;

	case 3:
		clearScreen();
		bloquearMoto(ecocity);
		break;

	case 4:
		clearScreen();
		generaItinerarios(ecocity);
		break;

	case 0:
		clearScreen();
		break;

	default:
		clearScreen();
		cout << "Opción inválida" << endl;
		break;
	}
}

//=================================FIN ITINERARIOS=================================

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

void eliminarClientes(EcoCityMoto& ecocity) {
	string tam;
	cout << "¿Cuantos clientes quiere eliminar? (Se eliminaran del inicio de la tabla hash): ";
	cin >> tam;
	if (stoi(tam) < 1 || ecocity.getNumClientes() < stoi(tam)) {
		cout << "Tamaño no válido" << endl;
		return;
	}
	clienteActivo = nullptr;
	vector<string>* dnis = ecocity.getDniClientes();
	for (size_t i = 0; i < stoi(tam); i++) {
		if (!ecocity.eliminarCliente((*dnis)[i]))
		{
			cerr << "Error durante el borrado (iteración " << i << ")" << endl;
			break;
		}
	}
	delete dnis;
	return;
}

/*
*@Brief Submenu de Clientes
*/
void menuClientes(EcoCityMoto& ecocity) {
	if (clienteActivo) {
		cout << "Cliente seleccionado: " << clienteActivo->getDni() << " Puntos: " << clienteActivo->getPuntos() << endl << clienteActivo->getDisplay() << endl;
	}
	else
		cout << "Actualmente no hay cliente seleccionado" << endl;
	int opcion;
	cout << endl << endl << "Submenu de Clientes" << endl << endl;
	cout << "1 - Insertar cliente" << endl;
	cout << "2 - Buscar cliente" << endl;
	cout << "3 - Borrar cliente" << endl;
	cout << "4 - Estado de la tabla hash" << endl;
	cout << "5 - Gestionar itinerarios" << endl;
	cout << "6 - Eliminar varios clientes" << endl;
	cout << "7 - Recorrido completo" << endl;
	cout << "0 - Salir" << endl;
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
		cout << ecocity.estadoTabla();
		break;

	case 5:
		clearScreen();
		gestionItinerarios(ecocity);
		break;

	case 6:
		clearScreen();
		eliminarClientes(ecocity);
		break;

	case 7:
	{
		clearScreen();
		vector<string>* dnis = ecocity.getDniClientes();
		for (size_t i = 0; i < dnis->size(); i++) {
			Cliente* temp;
			if (ecocity.buscaCliente((*dnis)[i], temp)) {
				cout << "Cliente encontrado: " << temp->toCSV() << endl;
			}
			else {
				cout << "No se encontró el cliente con DNI " << (*dnis)[i] << ". ¿Desea continuar? [S/n]: ";
				string opc;
				cin >> opc;
				if (opc[0] != 'S' && opc[0] != 's'){
					break;
					delete dnis;
				}
			}
		}
		delete dnis;
		break;
	}
	case 0:
		clearScreen();
		return;
		break;

	default:
		clearScreen();
		cout << "Opción invalida";
		break;
	}
}

//===========================================FIN CLIENTES===========================================
//===========================================MOTOS===========================================


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
		if (encontrada && encontrada->getEstado()!=estatus::sinbateria) {
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
	{
		clearScreen();
		cout << "Opción inválida";
		return;
	}
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
	cout << "0 - Salir" << endl;
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
	case 0:
		clearScreen();
		return;
		break;

	default:
		clearScreen();
		cout << "Opción inválida";
		break;
	}
}

//===========================================FIN MOTOS===========================================
//===========================================MALLA===========================================

void menuMalla(EcoCityMoto& ecocity) {
	int opcion;
	cout << endl << endl << "Submenu de la Malla" << endl << endl;
	cout << "1 - Generar puntos de recarga" << endl;
	cout << "2 - Informacion de la malla" << endl;
	cout << "3 - Ver contenido" << endl;
	cout << "0 - Salir" << endl;
	cout << "¿Que desea hacer?: ";
	cin >> opcion;
	switch (opcion) {
	case 1:
	{
		clearScreen();
		UTM minimo, maximo;
		cout << "Latitud minima: ";
		cin >> minimo.latitud;
		cout << "Longitud minima: ";
		cin >> minimo.longitud;
		cout << "Latitud maxima: ";
		cin >> maximo.latitud;
		cout << "Longitud maxima: ";
		cin >> maximo.longitud;
		int divX, divY;
		cout << "Divisiones en X: ";
		cin >> divX;
		cout << "Divisiones en Y: ";
		cin >> divY;
		ecocity.crearPuntosDeRecarga(minimo, maximo, divX, divY);
		break;
	}

	case 2:
		clearScreen();
		cout << ecocity.infoRecargas();
		break;

	case 3:
		clearScreen();
		ecocity.verPuntos();
		break;
	case 0:
		clearScreen();
		return;
		break;

	default:
		clearScreen();
		cout << "Opción inválida";
		break;
	}
}

//===========================================FIN MALLA===========================================
//===========================================GESTION DE LAS EEDD===========================================

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
		ecocity.cargarMotos(archivoMotos);
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
		ecocity.cargarMotos(archivoMotos);
	}
	if (confCli == 'S' || confCli == 's') {
		cout << "Borrando información de clientes..." << endl;
		ecocity.cargarClientes(archivoClientes);
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
	cout << "0 - Salir" << endl;
	cout << "¿Qué desea hacer?: ";
	cin >> opcion;
	switch (opcion)
	{
	case 1:
		clearScreen();
		ecocity.cargarClientes(archivoClientes);
		break;
	case 2:
		clearScreen();
		ecocity.cargarMotos(archivoMotos);
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
	case 0:
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
	cout << "0 - Salir" << endl;
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
	case 0:
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



void IA(EcoCityMoto& ecocity) {
	unsigned mejorMax = 1, mejorPrimo = 2, mejorSum = 1, mejorTam = 15991, tamInicial = 15991, tamOriginal = 15991, sumOriginal=1;
	float  pCol = 20;
	ifstream datosIA;
	string archivoIA = "iaData.txt";
	datosIA.open(archivoIA);
	if (datosIA.good()) {
		string linea, maxStr, primoStr, sumStr, tamStr, colStr;
		getline(datosIA, linea);
		stringstream ss;
		ss << linea;
		getline(ss, maxStr, ';');
		getline(ss, primoStr, ';');
		getline(ss, sumStr, ';');
		getline(ss, tamStr, ';');
		getline(ss, colStr);
		mejorMax = stoi(maxStr);
		mejorPrimo = stoi(primoStr);
		mejorSum = stoi(sumStr);
		sumOriginal = mejorSum;
		mejorTam = stoi(tamStr);
		setlocale(LC_ALL, "english");
		pCol = stof(colStr);
		setlocale(LC_ALL, "spanish");
		tamInicial = mejorTam;
		tamOriginal = tamInicial;
	}
	datosIA.close();
	unsigned interPrimo, interSum, interTam=1;
	string archivo = "itinerarios.txt";
	std::vector<Cliente*>* v = leerFich::ficheroaVector(archivo);

	cout << "Introduzca el nº de interacciones para primo: ";
	cin >> interPrimo;
	cout << "Introduzca el nº de interacciones para sum: ";
	cin >> interSum;
	clearScreen();
	for (size_t itPrimos = 0; itPrimos < interPrimo; itPrimos++) {
		ecocity.getTabla()->sumHash2 = sumOriginal;
		for (size_t itSum = 0; itSum < interSum; itSum++) {
			tamInicial = tamOriginal;
			for (size_t itTam = 0; itTam < interTam; itTam++) {
				if (itPrimos == 0 && itSum == 0 && itTam == 0) {
					ifstream ultimo;
					string ultimoFich = "iaLast.txt";
					ultimo.open(ultimoFich);
					if (ultimo.good()) {
						stringstream ss;
						string lin, tama, prim, suma, promedio;
						getline(ultimo, lin);
						ss << lin;
						getline(ss, prim, ';');
						getline(ss, suma, ';');
						getline(ss, tama, ';');
						getline(ss, promedio, ';');
						ecocity.vectorToTabla(v, stoi(tama), stoi(prim), stoi(suma));
						setlocale(LC_ALL, "english");
						pCol = stof(promedio);
						setlocale(LC_ALL, "spanish");
					}
					else
					{
						ecocity.vectorToTabla(v, tamInicial, mejorPrimo, mejorSum);
					}
					ultimo.close();
				}
				else
					ecocity.vectorToTabla(v, tamInicial, ecocity.getTabla()->primoHash2, ecocity.getTabla()->sumHash2);
				THashCliente* tabla = ecocity.getTabla();
				if (tabla->promedioColisiones() < pCol) {
					mejorMax = tabla->maxColisiones();
					mejorPrimo = tabla->primoHash2;
					mejorSum = tabla->sumHash2;
					mejorTam = tabla->tamInicial;
					pCol = tabla->promedioColisiones();
				}
				clearScreen();
				cout << "Interacciones: " << itPrimos + 1 << " primos, " << itSum + 1 << " suma "  << endl << endl;

				cout << "ACTUAL MEJOR                                                    ULTIMO PROBADO" << endl;
				cout << "MAX COLISIONES:" << mejorMax << "                                             MAX COLISIONES: " << tabla->maxColisiones() << endl;
				cout << "PROMEDIO COLISIONES: " << pCol << "                                 PROMEDIO COLISIONES: " << tabla->promedioColisiones() << endl;
				cout << "TAMTABLA: " << mejorTam << "                                                      TAM INICIAL: " << tabla->tamInicial << endl;
				cout << "PRIMO: " << mejorPrimo << "                                                          PRIMO:" << tabla->primoHash2 << endl;
				cout << "SUMA: " << mejorSum << "                                                               SUMA:" << tabla->sumHash2 << endl << endl;

				if (tamInicial < tabla->numCliente()) {
					tamInicial = tabla->siguientePrimo(tamInicial * (0.75 + ((float)tamInicial / tabla->numCliente())));
				}
				else
				{
					tamInicial = tabla->siguientePrimo(tamInicial);
				}
			}
			ecocity.getTabla()->sumHash2 = ecocity.getTabla()->siguientePrimo(ecocity.getTabla()->sumHash2);
		}
		ecocity.getTabla()->primoHash2 = ecocity.getTabla()->siguientePrimo(ecocity.getTabla()->primoHash2);
	}
	ofstream iaOut;
	iaOut.open(archivoIA);
	if (iaOut.good()) {
		iaOut << mejorMax << ";" << mejorPrimo << ";" << mejorSum << ";" << mejorTam << ";" << pCol;
	}
	iaOut.close();
	ofstream iaUltimo;
	string archivoUltimo = "iaLast.txt";
	iaUltimo.open(archivoUltimo);
	if (iaUltimo.good()) {
		iaUltimo << ecocity.getTabla()->primoHash2 << ";" << ecocity.getTabla()->sumHash2 << ";" << ecocity.getTabla()->tamInicial << ";" << ecocity.getTabla()->promedioColisiones();
	}
	iaUltimo.close();

	for (unsigned i = 0; i < v->size(); i++) {
		delete (*v)[i];
	}
	delete v;
}

//===========================================FIN GESTION===========================================

/*
*@Brief Menu principal
*/
bool menuPrincipal(EcoCityMoto& ecocity) {
	int opcion=-1;
	while (opcion != 0) {
		cout << endl << endl << "Programa de Gestión de EcoCityMoto" << endl << endl;
		cout << "1 - Instrucciones" << endl;
		cout << "2 - Configuracion" << endl;
		cout << "3 - Clientes (Tabla Hash)" << endl;
		cout << "4 - Motos (STL Vector)" << endl;
		cout << "5 - Puntos de recarga (Malla)" << endl;
		cout << "6 - Cargar datos" << endl;
		cout << "7 - Guardar clientes e itinerarios" << endl;
		cout << "8 - Estado actual" << endl;
		cout << "9 - Reiniciar información" << endl;
		cout << "0 - Salir" << endl;
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
			menuMalla(ecocity);
			break;

		case 6:
			clearScreen();
			menuCarga(ecocity);
			break;

		case 7:
			clearScreen();
			ecocity.guardarClientesItinerarios(archivoItinerarios);
			break;

		case 8:
			clearScreen();
			mostrarEstado(ecocity);
			break;

		case 9:
			clearScreen();
			reiniciarApp(&ecocity);
			break;

		case 0:
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

/*
*@Brief Menu principal
*/
bool menuBasico(EcoCityMoto& ecocity, Cliente* cliente) {
	int opcion = 0;
	clearScreen();
	cout << "Bienvenido " << cliente->GetNombreCompleto()<<endl;
	while (opcion != 7) {
		cout << endl << endl << "Programa de EcoCityMoto" << endl << endl;
		cout <<cliente->toCSV() << endl << endl;
		cout << "1 - Instrucciones" << endl;
		cout << "2 - Configuracion" << endl;
		cout << "3 - Alquilar moto más cercana" << endl;
		cout << "4 - Bloquear moto" << endl;
		cout << "5 - Ver estado actual de la moto" << endl;
		cout << "6 - Ver itinerarios anteriores" << endl;
		cout << "0 - Salir" << endl;
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
			Moto* motoCercana;
			clearScreen();
			cout << "Buscando moto más cercana a " << cliente->getPosicion().toCSV() << " ..." << endl;
			try {
				motoCercana = &ecocity.localizaMotoCercana(*cliente);
				motoCercana->seActiva(*cliente);
				cliente->creaItinerario(*motoCercana);
				cout << "Moto encontrada y activada: " << motoCercana->getId() << "  -  " << motoCercana->getUTM().toCSV();
			}
			catch (std::runtime_error & e) {
				cerr << e.what();
			}
			break;

		case 4:
			clearScreen();
			try {
				cliente->terminarTrayecto();
			}
			catch (std::runtime_error & e) {
				cerr << e.what();
				return false;
			}
			cout << "Moto bloqueada";
			break;

		case 5:
			clearScreen();
			cout << cliente->getDisplay() << endl;
			break;

		case 6:
			clearScreen();
			verItinerario(ecocity, *cliente);
			break;

		case 0:
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

bool login(EcoCityMoto& ecocity) {
	clearScreen();
	string dni, pass;
	Cliente* aux;
	while (true) {
		cout << "¿Quiere entrar a la aplicación como administrador? [S/n]: ";
		cin >> dni;
		if (dni[0] == 'S' || dni[0] == 's') {
			menuPrincipal(ecocity);
			cout << "¿Quiere salir de la aplicación? [S/n]: ";
			string opcion;
			cin >> opcion;
			if (opcion[0] == 'S' || opcion[0] == 's')
				return true;
			continue;
		}
		cout << "Introduzca su DNI: ";
		cin >> dni;

		if (ecocity.buscaCliente(dni, aux)) {
			cout << aux->getPass() << endl;
			cout << "Introduzca su contraseña: ";
			cin >> pass;
			if (aux->getPass() == pass) {
				menuBasico(ecocity, aux);
				cout << "¿Quiere salir de la aplicación? [S/n]: ";
				string opcion;
				cin >> opcion;
				if (opcion[0] == 'S' || opcion[0] == 's')
					return true;
				continue;
			}
		}
		clearScreen();
		cout << "DNI o contraseña invalida" << endl;
	}
}
