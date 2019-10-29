#include "Cliente.h"
#include "EcoCityMoto.h"
#include <cmath>
#include <complex>

Cliente::Cliente() : dni(""), pass(""), nombre(""), apellido(""), direccion(""), nombreCompleto("") {
}

Cliente::Cliente(string dni) :
	dni(dni) {
}


Cliente::Cliente(string _dni, string _pass, string _nombre, string _apellido, string _direccion, double _latitud, double _longitud) :
	dni(_dni), pass(_pass), nombre(_nombre), apellido(_apellido), direccion(_direccion), posicion(_latitud, _longitud) {
	nombreCompleto = nombre + " " + apellido;
}

Cliente::Cliente(const Cliente& orig) : dni(orig.dni), pass(orig.pass), nombre(orig.nombre), apellido(orig.apellido), direccion(orig.direccion) {
	nombreCompleto = orig.nombreCompleto;
	posicion.latitud = orig.posicion.latitud;
	posicion.longitud = orig.posicion.longitud;
}

Cliente::~Cliente() {
}

UTM Cliente::getPosicion() const {
	return posicion;
}

/**
	@brief Devuelve una referencia a la lista que almacena los itinerarios
	@throws std::logic_error Si no se han creado itinerarios para el cliente
*/
ListaDEnlazada<Itinerario>& Cliente::getItinerarios()
{
	if (listaItinerarios.getTam() == 0)
		throw std::logic_error("[Cliente.cpp] El cliente no tiene itinerarios");
	return this->listaItinerarios;
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
 * @brief Operador de asignaci�n
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
		//TODO: revisar creacion junto a creaItinerario
		Itinerario* aux = new Itinerario(aplicacion->idItinerario(), minimo, maximo);
		listaItinerarios.insertaFinal(*aux);
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
	//TODO: revisar creacion junto a crearItinerarios
	Itinerario nuevo(aplicacion->idItinerario(), tempMin, tempMax);
	nuevo.setInicio(m.getUTM());
	nuevo.setVehiculo(&m);
	listaItinerarios.insertaFinal(nuevo);
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
	listaItinerarios.Final().setMinutos(rand() % 300);
	listaItinerarios.Final().getVehiculo()->seDesactiva();
	
}
