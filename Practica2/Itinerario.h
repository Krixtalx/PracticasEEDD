#ifndef ITINERARIO_H
#define ITINERARIO_H

#include "Fecha.h"
#include "UTM.h"

class Itinerario{
	static int id;
	int minutos = 0;
	UTM inicio, fin;
	Fecha fecha;
	//TODO: idGlobal compartida entre todos los objetos
public:
	Itinerario();
	~Itinerario();
	int getID();
};


#endif // !ITINERARIO_H