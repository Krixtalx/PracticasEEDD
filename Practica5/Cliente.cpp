#include "Cliente.h"
#include "EcoCityMoto.h"
#include <cmath>
#include <complex>

Cliente::Cliente() : dni(""), pass(""), nombre(""), apellido(""), direccion(""), nombreCompleto("") {
	listaItinerarios = new std::list<Itinerario*>;
}

Cliente::Cliente(string dni) :
	dni(dni) {
}


Cliente::Cliente(string _dni, string _pass, string _nombre, string _apellido, string _direccion, double _latitud, double _longitud) :
	dni(_dni), pass(_pass), nombre(_nombre), apellido(_apellido), direccion(_direccion), posicion(_latitud, _longitud) {
	nombreCompleto = nombre + " " + apellido;
	listaItinerarios = new std::list<Itinerario*>;
}

Cliente::Cliente(const Cliente& orig): dni(orig.dni), pass(orig.pass), nombre(orig.nombre), apellido(orig.apellido), direccion(orig.direccion){
	nombreCompleto = orig.nombreCompleto;
	posicion.latitud = orig.posicion.latitud;
	posicion.longitud = orig.posicion.longitud;
	this->listaItinerarios = new std::list<Itinerario*>(*(orig.listaItinerarios));
	aplicacion = orig.aplicacion;
	
}

Cliente::~Cliente() {
	while (!listaItinerarios->empty()) {
		delete listaItinerarios->front();
		listaItinerarios->pop_front();
	}
	delete listaItinerarios;
}

UTM Cliente::getPosicion() const {
	return posicion;
}

/**
	@brief Devuelve una referencia a la lista que almacena los itinerarios
	@throws std::logic_error Si no se han creado itinerarios para el cliente
*/
list<Itinerario*>& Cliente::getItinerarios()
{
	if (listaItinerarios->size() == 0)
		throw std::logic_error("[Cliente.cpp] El cliente no tiene itinerarios");
	return *(this->listaItinerarios);
}

/**
 * @brief Compara dos clientes por su nombre
 * @param otro Cliente a comparar
 * @return True si el nombre del cliente *this es menor alfabeticamente que el de otro
 */
bool Cliente::operator<(Cliente& otro) {
	if (this->dni < otro.dni)
		return true;
	return false;
}

bool Cliente::operator>(Cliente& otro){
	return dni>otro.dni;
}

/**
 *  @brief Compara dos clientes por su nombre completo
 *  @param otro Cliente a comparar
 *  @return True si el nombre completo de *this es menor alfabeticamente que el de otro
 */
bool Cliente::menorQue(Cliente& otro) {
	if (this->nombreCompleto < otro.nombreCompleto)
		return true;
	return false;
}


/**
 * @brief Operador de asignación
 * @param right Cliente del que se copia el estado
 * @return Devuelve this para poder encadenar operadores
 */
Cliente& Cliente::operator=(const Cliente& right) {
	if (this == &right)
		return *this;

	this->direccion = right.direccion;
	this->dni = right.dni;
	this->nombre = right.nombre;
	this->apellido = right.apellido;
	this->pass = right.pass;
	this->posicion = right.posicion;
	this->nombreCompleto = right.nombreCompleto;

	if (listaItinerarios) {
		while (!listaItinerarios->empty()) {
			delete listaItinerarios->front();
			listaItinerarios->pop_front();
		}
		delete listaItinerarios;
	}

	this->listaItinerarios = new std::list<Itinerario*>(*(right.listaItinerarios));
	this->aplicacion = right.aplicacion;

	return *this;
}

/**
 * @brief Getter del atributo apellido
 * @return string apellido
 */
string Cliente::GetApellido() const {
	return apellido;
}

/**
 * @brief Getter del atributo nombre
 * @return string nombre
 */
string Cliente::GetNombre() const {
	return nombre;
}

/**
*@Brief Gette del atributo nombre completo
*@return string el Nombre completo
*/
string Cliente::GetNombreCompleto() const {
	return nombreCompleto;
}

string Cliente::getDni() const
{
	return dni;
}

/**
 * @brief Calcula la distancia entre 2 clientes utilizando la formula de la distancia entre 2 puntos
 * @param otro: Cliente con el que se calcula la distancia
 * @return La distancia entre los 2 clientes
 */
double Cliente::DistanciaCliente(Cliente& otro) {
	return sqrt(pow(this->posicion.latitud - otro.getPosicion().latitud, 2) + pow(this->posicion.longitud - otro.getPosicion().longitud, 2));
}

ostream& operator<<(ostream& os, const Cliente& cliente){
	os << "DNI: " << cliente.dni << endl;
	return os;
}

void Cliente::setAplicacion(EcoCityMoto* app)
{
	aplicacion = app;
}

/**
	@brief Devuelve una referencia a la moto mas cercana
	@post Realiza la operacion mediante el metodo de EcoCityMoto
*/
Moto& Cliente::buscaMotoCercana()
{
	return aplicacion->localizaMotoCercana(*this);
}

/**
*@Brief crea "num" itinerarios y los añade a la lista
*@param num Numero de itinerarios a crear
*@param idUltimo ID del ultimo de los itinerarios
*/
void Cliente::crearItinerarios(int num, UTM& minimo, UTM& maximo) {
	for (int i = 0; i < num; i++) {
		Itinerario* aux = new Itinerario(aplicacion->idItinerario(), minimo, maximo);
		try {
			aux->setVehiculo(aplicacion->getMotoAleatoria());
		}
		catch (std::range_error &e) {
			string temp = e.what();
			throw std::range_error("[Cliente::crearItinerarios]" + temp);
		}
		listaItinerarios->push_back(aux);
	}
}

/**
	@brief Crea un nuevo itinerario en el cliente
	@param m Moto usada en el viaje
	@post Se genera un itinerario cuyo inicio es la posicion de la moto, y con un final generado aleatoriamente en el rango (37, 3)-(38, 4)
*/
void Cliente::creaItinerario(Moto& m)
{
	UTM tempMin, tempMax;
	tempMin.latitud = 37;
	tempMin.longitud = 3;
	tempMax.latitud = 38;
	tempMax.longitud = 4;
	Itinerario* nuevo = new Itinerario(aplicacion->idItinerario(), tempMin, tempMax);
	nuevo->setInicio(m.getUTM());
	nuevo->setVehiculo(&m);
	listaItinerarios->push_back(nuevo);
}

/**
	@brief Llama al metodo de EcoCityMoto para desbloquear la moto indicada
*/
void Cliente::desbloqueaMoto(Moto& m)
{
	aplicacion->desbloqueaMoto(m, *this);
}

/**
	@brief Desactiva la moto que estubiese usando y genera un valor aleatorio para la duracion del viaje
*/
void Cliente::terminarTrayecto()
{
	if (listaItinerarios->size() == 0)
		throw std::runtime_error("[Cliente::terminarTrayecto] El cliente no tiene itinerarios");
	listaItinerarios->back()->setMinutos(rand() % listaItinerarios->back()->getVehiculo()->getPorcentajeBateria(), aplicacion->getLimiteBateria());
	listaItinerarios->back()->getVehiculo()->setUTM(listaItinerarios->back()->getFin());
	listaItinerarios->back()->getVehiculo()->seDesactiva(this->getItinerarios().back()->getDuracion(), aplicacion->getLimiteBateria());
	posicion = listaItinerarios->back()->getVehiculo()->getUTM();
}

/**
	@brief Inserta el itinerario en la lista del cliente
*/
void Cliente::addItinerario(Itinerario* iti)
{
	listaItinerarios->push_back(iti);
}

/**
	@brief Devuleve la informacion del cliente en formato CSV
*/
string Cliente::toCSV()
{
	return (dni + ";" + pass + ";" + nombreCompleto + ";" + direccion + ";" + std::to_string(posicion.latitud) + ";" + std::to_string(posicion.longitud));
}

