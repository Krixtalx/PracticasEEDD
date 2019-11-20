#include "leerFich.h"
void leerFich::leeMotos(string fichMotos, EcoCityMoto* app) {
	
	cout << "Comenzando lectura del fichero " << fichMotos << "..." << endl;
	ifstream fe; //Flujo de entrada
	string linea; //Cada línea tiene un clienete
	int total = 0; //Contador de líneas o clientes

	//Variables auxiliares para almacenar los valores leídos
	string matricula, estado, latitud, longitud;
	int iestado;
	double dlat, dlon;

	//Asociamos el flujo al fichero
	fe.open(fichMotos);

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
				Moto* moto;
				if (estadoMoto == estatus::sinbateria) {
					moto = new Moto(matricula, utm, estadoMoto, 1 + (rand() % app->getLimiteBateria()));
				}
				else {
					moto = new Moto(matricula, utm, estadoMoto, 15 + (rand() % 85));
				}
				app->insertaMoto(moto);
			}
		}

		cout << "Total de Motos en el fichero: " << total << endl;
		fe.close(); //Cerramos el flujo de entrada
	}
	else {
		cerr << "No se puede abrir el fichero" << endl;
	}
	cout << "¡Lectura satisfactoria!" << endl;
	
}

void leerFich::leeLineaCliente(string& csv, EcoCityMoto* ecocity, Cliente*& cliActivo) {
	
	stringstream ss;
	string dni, pass, nombre, apellido, direccion, latitud, longitud;
	float dlat, dlon;
	//Inicializamos el contenido de ss
	ss << csv;

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
	client.setAplicacion(ecocity);
	try {
		//cliActivo = ecocity->insertaCliente(client);
		if (!ecocity->nuevoCliente(client))
			throw std::runtime_error("Error al insertar");
		cliActivo = ecocity->buscarCliente(dni);
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
					throw std::runtime_error(e);
				}
			}
			else {
				if (!clienteActivo)
					throw std::runtime_error("[leeItinerariosYClientes] Error al buscar cliente");
				try {
					ss << linea;
				}
				catch (std::runtime_error & e) {
					cerr << e.what();
				}
				string id, minutos;
				string latInicio, lonInicio, latFinal, lonFinal;
				string dia, mes, anio, hora, minuto;
				string idMoto;
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
				getline(ss, minuto, ';');
				getline(ss, idMoto);
				UTM inicio(stod(latInicio), stod(lonInicio)), fin(stod(latFinal), stod(lonFinal));
				Fecha fecha(stoi(dia), stoi(mes), stoi(anio), stoi(hora), stoi(minuto));
				Moto* temp = 0;
				ecocity->buscaMoto(idMoto, temp);
				Itinerario* iti = new Itinerario(stoi(id), stoi(minutos), inicio, fin, fecha);
				iti->setVehiculo(temp);
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
	cout << "¡Lectura satisfactoria!" << endl;
	
}

void leerFich::leeClientes(string fileNameClientes, EcoCityMoto* ecocity) {
	
	cout << "Comenzando lectura del fichero " << fileNameClientes << "..." << endl;
	ifstream fe; //Flujo de entrada
	string linea; //Cada línea tiene un clienete
	int total = 1; //Contador de líneas o clientes

	//Variables auxiliares para almacenar los valores leídos
	string dni, nombre, apellido, pass, direccion, latitud, longitud;
	double dlat, dlon;

	//Asociamos el flujo al fichero
	fe.open(fileNameClientes);

	if (fe.good()) {
		//Mientras no se haya llegado al final del fichero
		while (!fe.eof()) {
			getline(fe, linea); //Toma una línea del fichero
			if (linea == "" || linea[0] == 'N'){
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