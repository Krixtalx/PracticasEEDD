#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include "UTM.h"
#include "ListaDEnlazada.h"
#include "Itinerario.h"

using namespace std;

class EcoCityMoto;

class Cliente {
private:
	string dni = "";
	string pass = "";
	string nombre = "";
	string apellido = "";
	string direccion = "";
	string nombreCompleto = "";
	UTM posicion;
	ListaDEnlazada<Itinerario> listaItinerarios;
	EcoCityMoto* aplicacion = 0;

public:
	Cliente();
	Cliente(string dni);
	Cliente(string _dni, string _pass, string _nombre, string _apellido, string _direccion, double _latitud, double _longitud);
	Cliente(const Cliente& orig);
	virtual ~Cliente();
	bool operator<(Cliente& otro);
	bool operator>(Cliente& otro);
	bool menorQue(Cliente& otro);
	Cliente& operator=(const Cliente& right);
	string GetApellido() const;
	string GetNombre() const;
	string GetNombreCompleto() const;
	double DistanciaCliente(Cliente& otro);
	UTM getPosicion() const;
	void crearItinerarios(int num, UTM& minimo, UTM& maximo);
	ListaDEnlazada<Itinerario>& getItinerarios();
	friend ostream& operator<<(ostream& os, const Cliente& cliente);
	void setAplicacion(EcoCityMoto* app);
	Moto& buscaMotoCercana();
	void creaItinerario(Moto& m);
	void desbloqueaMoto(Moto& m);
	void terminarTrayecto();
};

#endif /* CLIENTE_H */