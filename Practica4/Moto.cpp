#include "Moto.h"

/**
	@brief Constructor por defecto
*/
Moto::Moto() : id("0") {
}

/**
	@brief Constructor parametrizado
*/
Moto::Moto(std::string id, UTM posicion, Estado estatus): id(id), posicion(posicion), estatus(estatus), usadoPor(0){
}

/**
	@brief Constructor por copia
*/
Moto::Moto(const Moto& orig){
	id = orig.id;
	posicion = orig.posicion;
	estatus = orig.estatus;
	usadoPor = orig.usadoPor;
}

/**
	@brief Destructor
*/
Moto::~Moto(){
}

/**
	@brief Operador de asignacion
	@param right Objeto cuyos objetos se usan en la asignacion
*/
Moto& Moto::operator=(Moto& right)
{
	id = right.id;
	posicion.latitud = right.posicion.latitud;
	posicion.longitud = right.posicion.longitud;
	estatus = right.estatus;
	usadoPor = right.usadoPor;
	return *this;
}

std::string Moto::getId()
{
	return id;
}

UTM& Moto::getUTM()
{
	return posicion;
}

/**
	@brief Devuelve un string con el nombre completo y el dni del cliente asociado
	@pre La moto debe tener un cliente asociado
*/
std::string Moto::getDatosCliente()
{
	if (usadoPor) {
		return "Nombre: " + usadoPor->GetNombreCompleto() + "         DNI: " + usadoPor->getDni();
	}
	throw std::logic_error("[Moto::getDatosCliente] No hay cliente asociado");
}

/**
	@brief Devuelve un string con el estado de la moto
*/
std::string Moto::getEstado()
{
	if (estatus.activa)
		return "Activada";
	if (estatus.bloqueada)
		return "Bloqueada";
	if (estatus.roto)
		return "Rota";
	if (estatus.sinbateria)
		return "Sin bateria";
	throw std::invalid_argument("[Moto::getEstado] Error en el estado");
}

/**
*@Brief Método encargado de activar la moto
*@Param Cliente: usuario que activa la moto
*/
void Moto::seActiva(Cliente& usuario){
	if (estatus.bloqueada && !estatus.sinbateria && !estatus.roto){
		estatus.activa = true;
		estatus.bloqueada = false;
		usadoPor = &usuario;
	}
}

/**
*@Brief Método encargado de desactivar la moto
*/
void Moto::seDesactiva(){
	if (estatus.activa) {
		//Cliente* aux = new Cliente("Nulo");
		estatus.activa = false;
		estatus.bloqueada = true;
		usadoPor = 0;
	}
}
/**
*@Brief Setter del campo sinBateria de estatus
*/
void Moto::setSinbateria(){
	estatus.sinbateria = true;
}
/**
*@Brief Setter del campo Roto de estatus
*/
void Moto::setRoto(){
	estatus.roto = true;
}
/**
*@Brief Calcula la distancia entre 2 motos
*/
double Moto::distanciaMoto(Moto& otro){
	return sqrt(pow(this->posicion.latitud - otro.posicion.latitud, 2) + pow(this->posicion.longitud - otro.posicion.longitud, 2));
}

/**
	@brief Calcula la distancia entre la moto y el cliente indicado
*/
double Moto::distanciaCliente(Cliente& cliente){
	if (estatus.bloqueada && !estatus.roto && !estatus.sinbateria) {
		return sqrt(pow(this->posicion.latitud - cliente.getPosicion().latitud, 2) + pow(this->posicion.longitud - cliente.getPosicion().longitud, 2));
	}
	return 99999999.99;
}
