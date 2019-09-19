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

//TODO: Lanzar excepciones BAD_ALLOC

template<class T>
class VDinamico {
private:
    int tamL, tamF; //Tamaño lógico y tamaño fisico
    T* buffer;
    bool sorted=false;
    void aumentarTamF();
    void disminuirTamF();

public:
    VDinamico();
    VDinamico(unsigned int atamL);
    VDinamico(const VDinamico& orig);
    VDinamico(const VDinamico& orig, unsigned int inicio, unsigned int num);
    virtual ~VDinamico();
    T& getTamF();
    T& getTamL();
    T& operator=(VDinamico<T>& asig);
    T& operator[](int pos);
    void insertarDato(T& dato, unsigned int pos = UINT_MAX);
    void eliminarDato(unsigned int pos = UINT_MAX);
};

/**
 * @brief Constructor por defecto
 * @post Crea un nuevo vector dinamico de tamF = 1
 */
template<class T>
VDinamico<T>::VDinamico() : tamF(1), tamL(0) {
    buffer = new T[tamF];
}

/**
 * @brief Constructor parametrizado
 * @param atamL Tamanio logico del vector a crear
 * @post Crea un nuevo vector dinamico con capacidad para el numero de datos indicado
 */
template<class T>
VDinamico<T>::VDinamico(unsigned int atamL) : tamL(atamL), tamF(1) {
    while (tamF < tamL)
        tamF *= 2;
    buffer = new T[tamF];
}

/**
 * @brief Constructor por copia
 * @param orig Vector a copiar
 * @post Crea un nuevo vector dinamico igual al vector dado
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico& orig) : tamF(orig.tamF), tamL(orig.tamL) {
    buffer = new T[tamF];
    for (int i = 0; i < tamL; i++) {
        buffer[i] = orig[i];
    }
}

/**
 * @brief Constructor por copia parcial
 * @param orig Vector a copiar
 * @param inicio Comienzo del fragmento a copiar
 * @param num Numero de elementos a copiar
 * @post Crea un nuevo vector dinamico cuyo contenido es el fragmento indicado del vector dado
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico& orig, unsigned int inicio, unsigned int num) : tamL(num), tamF(orig.tamF) {
    //TODO: Excep. si el fragmento a copiar esta fuera de los limites del vector
    buffer = new T[tamF];
    for (int i = 0; i < num; i++) {
        buffer[i] = orig[inicio++];
    }
}

/**
 * @brief Destructor
 */
template<class T>
VDinamico<T>::~VDinamico() {
    delete[] buffer;
}

template<class T>
T& VDinamico<T>::getTamF() {
    return tamF;
}

template<class T>
T& VDinamico<T>::getTamL() {
    return tamL;
}

/**
 * @brief Operador de asignacion
 * @param asig Vector a copiar
 * @post Recrea el vector dinamico igual al vector dado
 * @return Propio vector para permitir operaciones en cascada
 */
template<class T>
T& VDinamico<T>::operator=(VDinamico<T>& asig) {
    delete[] buffer;
    tamF = asig.tamF;
    tamL = asig.tamL;
    buffer = new T[tamF];
    for (int i = 0; i < tamL; i++) {
        buffer[i] = asig[i];
    }
    return *this;
}

/**
 * @brief Operador []
 * @param pos Posicion a acceder en el vector
 * @return Valor almacenado en la posicion indicada
 */
template<class T>
T& VDinamico<T>::operator[](int pos) {
    //TODO: Excep. si pos no esta en el rango permitido
    return buffer[pos];
}

/**
 * @brief Inserta un dato en el vector
 * @param dato Dato a insertar
 * @param pos Posicion donde colocar el dato
 * @post Inserta el dato en la posicion indicada, desplazando el resto de datos
 */
template<class T>
void VDinamico<T>::insertarDato(T& dato, unsigned int pos) {
    //TODO: Excep. si pos no esta en el rango permitido
    if (pos == UINT_MAX) {
        buffer[tamL++] = dato;
    } else {
        tamL++;
        
        if (tamL == tamF) {
            aumentarTamF();
        }

        for (int i = tamL; i > pos; i--) {
            buffer[i] = buffer[i - 1];
        }
        buffer[pos] = dato;
        tamL++;
    }
}

/**
 * @brief Elimina un dato del vector
 * @param pos Posicion del dato a borrar
 * @post Elimina el dato indicado y reorganiza los elementos del vector
 */
template<class T>
void VDinamico<T>::eliminarDato(unsigned int pos) {
    //TODO: Excep. si pos no esta en el rango permitido
    
    if (pos != UINT_MAX) {
        for (int i = pos; i + 1 < tamL; i++) {
            buffer[i] = buffer[i + 1];
        }
    }else{
        buffer[tamL]=0;
    }
    
    tamL--;
    
    if(tamL*3<=tamF)
        disminuirTamF();
}

/**
* @brief Crea un nuevo buffer con el doble de tamaño físico, copia todos los elementos del buffer anterior y borra el anterior buffer
* @post  El anterior buffer queda eliminado
*/
template <class T>
void VDinamico<T>::aumentarTamF(){
    int prevTamF=tamF;
    T* NuevoBuffer = new T[tamF*=2];
    for (int i = 0; i < prevTamF; i++) {
        NuevoBuffer[i]=buffer[i];
    }
}

/**
* @brief Crea un nuevo buffer con la mitad de tamaño físico, copia todos los elementos del buffer anterior y borra el anterior buffer
* @post  El anterior buffer queda eliminado
*/
template <class T>
void VDinamico<T>::disminuirTamF(){
    T* NuevoBuffer = new T[tamF/=2];
    for (int i = 0; i < tamF; i++) {
        NuevoBuffer[i]=buffer[i];
    }
}
#endif /* VDINAMICO_H */

