#ifndef ITINERARIO_H
#define ITINERARIO_H

#include "Fecha.h"
#include "UTM.h"

class Moto;

class Itinerario{
	int id=0;
	int minutos = 0;
	UTM inicio, fin;
	Fecha fecha;
	Moto* vehiculo = 0;

public:
	Itinerario();
	Itinerario(int num, const UTM& min, const UTM& max);
	~Itinerario();
	void generaUTM(const UTM &min, const UTM& max);
	int getID();
	void setInicio(UTM& pos);
	void setVehiculo(Moto* m);
	void setMinutos(int mins);
	Moto* getVehiculo();
	std::string toCSV();
};


#endif // !ITINERARIO_H