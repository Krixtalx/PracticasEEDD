#include "Cliente.h"
#include "EcoCityMoto.h"
#include <cmath>
#include <complex>

/**
*@Brief Constructor por defecto
*/
Cliente::Cliente() : dni(""), pass(""), nombre(""), apellido(""), direccion(""), nombreCompleto(""), display("No hay moto en uso") {
	listaItinerarios = new std::list<Itinerario*>;
}

/**
*@Brief Constructor parametrizado
*/
Cliente::Cliente(string dni): dni(dni) {
}

/**
*@Brief Constructor parametrizado
*/
Cliente::Cliente(string _dni, string _pass, string _nombre, string _apellido, string _direccion, double _latitud, double _longitud, int _puntos) :
	dni(_dni), pass(_pass), nombre(_nombre), apellido(_apellido), direccion(_direccion), posicion(_latitud, _longitud), display("No hay moto en uso"), puntos(_puntos) {
	nombreCompleto = nombre + " " + apellido;
	listaItinerarios = new std::list<Itinerario*>;
}

/**
*@Brief Constructor de copia
*/
Cliente::Cliente(const Cliente& orig): dni(orig.dni), pass(orig.pass), nombre(orig.nombre), apellido(orig.apellido), direccion(orig.direccion), display(orig.display), puntos(orig.puntos)
{
	nombreCompleto = orig.nombreCompleto;
	posicion.latitud = orig.posicion.latitud;
	posicion.longitud = orig.posicion.longitud;
	if(orig.listaItinerarios!=0)
		listaItinerarios = new list<Itinerario*>;
		for (list<Itinerario*>::iterator it = orig.listaItinerarios->begin(); it != orig.listaItinerarios->end(); it++) {
			Itinerario* temp = new Itinerario;
			*temp = *(*it);
			listaItinerarios->push_back(temp);
		}
	aplicacion = orig.aplicacion;
	
}

/**
*@Brief Destructor
*/
Cliente::~Cliente() {
	if (listaItinerarios != 0) {
		while (!listaItinerarios->empty()) {
			delete listaItinerarios->front();
			listaItinerarios->pop_front();
		}
		delete listaItinerarios;
	}
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
 * @brief Compara dos clientes por su DNI
 * @param otro Cliente a comparar
 * @return True si el DNI del cliente *this es menor alfabeticamente que el de otro
 */
bool Cliente::operator<(Cliente& otro) {
	if (this->dni < otro.dni)
		return true;
	return false;
}

/**
 * @brief Compara dos clientes por su DNI
 * @param otro Cliente a comparar
 * @return True si el DNI del cliente *this es mayor alfabeticamente que el de otro
 */
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
 * @brief Operador de asignaci�n
 * @param right Cliente del que se copia el estado
 * @return Devuelve this para poder encadenar operadores
 */
Cliente& Cliente::operator=(const Cliente& right) {
	if (this == &right)
		return *this;

	direccion = right.direccion;
	dni = right.dni;
	nombre = right.nombre;
	apellido = right.apellido;
	pass = right.pass;
	posicion = right.posicion;
	nombreCompleto = right.nombreCompleto;
	display = right.display;
	puntos = right.puntos;

	if (listaItinerarios) {
		while (!listaItinerarios->empty()) {
			delete listaItinerarios->front();
			listaItinerarios->pop_front();
		}
		delete listaItinerarios;
	}
	listaItinerarios = new list<Itinerario*>;
	for (list<Itinerario*>::iterator it = right.listaItinerarios->begin(); it != right.listaItinerarios->end(); it++) {
		Itinerario* temp = new Itinerario;
		*temp = **it;
		listaItinerarios->push_back(temp);
	}
	//this->listaItinerarios = new std::list<Itinerario*>(*(right.listaItinerarios));
	aplicacion = right.aplicacion;

	return *this;
}

/**
*@Brief Getter del atributo pass
*@Return string pass
*/
string Cliente::getPass()
{
	return pass;
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

/**
 * @brief Getter del atributo DNI
 * @return string dni
 */
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

/**
 * @brief Setter del atributo aplicacion
 */
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
*@Brief crea "num" itinerarios y los a�ade a la lista
*@param num Numero de itinerarios a crear
*@param idUltimo ID del ultimo de los itinerarios
*/
void Cliente::crearItinerarios(int num, UTM& minimo, UTM& maximo) {
	for (int i = 0; i < num; i++) {
		Itinerario* aux = new Itinerario(aplicacion->idItinerario(), minimo, maximo);
		try {
			aux->setVehiculo(aplicacion->getMotoAleatoria());
			aux->setMinutos((rand() % (100-aux->getVehiculo()->getPorcentajeBateria())) + 1);
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
	nuevo->setMinutos(0);
	nuevo->setInicio(m.getUTM());
	nuevo->setVehiculo(&m);
	listaItinerarios->push_back(nuevo);
	display = "Moto en uso: " + nuevo->getVehiculo()->getId() + " ";
	switch (nuevo->getVehiculo()->getEstado())
	{
	case estatus::activa:
		display += "activa (" + to_string(nuevo->getVehiculo()->getPorcentajeBateria()) + "% de bater�a restante)";
		break;
	case estatus::bloqueada:
		display += "bloqueada (" + to_string(nuevo->getVehiculo()->getPorcentajeBateria()) + "% de bater�a restante)";
		break;
	case estatus::rota:
		display += "rota (" + to_string(nuevo->getVehiculo()->getPorcentajeBateria()) + "% de bater�a restante)";
		break;
	default:
		display += "sin bater�a";
	}
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
void Cliente::terminarTrayecto(bool forzarBateria)
{
	if (listaItinerarios->size() == 0)
		throw std::runtime_error("[Cliente::terminarTrayecto] El cliente no tiene itinerarios");
	if (forzarBateria)
		listaItinerarios->back()->setMinutos(listaItinerarios->back()->getVehiculo()->getPorcentajeBateria());
	else
		listaItinerarios->back()->setMinutos(rand() % listaItinerarios->back()->getVehiculo()->getPorcentajeBateria());
	listaItinerarios->back()->getVehiculo()->setUTM(listaItinerarios->back()->getFin());
	listaItinerarios->back()->getVehiculo()->seDesactiva(this->getItinerarios().back()->getDuracion(), aplicacion->getLimiteBateria());
	posicion = listaItinerarios->back()->getVehiculo()->getUTM();
	display = "No hay moto en uso";
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
	return (dni + ";" + pass + ";" + nombreCompleto + ";" + direccion + ";" + std::to_string(posicion.latitud) + ";" + std::to_string(posicion.longitud) + ";" + std::to_string(puntos));
}

/**
 * @brief Actualiza el mensaje almacenado en el atributo display
 */
void Cliente::mostrarMensaje(string texto)
{
	display = texto;
}

/**
 * @brief Getter del atributo display
 * @return string display
 */
string& Cliente::getDisplay()
{
	return display;
}

int Cliente::getPuntos()
{
	return puntos;
}

void Cliente::decrementarPunto()
{
	puntos--;
}

void Cliente::incrementarPunto()
{
	puntos++;
}

void Cliente::puntoRecargaCercano()
{
	PuntoRecarga* encontrado = aplicacion->puntoRecargaCercano(this);
	if (encontrado) {
		recargarMoto(encontrado);
	}
}

void Cliente::recargarMoto(PuntoRecarga* pr)
{
	listaItinerarios->back()->getVehiculo()->recargar(pr);
	posicion.latitud = pr->getX();
	posicion.longitud = pr->getY();
	display = ("Moto recargada en el punto de recarga: " + pr->getID());
}
