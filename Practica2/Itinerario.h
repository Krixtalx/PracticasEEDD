#ifndef ITINERARIO_H
#define ITINERARIO_H

#include "Fecha.h"
#include "UTM.h"

class Itinerario{
	int id=0;
	int minutos = 0;
	UTM inicio, fin;
	Fecha fecha;
	//TODO: idGlobal compartida entre todos los objetos
public:
	Itinerario();
	Itinerario(int num, const UTM& min, const UTM& max);
	~Itinerario();
	void generaUTM(const UTM &min, const UTM& max);
	int getID();
};


#endif // !ITINERARIO_H