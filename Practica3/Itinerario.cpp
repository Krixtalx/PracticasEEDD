#include "Itinerario.h"
#include "Moto.h"
#include <ctime>
#include <time.h>


Itinerario::Itinerario() {
}

/**
*@Brief Constructor parametrizado
*@param num, id que tomar� el itinerario
*@param min, max UTMs que indican las coordenadas UTM minimas y maximas que se generaran
*/
Itinerario::Itinerario(int num, const UTM& min, const UTM& max): id(num){
	generaUTM(min, max);
	srand(time(0)+rand());
	const unsigned int diasMes[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	unsigned int ano = (rand() % 40)+2019;
	unsigned int mes = (rand() % 12)+1;
	unsigned int dia;
	if (mes==2){
		if (ano%4==0){
			dia = (rand() % 29)+1;
		}
		else {
			dia = (rand() % 28)+1;
		}
	}
	else {
		dia = (rand() % diasMes[mes - 1])+1;
	}
	this->fecha.asignarDia(dia, mes, ano);
	this->minutos = (rand() % 500) +1;
}

/**
	@brief Destructor
*/
Itinerario::~Itinerario(){
}

/**
	@brief Operador de asignacion
	@param right Objeto cuyos atributos se usan en la asignacion
	@return El propio objeto para operaciones en cascada
*/
Itinerario& Itinerario::operator=(Itinerario& right)
{
	id = right.id;
	minutos = right.minutos;
	inicio = right.inicio;
	fin = right.fin;
	fecha = right.fecha;
	vehiculo = right.vehiculo;
	return *this;
}

/**
*@Brief Generador pseudoaleatorio de coordenadas UTM de inicio y fin
*/
void Itinerario::generaUTM(const UTM& min, const UTM& max)
{
	srand(time(0)+rand());
	this->inicio.latitud = ((double)rand() / (double)RAND_MAX) * (max.latitud - min.latitud) + min.latitud;
	this->inicio.longitud = ((double)rand() / (double)RAND_MAX) * (max.longitud - min.longitud) + min.longitud;
	this->fin.latitud = ((double)rand() / (double)RAND_MAX) * (max.latitud - min.latitud) + min.latitud;
	this->fin.longitud = ((double)rand() / (double)RAND_MAX) * (max.longitud - min.longitud) + min.longitud;
}

/**
*@Brief Getter del atributo ID
*/
int Itinerario::getID(){
	return id;
}

void Itinerario::setInicio(UTM& pos)
{
	inicio = pos;
}

void Itinerario::setVehiculo(Moto* m)
{
	vehiculo = m;
}

void Itinerario::setMinutos(int mins)
{
	minutos = mins;
}

Moto* Itinerario::getVehiculo()
{
	return vehiculo;
}

/**
*@Brief Devuelve un string en formato CSV con los atributos del objeto
*/
std::string Itinerario::toCSV(){
	std::string idString = to_string(id);
	std::string minutosString = to_string(minutos);
	std::string inicioString = inicio.toCSV();
	std::string finString = fin.toCSV();
	std::string fechaString = fecha.cadena();
	return idString + ";" + minutosString + ";" + inicioString + ";" + finString + ";" + fechaString;
}
