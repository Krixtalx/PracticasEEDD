#include "Moto.h"

/**
	@brief Constructor por defecto
*/
Moto::Moto() : id("0") {
	porcentajeBateria = rand() % 100;
	if (porcentajeBateria < limiteBateria)
		estado = estatus::sinbateria;
}

/**
	@brief Constructor parametrizado
*/
Moto::Moto(std::string id, UTM posicion, estatus _estado, int porcentajeBateria): id(id), posicion(posicion), estado(_estado), porcentajeBateria(porcentajeBateria),usadoPor(0){
	if (porcentajeBateria < limiteBateria)
		estado = estatus::sinbateria;
}

/**
	@brief Constructor por copia
*/
Moto::Moto(const Moto& orig){
	id = orig.id;
	posicion = orig.posicion;
	estado = orig.estado;
	usadoPor = orig.usadoPor;
	porcentajeBateria = orig.porcentajeBateria;
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
	estado = right.estado;
	usadoPor = right.usadoPor;
	porcentajeBateria = right.porcentajeBateria;
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
estatus Moto::getEstado()
{
	return estado;
	/*if (estatus.activa)
		return "Activada";
	if (estatus.bloqueada)
		return "Bloqueada";
	if (estatus.roto)
		return "Rota";
	if (estatus.sinbateria)
		return "Sin bateria";
	throw std::invalid_argument("[Moto::getEstado] Error en el estado");*/
}

/**
*@Brief Método encargado de activar la moto
*@Param Cliente: usuario que activa la moto
*/
void Moto::seActiva(Cliente& usuario){
	if (estado == estatus::bloqueada){
		estado = estatus::activa;
		usadoPor = &usuario;
	}
}

/**
*@Brief Método encargado de desactivar la moto
*/
void Moto::seDesactiva(){
	if (estado == estatus::activa) {
		estado = estatus::bloqueada;
		usadoPor = 0;
	}
}
void Moto::setPorcentajeBateria(int porcentaje)
{
	porcentajeBateria = porcentaje;
	if (porcentajeBateria < limiteBateria)
		estado = estatus::sinbateria;
}
int Moto::getPorcentajeBateria()
{
	return porcentajeBateria;
}
/**
*@Brief Setter del campo sinBateria de estatus
*/
void Moto::setSinbateria(){
	estado = estatus::sinbateria;
}
/**
*@Brief Setter del campo Roto de estatus
*/
void Moto::setRoto(){
	estado = estatus::rota;
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
	//if (estatus.bloqueada && !estatus.roto && !estatus.sinbateria) 
	if(estado == estatus::bloqueada)
	{
		return sqrt(pow(this->posicion.latitud - cliente.getPosicion().latitud, 2) + pow(this->posicion.longitud - cliente.getPosicion().longitud, 2));
	}
	return 99999999.99;
}
