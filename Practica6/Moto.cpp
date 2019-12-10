#include "Moto.h"

/**
	@brief Constructor por defecto
*/
Moto::Moto() : id("0") {
	porcentajeBateria = rand() % 100;
}

/**
	@brief Constructor parametrizado
*/
Moto::Moto(std::string id, UTM posicion, estatus _estado, int porcentajeBateria): id(id), posicion(posicion), estado(_estado), porcentajeBateria(porcentajeBateria),usadoPor(0){

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

void Moto::setUTM(UTM& _posicion)
{
	posicion = _posicion;
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

Cliente* Moto::getCliente()
{
	return usadoPor;
}

/**
	@brief Devuelve el estado actual de la moto
*/
estatus Moto::getEstado()
{
	return estado;
}

void Moto::setEstado(estatus _estado)
{
	estado = _estado;
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
void Moto::seDesactiva(int duracion, int limiteBateria){
	if (estado == estatus::activa) {
		estado = estatus::bloqueada;
		usadoPor = 0;
		setPorcentajeBateria(porcentajeBateria-duracion, limiteBateria);
	}
}
void Moto::setPorcentajeBateria(int porcentaje, int limiteBateria)
{
	porcentajeBateria = porcentaje;
	if (porcentajeBateria < limiteBateria)
		estado = estatus::sinbateria;
	else
		estado = estatus::bloqueada;
}
int Moto::getPorcentajeBateria()
{
	return porcentajeBateria;
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
	if(estado == estatus::bloqueada)
	{
		return sqrt(pow(this->posicion.latitud - cliente.getPosicion().latitud, 2) + pow(this->posicion.longitud - cliente.getPosicion().longitud, 2));
	}
	return 99999999.99;
}

void Moto::comprobarBateria(int limiteBateria)
{
	if (porcentajeBateria < limiteBateria)
		estado = estatus::sinbateria;
}

void Moto::recargar(PuntoRecarga* pr)
{
	posicion.latitud = pr->getX();
	posicion.longitud = pr->getY();
	terminarRecarga();
}

void Moto::terminarRecarga()
{
	porcentajeBateria = 100;
	estado = bloqueada;
}
