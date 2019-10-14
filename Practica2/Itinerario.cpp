#include "Itinerario.h"
#include <ctime>
#include <time.h>


int Itinerario::id = 0;

Itinerario::Itinerario() {
	srand(time(0));
	this->minutos = rand() % 120;
	//35 - 44 latitud
	inicio.latitud = ((double)rand() / (double)RAND_MAX) * 9 + 35.;
	fin.latitud = ((double)rand() / (double)RAND_MAX) * 9 + 35.;
	//-9.5 - 3.5 longitud
	inicio.longitud = -9.5 + ((double)rand() / (double)RAND_MAX) * 13;
	fin.longitud = -9.5 + ((double)rand() / (double)RAND_MAX) * 13;
	this->fecha.asignarDia((rand() % 30) + 1, (rand() % 12) + 1, 2019);
	this->id++;
}

Itinerario::~Itinerario(){
	this->id--;
}

int Itinerario::getID()
{
	return id;
}
