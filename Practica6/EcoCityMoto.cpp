#include "EcoCityMoto.h"
#include "Cliente.h"
#include "leerFich.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

/**
*@Brief M�todo encargado de cargar la informaci�n desde fichero mediante las funciones del espacio de nombres leerFich
*/
void EcoCityMoto::cargaEEDD(string fichCli, string fichMotos)
{
	cout << "�Quiere iniciar la lectura desde los ficheros por defecto? [S/n]: ";
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
	clientes = new THashCliente;
	cargaEEDD("itinerarios.txt", "motos.txt");
}

/**
	@brief Constructor parametrizado
	@param _idUltimo Id del ultimo itinerario
*/
EcoCityMoto::EcoCityMoto(unsigned _idUltimo, size_t tamTabla) : idUltimo(_idUltimo)
{
	motos = new vector<Moto*>;
	//clientes = new map<std::string, Cliente>;
	clientes = new THashCliente(tamTabla);
	cargaEEDD("itinerarios.txt", "motos.txt");
}

/**
	@brief Destructor
*/
EcoCityMoto::~EcoCityMoto()
{
	string archivo = "itinerarios.txt";
	guardarClientesItinerarios(archivo);
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
	recargas = orig.recargas;
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
	recargas = right.recargas;
	return *this;
}

/**
	@brief Busca la moto m�s cercana a la posicion indicada
	@pre Debe haber alguna moto disponible (bloqueada, no rota y con bateria)
*/
Moto& EcoCityMoto::localizaMotoCercana(UTM posicion)
{
	Moto* masCercana = 0;
	double menorDistancia = 99999, distancia;
	Cliente temp("", "", "", "", "", posicion.latitud, posicion.longitud, 0);
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
	@brief Busca la moto m�s cercana al cliente indicado
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

/**
*@Brief Inserta un cliente en la tabla hash
*@return True si se ha insertado correctamente, false en otro caso
*/
bool EcoCityMoto::nuevoCliente(Cliente& cliente)
{
	return clientes->insertar(clientes->djb2(cliente.getDni()), cliente.getDni(), cliente);
}

/**
	@brief Inserta un cliente en la tabla hash
	@return Puntero al cliente recien insertado
*/
Cliente* EcoCityMoto::insertaCliente(Cliente& cliente)
{
	Cliente* aux = new Cliente(cliente);
	if (!nuevoCliente(*aux))
		return nullptr;
	return aux;
}

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
			if (it->estado == EstadoHash::ocupado) {
				it->cliente.crearItinerarios((rand() % 5) + 1, min, max);
			}
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
	@post el parametro motoEncontrada se iguala a un puntero a la moto encontrada
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

/**
*@Brief Busca el cliente cuyo DNI coincida con el indicado
*@Return Puntero al cliente encontrado, nullptr si no se encuentra
*/
Cliente* EcoCityMoto::buscarCliente(std::string& dni)
{
	Cliente* encontrado = 0;
	if (!clientes->buscar(clientes->djb2(dni), dni, encontrado)) {
		return nullptr;
	}
	return encontrado;
}

/*
*@Brief Busca el cliente cuyo DNI coicida con el indicado
*@Post el parametro clienteEncontrado se iguala a un puntero al cliente encontrado
*@Return true si se ha encontrado, false en otro caso
*/
bool EcoCityMoto::buscaCliente(std::string& dni, Cliente* &clienteEncontrado)
{
	clienteEncontrado = buscarCliente(dni);
	if (clienteEncontrado) {
		return true;
	}
	else {
		return false;
	}
}

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
	@brief Devuelve el id del siguiente itinerario a crear e incrementa en 1 el total
*/
unsigned int EcoCityMoto::idItinerario(){
	idUltimo++;
	return idUltimo - 1;
}

/**
*@Brief Setter del atributo idUltimo
*/
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
		if (i == 309) {
			int x = 5 + 2;
		}
		if ((*motos)[i]->getEstado() == estatus::sinbateria && recargas.fueraAmbito((*motos)[i]->getUTM().latitud, (*motos)[i]->getUTM().longitud)) {
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
	clientes = new THashCliente(15991);
}

/**
	@brief Elimina el contenido del mapa de clientes
*/
void EcoCityMoto::borraClientes()
{
	delete clientes;
	clientes = new THashCliente(15991);
}

/**
	@brief Elimina el contenido del vector de motos
*/
void EcoCityMoto::borraMotos()
{
	delete motos;
	motos = new vector<Moto*>;
}

/**
*@Brief Devuelve el numero de clientes en la tabla hash
*/
unsigned EcoCityMoto::getNumClientes()
{
	//return clientes->size();
	return clientes->numCliente();
}

/**
*@Brief Devuelve el numero de motos almacenadas
*/
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

/**
*@Brief Devuelve el limite de bateria para considerar una moto como sin bateria
*/
int EcoCityMoto::getLimiteBateria()
{
	return limiteBateria;
}

/**
	@brief Elimina el cliente con el ID indicado
*/
bool EcoCityMoto::eliminarCliente(std::string id)
{
	return clientes->borrar(clientes->djb2(id), id);
}

/**
*@Brief Devuelve un string con la informacion de la tabla
*/
string EcoCityMoto::estadoTabla()
{
	stringstream estado;
	estado << "Maximo de colisiones: " << clientes->maxColisiones() << endl
		 << "Promedio de colisiones: " << clientes->promedioColisiones() << endl
		 << "Tama�o de la tabla: " << clientes->tamaTabla() << endl
		 << "Numero de clientes: " << clientes->numCliente() << endl
		 << "Colisiones de la ultima insercion: " << clientes->ultimasColisiones() << endl
		 << "Factor de carga: " << clientes->factorCarga() << endl;
	return estado.str();
}

/**
*@Brief Devuelve la codificacion djb2 del dni indicado
*/
unsigned long EcoCityMoto::claveString(string& dni)
{
	return clientes->djb2(dni);
}

/**
*@Brief Crea la tabla Hash a partir de un vector de Clientes
*/
EcoCityMoto& EcoCityMoto::vectorToTabla(std::vector<Cliente*>* v, unsigned tamInicio, unsigned primo, unsigned suma)
{
	THashCliente* aux = clientes;
	clientes = new THashCliente(tamInicio);
	clientes->primoHash2 = primo;
	clientes->sumHash2 = suma;
	delete aux;
	for (unsigned i = 0; i < v->size(); i++) {
		clientes->insertar(clientes->djb2((*v)[i]->getDni()), (*v)[i]->getDni(), *((*v)[i]));
	}
	
	return *this;
}

/**
*@Brief Carga los clientes desde el archivo que se pasa como parametro
*/
void EcoCityMoto::cargarClientes(string& archivo)
{
	try {
		unsigned tam = clientes->tamaTabla();
		if (clientes)
			delete clientes;
		clientes = new THashCliente(tam);
		leerFich::leeClientes(archivo, this);
	}
	catch (std::runtime_error & e) {
		cerr << e.what() << endl;
	}
}

/**
*@Brief Carga el vector de motos desde un fichero
*@Post Se elimina el vector anterior para ser sustuido
*/
void EcoCityMoto::cargarMotos(string& archivo)
{
	if (motos)
		delete motos;
	motos = new vector<Moto*>;
	leerFich::leeMotos(archivo, this);
}

/**
*@Brief Almacena el estado de los clientes y sus itinerarios en fichero
*@Param archivo Nombre del fichero donde se guardara el estado
*/
void EcoCityMoto::guardarClientesItinerarios(string& archivo)
{
	char guardar = '\0';
	cout << "�Quiere guardar el estado actual de los clientes? [S/n]: ";
	cin >> guardar;
	if (guardar == 'S' || guardar == 's') {
		std::ofstream archivoItis;
		archivoItis.open(archivo);
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
				if (it->estado == ocupado) {
					archivoItis << "-" << it->cliente.toCSV() << endl;
					archivoItis << verItinerario(it->cliente);
				}
			}
			cout << "�Itinerarios guardados satisfactoriamente!";
		}
	}
}

/**
* @Brief Devuelve un vector de strings con los DNIs de los clientes que hay en la tabla hash
*/
vector<string>* EcoCityMoto::getDniClientes() {
	vector<string>* dnis = new vector<string>;
	for (vector<Entrada>::iterator it = clientes->iteradorInicio(); it != clientes->iteradorFinal(); it++) {
		if (it->estado == ocupado) {
			dnis->push_back(it->cliente.getDni());
		}
	}
	return dnis;
}

/**
*@Brief Devuelve el numero de colisiones en la ultima operacion de insercion de cliente
*/
unsigned EcoCityMoto::ultimasColisiones()
{
	return clientes->ultimasColisiones();
}

/**
*@Brief Devuelve un puntero a la tabla hash de clientes
*/
THashCliente* EcoCityMoto::getTabla()
{
	return clientes;
}

void EcoCityMoto::crearPuntosDeRecarga(UTM minimo, UTM maximo, int diviX, int diviY)
{
	srand(82277);
	MallaRegular<PuntoRecarga> nuevaMalla(minimo.latitud, minimo.longitud, maximo.latitud, maximo.longitud, diviX, diviY);
	recargas = nuevaMalla;
	int numInsertar = 300;
	for (size_t i = 0; i < numInsertar; i++) {
		UTM posicion;
		posicion.latitud = minimo.latitud + (float)rand() / (float)(RAND_MAX / (maximo.latitud - minimo.latitud));
		posicion.longitud = minimo.longitud + (float)rand() / (float)(RAND_MAX / (maximo.longitud - minimo.longitud));
		string id("Punto de recarga " + to_string((i + 1)));
		PuntoRecarga temp(string(id), posicion);
		recargas.insertar(temp);
	}
	srand(time(0));
}

string EcoCityMoto::infoRecargas()
{
	stringstream ss;
	ss << "Maximo de elementos en una celda: " << recargas.maxElementosPorCelda() << std::endl << "Media de elementos: " << recargas.mediaElementosPorCelda() << std::endl;
	ss << "Total de elementos: " << recargas.getNumElementos() << std::endl << "Tama�o de celda X: " << recargas.getTamCelda().first << " Tama�o de celda Y: " << recargas.getTamCelda().second << std::endl;
	return ss.str();
}

PuntoRecarga* EcoCityMoto::puntoRecargaCercano(Cliente* cli)
{
	return recargas.buscarCercano(cli->getPosicion().latitud, cli->getPosicion().longitud);
}

void EcoCityMoto::verPuntos()
{
	recargas.recorrerMalla();
}
