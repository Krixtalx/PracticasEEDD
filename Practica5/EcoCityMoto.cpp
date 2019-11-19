#include "EcoCityMoto.h"
#include "Cliente.h"
#include "leerFich.h"

#include <iostream>
#include <fstream>
#include <sstream>

void EcoCityMoto::cargaEEDD(string fichCli, string fichMotos)
{
	cout << "¿Quiere iniciar la lectura desde los ficheros por defecto? [S/n]: " << endl;
	char entrada;
	cin >> entrada;
	if (entrada == 'S') {
		leerFich::leeMotos(fichMotos, this);
		try {
			leerFich::leeItinerariosYClientes(fichCli, this);
		}
		catch (std::runtime_error & e) {
			cerr << e.what() << endl;
		}
	}
}

/**
	@brief Constructor por defecto
*/
EcoCityMoto::EcoCityMoto()
{
	motos = new vector<Moto*>;
	//clientes = new map<std::string, Cliente>;
	clientes = new THashCliente(1000);
	cargaEEDD("itinerarios.txt", "motos.txt");
}

/**
	@brief Constructor parametrizado
	@param _idUltimo Id del ultimo itinerario
*/
EcoCityMoto::EcoCityMoto(unsigned _idUltimo) : idUltimo(_idUltimo)
{
	motos = new vector<Moto*>;
	//clientes = new map<std::string, Cliente>;
	clientes = new THashCliente(1000);
	cargaEEDD("itinerarios.txt", "motos.txt");
}

/**
	@brief Destructor
*/
EcoCityMoto::~EcoCityMoto()
{
	char guardar = '\0';
	cout << "¿Quiere guardar el estado actual de los clientes? [S/n]: ";
	cin >> guardar;
	if (guardar == 'S' || guardar == 's') {
		std::ofstream archivoItis;
		archivoItis.open("itinerarios.txt");
		if (!archivoItis.good())
			cout << "Error en el archivo itinerarios.txt" << endl;
		else {
			cout << endl << "Iniciando guardado de itinerarios en el fichero: itinerarios.txt" << endl;
			/*for (std::map<string, Cliente>::iterator it = clientes->begin(); it != clientes->end(); it++)
			{
				archivoItis << "-" << it->second.toCSV() << endl;
				archivoItis << verItinerario(it->second);
			}
			*/
			for (std::vector<Entrada>::iterator it = clientes->iteradorInicio(); it != clientes->iteradorFinal(); it++) {
				archivoItis << "-" << it->cliente.toCSV() << endl;
				archivoItis << verItinerario(it->cliente);
			}
			cout << "¡Itinerarios guardados satisfactoriamente!";
		}
	}
	while (!motos->empty()) {
		delete motos->back();
		motos->pop_back();
	}
	delete motos;
	delete clientes;
}

/**
	@brief Constructor de copia
	@param orig Objeto del que copiar
*/
EcoCityMoto::EcoCityMoto(EcoCityMoto& orig) : idUltimo(orig.idUltimo)
{
	motos = new vector<Moto*>(*(orig.motos));
	//clientes = new map<std::string, Cliente>(*(orig.clientes));
	clientes = new THashCliente(*(orig.clientes));
}

/**
	@brief Operador de asignacion
	@param right Objeto cuyos atributos se van a asignar
*/
EcoCityMoto& EcoCityMoto::operator=(EcoCityMoto& right)
{
	idUltimo = right.idUltimo;

	while (!motos->empty()) {
		delete motos->back();
		motos->pop_back();
	}
	delete motos;

	motos = new vector<Moto*>(*(right.motos));
	delete clientes;
	//clientes = new map<std::string, Cliente>(*(right.clientes));
	clientes = new THashCliente(*(right.clientes));
	return *this;
}

/**
	@brief Busca la moto más cercana a la posicion indicada
	@pre Debe haber alguna moto disponible (bloqueada, no rota y con bateria)
*/
Moto& EcoCityMoto::localizaMotoCercana(UTM posicion)
{
	Moto* masCercana = 0;
	double menorDistancia = 99999, distancia;
	Cliente temp("", "", "", "", "", posicion.latitud, posicion.longitud);
	for (int i = motos->size() - 1; i >= 0; i--) {
		distancia = (*motos)[i]->distanciaCliente(temp);
		if (distancia < menorDistancia) {
			masCercana = (*motos)[i];
			menorDistancia = distancia;
		}
	}
	return *masCercana;
}

/**
	@brief Busca la moto más cercana al cliente indicado
	@pre Debe haber alguna moto disponible (bloqueada, no rota y con bateria)
*/
Moto& EcoCityMoto::localizaMotoCercana(Cliente& cliente){
	Moto* masCercana = 0;
	double menorDistancia = 99999.99;
	double distancia;
	bool aux=false;
	if (motos->size() <= 0) {
		throw std::runtime_error("[Localiza moto cercana]: No hay ninguna moto en el sistema");
	}
	for (unsigned i = 0; i < motos->size(); i++){
		if ((*motos)[i]->getEstado() != estatus::bloqueada)
			continue;
		distancia = (*motos)[i]->distanciaCliente(cliente);
		if (menorDistancia > distancia) {
			aux = true;
			masCercana = (*motos)[i];
			menorDistancia = distancia;
		}
	}
	if (aux)
		return *masCercana;
	else
		throw std::runtime_error("[Localiza moto cercana]: No hay ninguna moto disponible en el sistema");
}

/**
	@brief Activa la moto indicada y le asigna el cliente dado
*/
void EcoCityMoto::desbloqueaMoto(Moto& m, Cliente& cli)
{
	m.seActiva(cli);
}

/**
	@brief Inserta una moto en el vector de motos
*/
EcoCityMoto& EcoCityMoto::insertaMoto(Moto* moto)
{
	motos->push_back(moto);
	return *this;
}

bool EcoCityMoto::nuevoCliente(Cliente& cliente)
{
	return clientes->insertar(clientes->djb2(cliente.getDni()), cliente.getDni(), cliente);
}

/**
	@brief Inserta un cliente en el arbol de clientes
	@return Puntero al cliente recien insertado

Cliente* EcoCityMoto::insertaCliente(Cliente& cliente)
{
	std::map<std::string, Cliente>::iterator it;
	std::pair<std::map<std::string, Cliente>::iterator, bool> parInserta;
	parInserta = clientes->insert(std::pair<const std::string, Cliente>(cliente.getDni(), cliente));
	if (!parInserta.second)
		throw std::runtime_error("[EcoCityMoto::insertaCliente] No se pudo insertar");
	return &(parInserta.first->second);
}
*/
/**
	@brief Inserta un itinerario a la lista del cliente indicado
*/
EcoCityMoto& EcoCityMoto::insertaItinerario(Itinerario* itinerario, std::string dni)
{
	Cliente* encontrado;
	//buscaCliente(dni, encontrado);
	encontrado = buscarCliente(dni);
	if (encontrado)
		encontrado->getItinerarios().push_back(itinerario);
	else
		cout << "No se pudo encontrar al cliente indicado" << endl;
	return *this;
}

/**
	@brief Genera itinerarios aleatoriamente para cada cliente
	@param min, max Coordenadas UTM minimas y maximas en la generacion
*/
EcoCityMoto& EcoCityMoto::crearItinerarios(UTM& min, UTM& max)
{
	//std::map<std::string, Cliente>::iterator it;
	//for (it = clientes->begin(); it != clientes->end(); it++) {
	for(std::vector<Entrada>::iterator it = clientes->iteradorInicio(); it != clientes->iteradorFinal(); it++){
		try {
			//it->second.crearItinerarios((rand() % 5) + 1, min, max);
			it->cliente.crearItinerarios((rand() % 5) + 1, min, max);
		}
		catch (std::range_error & e) {
			string temp = e.what();
			throw std::range_error("[EcoCityMoto::crearItinerarios]" + temp);
		}
	}
	return *this;
}

/**
	@brief Muestra en formato CSV los itinerarios del cliente indicado
*/
std::string& EcoCityMoto::verItinerario(Cliente& cliente){
	string *aux=new string;
	std::list<Itinerario*> lista;
	try {
		lista = cliente.getItinerarios();
	}
	catch (std::logic_error& e) {
		string temp = e.what();
		throw std::logic_error("[EcoCityMoto::verItinerario]" + temp);
	}
	list<Itinerario*>::iterator iterator;
	for (iterator = lista.begin(); iterator != lista.end(); iterator++)
			*aux += ((*iterator)->toCSV() + "\n");
	return *aux;
}

/**
	@brief Busca la moto cuya ID coincida con la indicada
*/
bool EcoCityMoto::buscaMoto(std::string id, Moto* &motoEncontrada)
{
	for(int i = (*motos).size() - 1; i >= 0; i--){
		if ((*motos)[i]->id == id) {
			if(motoEncontrada)
				delete motoEncontrada;
			motoEncontrada = (*motos)[i];
			return true;
		}
	}
	return false;
}

Cliente* EcoCityMoto::buscarCliente(std::string& dni)
{
	Cliente* encontrado = 0;
	if (!clientes->buscar(clientes->djb2(dni), dni, encontrado)) {
		return nullptr;
	}
	return encontrado;
}

/**
	@brief Busca el cliente cuyo DNI coicida con el indicado

bool EcoCityMoto::buscaCliente(std::string& dni, Cliente* &clienteEncontrado)
{

	std::map<std::string, Cliente>::iterator it;
	it = clientes->find(dni);
	if (it != clientes->end()) {
		clienteEncontrado = &(it->second);
		return true;
	}
	else {
		return false;
	}
}
*/
/**
	@brief Elimina la moto de la posicion indicada
*/
EcoCityMoto& EcoCityMoto::borraMoto(int pos)
{
	if (pos < 0 || motos->size() < pos)
		throw std::out_of_range("[EcoCityMoto::borraMoto] Se ha intentado borrar en una posicion no valida");
	std::vector<Moto*>::iterator it = motos->begin();
	for (int i = pos; i >= 0; i--)
		it++;
	motos->erase(it);
	return *this;
}
/**
	@brief Elimina el itinerario de la posicion indicada del cliente
*/
EcoCityMoto& EcoCityMoto::borraItinerario(int pos, std::string dni)
{
	Cliente* encontrado;
	//buscaCliente(dni, encontrado);
	encontrado = buscarCliente(dni);
	if (pos < 0 || encontrado->getItinerarios().size() < pos)
		throw std::out_of_range("[EcoCityMoto::borraItinerario] Se ha intentado borrar en una posicion no valida");
	std::list<Itinerario*>::iterator it = encontrado->getItinerarios().begin();
	for (int i = pos; i >= 0; i--)
		it++;
	encontrado->getItinerarios().erase(it);
	return *this;
}

/**
	@brief Muestra el mapa de clientes en inorden
*/
EcoCityMoto& EcoCityMoto::recorreMapa()
{
	//std::map<std::string, Cliente>::iterator it;
	//for (it = clientes->begin(); it != clientes->end(); it++) {
	for (std::vector<Entrada>::iterator it = clientes->iteradorInicio(); it != clientes->iteradorFinal(); it++){
		//std::cout << it->second;
		cout << it->cliente;
	}
	return *this;
}

/**
	@brief Devuelve el id del siguiente itinerario a crear e incrementa en 1 el total
*/
unsigned int EcoCityMoto::idItinerario(){
	idUltimo++;
	return idUltimo - 1;
}

void EcoCityMoto::setIdUltimo(unsigned _id)
{
	idUltimo = _id;
}

/**
	@brief Devuelve un vector STL de punteros a las motos sin bateria
*/
vector<Moto*>* EcoCityMoto::localizaMotoSinBateria() {
	vector<Moto*>* mSinBateria = new vector<Moto*>;
	for(unsigned i = 0; i < motos->size(); i++){
		if ((*motos)[i]->getEstado() == estatus::sinbateria) {
			mSinBateria->push_back((*motos)[i]);
		}
	}
	return mSinBateria;
}

/**
	@brief Elimina el contenido del vector de motos y el mapa de clientes
*/
void EcoCityMoto::borrarEEDD()
{
	while (!motos->empty()) {
		delete motos->back();
		motos->pop_back();
	}
	delete motos;
	delete clientes;
	motos = new vector<Moto*>;
	//clientes = new map<std::string, Cliente>;
	clientes = new THashCliente(1000);
}

/**
	@brief Elimina el contenido del mapa de clientes
*/
void EcoCityMoto::borraClientes()
{
	delete clientes;
	//clientes = new map<std::string, Cliente>;
	clientes = new THashCliente(1000);
}

/**
	@brief Elimina el contenido del vector de motos
*/
void EcoCityMoto::borraMotos()
{
	delete motos;
	motos = new vector<Moto*>;
}

unsigned EcoCityMoto::getNumClientes()
{
	//return clientes->size();
	return clientes->numCliente();
}

unsigned EcoCityMoto::getNumMotos()
{
	return motos->size();
}

/**
	@brief Devuelve un puntero a una moto aleatoria del vector de motos
*/
Moto* EcoCityMoto::getMotoAleatoria()
{
	if (!motos->size()){
		throw std::range_error("[EcoCityMoto::getMotoAleatoria] No hay motos cargadas");
	}
	return (*motos)[rand() % motos->size()];
}

int EcoCityMoto::getLimiteBateria()
{
	return limiteBateria;
}

/**
	@brief Elimina el cliente con el ID indicado
*/
bool EcoCityMoto::eliminarCliente(std::string id)
{
	//return clientes->erase(id);
	return clientes->borrar(clientes->djb2(id), id);
}

//TODO: borrar esto cuando funcione
void EcoCityMoto::verTabla()
{
	clientes->verTabla();
}
