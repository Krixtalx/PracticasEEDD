#ifndef ITINERARIO_H
#define ITINERARIO_H

#include "Cliente.h"
#include "Fecha.h"

class Itinerario
{
	int id = 0, minutos = 0;
	UTM inicio, fin;
	Fecha fecha;
	//TODO: idGlobal compartida entre todos los objetos
public:
	Itinerario();
	~Itinerario();
	int getID();
};


#endif // !ITINERARIO_H