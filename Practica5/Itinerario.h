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
	Itinerario(int _id, int _minutos, UTM& _inicio, UTM& _fin, Fecha& _fecha);
	~Itinerario();
	Itinerario& operator= (Itinerario& right);
	void generaUTM(const UTM &min, const UTM& max);
	int getID();
	int getDuracion();
	void setInicio(UTM& pos);
	UTM& getFin();
	void setVehiculo(Moto* m);
	void setMinutos(int mins, int limiteBateria);
	Moto* getVehiculo();
	std::string toCSV();
};


#endif // !ITINERARIO_H