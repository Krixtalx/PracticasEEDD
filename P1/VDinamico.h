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
    T* buffer;

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
VDinamico<T>::VDinamico(): tamF(1), tamL(0){
    buffer = new T[tamF];
}

template<class T>
VDinamico<T>::VDinamico(unsigned int atamL): tamL(atamL), tamF(1){
    while(tamF < tamL)
        tamF *= 2;
    buffer = new T[tamF];
}

#endif /* VDINAMICO_H */

