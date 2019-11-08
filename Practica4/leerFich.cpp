#include "leerFich.h"

void leerFich::leeMotos(string fichMotos, EcoCityMoto* app) {
	cout << "Comenzando lectura del fichero " << fichMotos << "..." << endl;
	ifstream fe; //Flujo de entrada
	string linea; //Cada l�nea tiene un clienete
	int total = 0; //Contador de l�neas o clientes

	//Variables auxiliares para almacenar los valores le�dos
	string matricula, estado, latitud, longitud;
	int iestado;
	double dlat, dlon;

	//Asociamos el flujo al fichero
	fe.open(fichMotos);

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
				estatus estadoMoto = estatus::rota;
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
				app->insertaMoto(moto);
			}
		}

		cout << "Total de Motos en el fichero: " << total << endl;
		fe.close(); //Cerramos el flujo de entrada
	}
	else {
		cerr << "No se puede abrir el fichero" << endl;
	}
	cout << "Lectura satisfactoria!" << endl;
}

void leerFich::leeLineaCliente(string& csv, EcoCityMoto* ecocity, Cliente*& cliActivo) {
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
	client.setAplicacion(ecocity);
	try {
		cliActivo = ecocity->insertaCliente(client);
	}
	catch (const std::runtime_error & e) {
		std::cout << e.what() << '\n';
	}
}

void leerFich::leeItinerariosYClientes(string archivo, EcoCityMoto* ecocity) {
	cout << "Comenzando lectura del fichero " << archivo << "..." << endl;
	ifstream fichero;
	fichero.open(archivo);
	int totalCli = 0, totalIti = 0;
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
					totalCli++;
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
				ecocity->setIdUltimo(stoi(id));
				totalIti++;
			}
		}
		cout << "Total de Clientes cargados: " << totalCli << endl;
		cout << "Total de Itinerarios cargados: " << totalIti << endl;
	}
	else {
		cerr << "No se pudo cargar los itinerarios" << endl;
	}
	cout << "Lectura satisfactoria!" << endl;
}

void leerFich::leeClientes(string fileNameClientes, EcoCityMoto* ecocity) {
	cout << "Comenzando lectura del fichero " << fileNameClientes << "..." << endl;
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
			if (!total || linea == ""){
				total++;
				continue;
			}
			Cliente* cli = 0;
			leeLineaCliente(linea, ecocity, cli);
			total++;
		}

		cout << "Total de Clientes cargados: " << total << endl;
		fe.close(); //Cerramos el flujo de entrada
	}
	else {
		cerr << "No se puede abrir el fichero" << endl;
	}
}