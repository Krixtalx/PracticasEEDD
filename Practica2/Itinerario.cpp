#include "Itinerario.h"
#include <ctime>
#include <time.h>


Itinerario::Itinerario() {
}

Itinerario::Itinerario(int num, const UTM& min, const UTM& max): id(num){
	generaUTM(min, max);
	this->fecha.asignarDia((rand() % 20) + 1, (rand() % 12) + 1, 2019);
	this->minutos = rand() % 300;
}

Itinerario::~Itinerario(){
}

void Itinerario::generaUTM(const UTM& min, const UTM& max)
{
	srand(time(0));
	this->inicio.latitud = ((double)rand() / (double)RAND_MAX) * (max.latitud - min.latitud) + min.latitud;
	this->inicio.longitud = ((double)rand() / (double)RAND_MAX) * (max.longitud - min.longitud) + min.longitud;
	this->fin.latitud = ((double)rand() / (double)RAND_MAX) * (max.latitud - min.latitud) + min.latitud;
	this->fin.longitud = ((double)rand() / (double)RAND_MAX) * (max.longitud - min.longitud) + min.longitud;
}

int Itinerario::getID()
{
	return id;
}
