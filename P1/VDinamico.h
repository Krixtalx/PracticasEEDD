/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VDinamico.h
 * Author: jcfer
 *
 * Created on 18 September 2019, 18:24
 */

#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <climits>

//TODO: Lanzar excepciones

template<class T>
class VDinamico {
    int tamL, tamF;
    T** buffer;

    void inicializar();
    void aumentarVector();

public:
    VDinamico();
    VDinamico(unsigned int atamL);
    VDinamico(const VDinamico& orig);
    VDinamico(const VDinamico& orig, unsigned int inicio, unsigned int num);
    virtual ~VDinamico();
    int getTamF() const;
    int getTamL() const;
    T& operator=(VDinamico<T>& asig);
    T& operator[](int value);
    void insertarDato(T& dato, unsigned int pos = UINT_MAX);
    void eliminarDato(unsigned int pos = UINT_MAX);
};

template<class T>
VDinamico<T>::VDinamico() : tamF(1), tamL(0) {
    buffer = new *T[tamF]; //Crea el buffer en memoria dinamica
    inicializar();
}

/**
 * @brief Metodo privado para inicializar cada valor del vector
 */
template<class T>
void VDinamico<T>::inicializar() {
    for (int i = 0; i < tamF; i++) {
        buffer[i] = new T;
    }
}

/**
 * @brief Constructor parametrizado
 * @param atamL Tamanio logico del vector
 * @post Crea un vector en memoria dinamica cuyo tamaño es una potencia de 2 mayor que tamL
 */
template<class T>
VDinamico<T>::VDinamico(unsigned int atamL) {
    tamF = 1;
    tamL = atamL;
    while (tamF <= atamL)
        tamF *= 2;
    *buffer = new T[tamF];
    inicializar();
}

/**
 * @brief Constructor de copia
 * @param orig Vector a copiar
 * @post Crea un vector dinamico igual que orig
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico<T>& orig) : tamF(orig.tamF), tamL(orig.tamL) {
    *buffer = new T[tamF];
    for (int i = 0; i < tamF; i++) {
        *buffer[i] = orig[i];
    }
}

/**
 * @brief Constructor de copia
 * @param orig Vector a copiar
 * @param inicio Inicio del segmento
 * @param num Final del segmento
 * @post Crea un vector dinamico igual a orig
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico& orig, unsigned int inicio, unsigned int num) : tamF(orig.tamF), tamL(orig.tamL) {
    *buffer = new T[tamF];
    inicializar();
    for (int i = inicio; i < num; i++) {
        *buffer[i] = orig[i];
    }
}

template<class T>
VDinamico<T>::~VDinamico() {
    for (int i = 0; i < tamF; i++) {
        delete buffer[i];
    }
    delete[] buffer;
}

template<class T>
int VDinamico<T>::getTamF() const {
    return tamF;
}

template<class T>
int VDinamico<T>::getTamL() const {
    return tamL;
}

/**
 * @brief Operador de asignacion
 * @param asig Vector a copiar
 * @post Crea un nuevo vector dinamico al cual se le asignan los valores del vector dado
 * @return Devuelve el propio objeto para permitir operaciones en cascada
 */
template<class T>
T& VDinamico<T>::operator=(VDinamico<T>& asig) {
    delete[] * buffer;
    tamF = asig.tamF;
    tamL = asig.tamL;
    *buffer = new T[tamF];
    for (int i = 0; i < tamL; i++) {
        *buffer[i] = asig[i];
    }

    return *this;
}

/**
 * @brief Operador []
 * @param value Posicion del vector a la que se accede
 * @return Objeto almacenado en la posicion dada
 */
template<class T>
T& VDinamico<T>::operator[](int value) {
    return *buffer[value];
}

/**
 * @brief Inserta un dato al vector dinamico
 * @param dato Dato a insertar
 * @param pos Posicion donde se insertara el dato
 * @post Inserta el dato en la posicion indicada o al final si no se especifica una posicion
 */
template<class T>
void VDinamico<T>::insertarDato(T& dato, unsigned int pos) {
    if (pos == UINT_MAX) {
        *buffer[tamL++] = dato;
    } else {
        *buffer[pos] = dato;
        tamL++;
    }
}

template<class T>
void VDinamico<T>::eliminarDato(unsigned int pos) {
    tamL--;
    delete buffer[pos];
    for (int i = pos; i < tamL; i++) {
        buffer[pos] = buffer[pos++];
    }
    delete buffer[tamL];
    buffer[tamL] = new T;
}
#endif /* VDINAMICO_H */

