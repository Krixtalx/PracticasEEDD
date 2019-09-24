/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.cpp
 * Author: jcfer
 * 
 * Created on 23 September 2019, 20:39
 */

#include "Cliente.h"

UTM::UTM() : latitud(0), longitud(0) {

}

UTM::UTM(double _lat, double _long) : latitud(_lat), longitud(_long) {
}

Cliente::Cliente() : dni(""), pass(""), nombre(""), apellido(""), direccion("") {
}

Cliente::Cliente(string nombre) :
nombre(nombre) {
}


Cliente::Cliente(string _dni, string _pass, string _nombre, string _apellido, string _direccion, double _latitud, double _longitud) :
dni(_dni), pass(_pass), nombre(_nombre), apellido(_apellido), direccion(_direccion), posicion(_latitud, _longitud) {
}

Cliente::Cliente(const Cliente& orig): dni(orig.dni), pass(orig.pass), nombre(orig.nombre), apellido(orig.apellido), direccion(orig.direccion) {
    posicion.latitud = orig.posicion.latitud;
    posicion.longitud = orig.posicion.longitud;
}

Cliente::~Cliente() {
}

/**
 * @brief Compara dos clientes por su nombre
 * @param otro Cliente a comparar
 * @return True si el nombre del cliente *this es menor alfabeticamente que el de otro
 */
bool Cliente::operator<(Cliente& otro) {
    if (this->nombre < otro.nombre)
        return true;
    return false;
}

Cliente& Cliente::operator=(const Cliente& right) {  
    if (this == &right) 
        return *this; 
    
    this->direccion = right.direccion;
    this->dni = right.dni;
    this->nombre = right.nombre;
    this->apellido = right.apellido;
    this->pass = right.pass;
    this->posicion=right.posicion;
    
    return *this;
}

string Cliente::GetApellido() const {
    return apellido;
}

string Cliente::GetNombre() const {
    return nombre;
}
