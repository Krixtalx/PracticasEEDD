#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <list>
#include "UTM.h"
#include "Itinerario.h"

using namespace std;

class EcoCityMoto;
class PuntoRecarga;

class Cliente {
private:
	string dni = "";
	string pass = "";
	string nombre = "";
	string apellido = "";
	string direccion = "";
	string nombreCompleto = "";
	string display = "";
	UTM posicion;
	std::list<Itinerario*>* listaItinerarios=0;
	EcoCityMoto* aplicacion = 0;
	int puntos = 0;

public:
	Cliente();
	Cliente(string dni);
	Cliente(string _dni, string _pass, string _nombre, string _apellido, string _direccion, double _latitud, double _longitud, int _puntos);
	Cliente(const Cliente& orig);
	virtual ~Cliente();
	bool operator<(Cliente& otro);
	bool operator>(Cliente& otro);
	bool menorQue(Cliente& otro);
	Cliente& operator=(const Cliente& right);
	string getPass();
	string GetApellido() const;
	string GetNombre() const;
	string GetNombreCompleto() const;
	string getDni() const;
	double DistanciaCliente(Cliente& otro);
	UTM getPosicion() const;
	void crearItinerarios(int num, UTM& minimo, UTM& maximo);
	std::list<Itinerario*>& getItinerarios();
	friend ostream& operator<<(ostream& os, const Cliente& cliente);
	void setAplicacion(EcoCityMoto* app);
	Moto& buscaMotoCercana();
	void creaItinerario(Moto& m);
	void desbloqueaMoto(Moto& m);
	void terminarTrayecto(bool forzarBateria);
	void addItinerario(Itinerario* iti);
	string toCSV();
	void mostrarMensaje(string texto);
	string& getDisplay();

	int getPuntos();
	void decrementarPunto();
	void incrementarPunto();
	void puntoRecargaCercano();
	void recargarMoto(PuntoRecarga* pr);
};

#endif /* CLIENTE_H */