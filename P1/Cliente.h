#ifndef CLIENTE_H
#define CLIENTE_H

#include<string>


using namespace std;

/*
 coordenadas UTM formadas por latitud y longitud
 */

struct UTM {
    double latitud;
    double longitud;

    UTM();
    UTM(double _lat, double _long);
};

class Cliente {
    string dni="";
    string pass="";
    string nombre="";
    string apellido="";
    string direccion="";
    string nombreCompleto="";
    UTM posicion;

public:
    Cliente();
    Cliente(string nombre);
    Cliente(string _dni, string _pass, string _nombre, string _apellido, string _direccion, double _latitud, double _longitud);
    Cliente(const Cliente& orig);
    virtual ~Cliente();
    bool operator<(Cliente& otro);
    bool menorQue(Cliente& otro);
    Cliente& operator=(const Cliente& right);
    string GetApellido() const;
    string GetNombre() const;
    string GetNombreCompleto() const;
    double DistanciaCliente(Cliente& otro);
    UTM getPosicion() const;


};

#endif /* CLIENTE_H */
