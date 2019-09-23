#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

#include "VDinamico.h"


using namespace std;

#include "Cliente.h"

void mostrarVDinCliente(VDinamico<Cliente> &vD){
    cout << "tamF: " << vD.getTamF() << " tamL:" << vD.getTamL() << endl;
}

void leeClientes(string fileNameClientes, VDinamico<Cliente>* vector) {
    ifstream fe; //Flujo de entrada
    string linea; //Cada línea tiene un clienete
    int total = 0; //Contador de líneas o clientes

    //Variables auxiliares para almacenar los valores leídos
    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon;



    //Asociamos el flujo al fichero 
    fe.open(fileNameClientes);

    if (fe.good()) {
        //Mientras no se haya llegado al final del fichero
        while (!fe.eof()) {
            getline(fe, linea); //Toma una línea del fichero
            stringstream ss; //Stream que trabaja sobre buffer interno         

            if (linea != "") {
                ++total;
            }

            if (total > 1) {
                //Inicializamos el contenido de ss
                ss << linea;

                //Leemos el NIF
                getline(ss, dni, ';'); //El carácter ; se lee y se elimina de ss

                //Leemos el pass
                getline(ss, pass, ';'); //El caráter ; se lee y se elimina de ss

                //Leemos el nombre
                getline(ss, nombre, ';'); //El caráter ; se lee y se elimina de ss

                //Leemos la dirección
                getline(ss, direccion, ';'); //El caráter ; se lee y se elimina de ss

                //Leemos la latitud y longitud
                getline(ss, latitud, ';'); //El caráter ; se lee y se elimina de ss
                getline(ss, longitud, ';'); //El caráter ; se lee y se elimina de ss

                dlat = stod(latitud);
                dlon = stod(longitud);

                //con todos los atributos leídos, se crea el cliente
                Cliente client(dni, pass, nombre, direccion, dlat, dlon);
                vector->insertarDato(client);
                //cout << "leido e insertado cliente " << total << "  ";
            }
        }

        cout << "Total de clientes en el fichero: " << total << endl;
        fe.close(); //Cerramos el flujo de entrada
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
}

int main(int argc, char** argv) {

    VDinamico<Cliente>* vClientes = new VDinamico<Cliente>;
    
    mostrarVDinCliente(*vClientes);
    
    cout << "Comienzo de lectura de un fichero " << endl;
    leeClientes("clientes_v2.csv", vClientes);
    mostrarVDinCliente(*vClientes);
    
    VDinamico<Cliente> vClientesOrdenado = *vClientes;
    vClientesOrdenado.ordenar();
    Cliente Francesco("Francesco");
    int posicion=vClientesOrdenado.busca(Francesco);
    cout<<posicion;

    delete vClientes;
    return 0;
}

