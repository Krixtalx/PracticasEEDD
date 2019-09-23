/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.h
 * Author: jcfer
 *
 * Created on 23 September 2019, 20:39
 */

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
    string dni;
    string pass;
    string nombre;
    string direccion;
    UTM posicion;

public:
    Cliente();
    Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud);
    Cliente(const Cliente& orig);
    virtual ~Cliente();
    bool operator<(Cliente& otro);
};

#endif /* CLIENTE_H */

