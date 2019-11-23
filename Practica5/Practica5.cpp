#include <iostream>
#include <ctime>
//#include "InterfazUsuario.h"
#include "EcoCityMoto.h"
#include "THashCliente.h"
#include "locale.h"
#include <string>
#include "leerFich.h"

void IA(EcoCityMoto& ecocity) {
	unsigned interacciones, maxCol=0, primo=0, sumHash, pNuevaTabla;
	float  pCol = 20;
	string archivo = "clientes.csv";
	std::vector<Cliente>* v=leerFich::ficheroaVector(archivo);
	
	cout << "Introduzca el nº de interacciones: ";
	cin >> interacciones;
	system("cls");
	for (unsigned i = 0; i < interacciones; i++)
	{

		ecocity.vectorToTabla(v);
		if (pCol > ecocity.getTabla()->promedioColisiones()) {
			maxCol = ecocity.getTabla()->maxColisiones();
			pCol = ecocity.getTabla()->promedioColisiones();
			primo = ecocity.getTabla()->primoHash2;
			sumHash = ecocity.getTabla()->sumHash2;
			pNuevaTabla = ecocity.getTabla()->pNuevaTabla;
		}

		system("cls");
		cout << "                                     Interacción " << i+1<<endl<<endl;
		cout << "                                     TAM " << ecocity.getTabla()->tamaTabla() << endl << endl;

		cout << "ACTUAL MEJOR                                                    ULTIMO PROBADO" << endl;
		cout << "MAX COLISIONES: " << maxCol<<"                                             MAX COLISIONES: "<< ecocity.getTabla()->maxColisiones() << endl;
		cout << "PROMEDIO COLISIONES: " << pCol <<"                                 PROMEDIO COLISIONES: "<< ecocity.getTabla()->promedioColisiones() << endl;
		cout << "PRIMO: " << primo<<"                                                          PRIMO:" << ecocity.getTabla()->primoHash2 << endl<<endl;

		ecocity.getTabla()->primoHash2 = ecocity.getTabla()->siguientePrimo(ecocity.getTabla()->primoHash2);

	}
}



int main()
{

	setlocale(LC_ALL, "spanish");

	char stop;
	size_t tamtabla = 5000;
	EcoCityMoto aLaVergaTodo(0, tamtabla);
	THashCliente* funciona = aLaVergaTodo.getTabla();
	cout << "TAM: " << funciona->numCliente() << endl;
	cout << "FCARGA: " << funciona->factorCarga() << endl;
	cout << "MAX COLISIONES: " << funciona->maxColisiones() << endl;
	cout << "PROMEDIO COLISIONES: " << funciona->promedioColisiones() << endl;

	IA(aLaVergaTodo);




	/*
	vector<string>* dnis = aLaVergaTodo.getDniClientes();
		
	size_t i;
	for (i = dnis->size() - 1; i > dnis->size()-2000; i--) {
		if (funciona->borrar(funciona->djb2((*dnis)[i]), (*dnis)[i]))
			cout << "BORRAO " << (*dnis)[i] << endl;
		else {
			cout << "MENUDA F LOCO " << i << endl;
			return 0;
		}
	}


	cout << "DONE: " << i << endl;
	cout << "TAM: " << funciona->numCliente() << endl;
	cout << "FCARGA: " << funciona->factorCarga() << endl;
	cout << "MAX COLISIONES: " << funciona->maxColisiones() << endl;
	cout << "PROMEDIO COLISIONES: " << funciona->promedioColisiones() << endl;
	*/

	/*srand(time(0));
	EcoCityMoto app;
	menuPrincipal(app);*/
	return 0;
}