#include "Itinerario.h"
#include <ctime>
#include <time.h>


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
}

Itinerario::Itinerario(int num): id(num){
}

Itinerario::~Itinerario(){
}

int Itinerario::getID()
{
	return id;
}
