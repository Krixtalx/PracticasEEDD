#include <iostream>
#include <ctime>
//#include "InterfazUsuario.h"
#include "EcoCityMoto.h"
#include "THashCliente.h"
#include "locale.h"
#include <string>
#include "leerFich.h"

void IA(EcoCityMoto& ecocity) {
	unsigned maxCol=0, primo=0, sumHash=0, pNuevaTabla;
	unsigned mejorMax = 0, mejorPrimo = 0, mejorSum = 0, mejorTam = 5000, tamInicial = 5000, tamOriginal;
	float  pCol = 20;
	ifstream datosIA;
	string archivoIA = "iaData.txt";
	datosIA.open(archivoIA);
	if (datosIA.good()) {
		string linea, maxStr, primoStr, sumStr, tamStr, colStr;
		getline(datosIA, linea);
		stringstream ss;
		ss << linea;
		getline(ss, maxStr, ';');
		getline(ss, primoStr, ';');
		getline(ss, sumStr, ';');
		getline(ss, tamStr, ';');
		getline(ss, colStr);
		mejorMax = stoi(maxStr);
		mejorPrimo = stoi(primoStr);
		mejorSum = stoi(sumStr);
		mejorTam = stoi(tamStr);
		setlocale(LC_ALL, "english");
		pCol = stof(colStr);
		setlocale(LC_ALL, "spanish");
		tamInicial = mejorTam;
		tamOriginal = tamInicial;
	}
	datosIA.close();
	unsigned interPrimo, interSum, interTam;
	string archivo = "clientes.csv";
	std::vector<Cliente*>* v=leerFich::ficheroaVector(archivo);

	cout << "Introduzca el nº de interacciones para primo: ";
	cin >> interPrimo;
	cout << "Introduzca el nº de interacciones para sum: ";
	cin >> interSum;
	cout << "Introduzca el nº de interacciones para tam: ";
	cin >> interTam;
	system("cls");
	for (size_t itPrimos = 0; itPrimos < interPrimo; itPrimos++) {
		
		for (size_t itSum = 0; itSum < interSum; itSum++) {
			tamInicial = tamOriginal;
			for (size_t itTam = 0; itTam < interTam; itTam++) {
				if (itPrimos == 0 && itSum == 0 && itTam == 0) {
					ifstream ultimo;
					string ultimoFich = "iaLast.txt";
					ultimo.open(ultimoFich);
					if (ultimo.good()) {
						stringstream ss;
						string lin, tama, prim, suma, promedio;
						getline(ultimo, lin);
						ss << lin;
						getline(ss, prim, ';');
						getline(ss, suma, ';');
						getline(ss, tama, ';');
						getline(ss, promedio, ';');
						ecocity.vectorToTabla(v, stoi(tama), stoi(prim), stoi(suma));
						setlocale(LC_ALL, "english");
						pCol = stof(promedio);
						setlocale(LC_ALL, "spanish");
					}
					else
					{
						ecocity.vectorToTabla(v, tamInicial, mejorPrimo, mejorSum);
					}
					ultimo.close();
				}
				else
					ecocity.vectorToTabla(v, tamInicial, ecocity.getTabla()->primoHash2, ecocity.getTabla()->sumHash2);
				THashCliente* tabla = ecocity.getTabla();
				if (tabla->promedioColisiones() < pCol) {
					mejorMax = tabla->maxColisiones();
					mejorPrimo = tabla->primoHash2;
					mejorSum = tabla->sumHash2;
					mejorTam = tabla->tamInicial;
					pCol = tabla->promedioColisiones();
				}
				system("cls");
				cout << "Interacciones: " << itPrimos+1 << " primos, " << itSum+1 << " suma, " << itTam+1 << " tamTabla" << endl << endl;

				cout << "ACTUAL MEJOR                                                    ULTIMO PROBADO" << endl;
				cout << "MAX COLISIONES: " << mejorMax << "                                             MAX COLISIONES: " << tabla->maxColisiones() << endl;
				cout << "PROMEDIO COLISIONES: " << pCol << "                                 PROMEDIO COLISIONES: " << tabla->promedioColisiones() << endl;
				cout << "TAMTABLA: " << mejorTam << "                                                      TAM INICIAL: " << tabla->tamInicial << endl;
				cout << "PRIMO: " << mejorPrimo << "                                                          PRIMO:" << tabla->primoHash2 << endl;
				cout << "SUMA: " << mejorSum << "                                                               SUMA:" << tabla->sumHash2 << endl << endl;

				tamInicial = tabla->siguientePrimo(tamInicial);
			}
			ecocity.getTabla()->sumHash2 = ecocity.getTabla()->siguientePrimo(ecocity.getTabla()->sumHash2);
		}
		ecocity.getTabla()->primoHash2 = ecocity.getTabla()->siguientePrimo(ecocity.getTabla()->primoHash2);
	}
	ofstream iaOut;
	iaOut.open(archivoIA);
	if (iaOut.good()) {
		iaOut << mejorMax << ";" << mejorPrimo << ";" << mejorSum << ";" << mejorTam << ";" << pCol;
	}
	iaOut.close();
	ofstream iaUltimo;
	string archivoUltimo = "iaLast.txt";
	iaUltimo.open(archivoUltimo);
	if (iaUltimo.good()) {
		iaUltimo << ecocity.getTabla()->primoHash2 << ";" << ecocity.getTabla()->sumHash2 << ";" << ecocity.getTabla()->tamInicial << ";" << ecocity.getTabla()->promedioColisiones();
	}
	iaUltimo.close();
	/*for (unsigned i = 0; i < interacciones; i++)
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
		cout << "PRIMO: " << primo<<"                                                          PRIMO:" << ecocity.getTabla()->primoHash2 << endl;
		cout << "SUMA: " << sumHash << "                                                               SUMA:" << ecocity.getTabla()->sumHash2 << endl << endl;

		ecocity.getTabla()->primoHash2 = ecocity.getTabla()->siguientePrimo(ecocity.getTabla()->primoHash2);
		ecocity.getTabla()->sumHash2 = ecocity.getTabla()->siguientePrimo(ecocity.getTabla()->sumHash2);

	}*/

	for (unsigned i = 0; i < v->size(); i++){
		delete (*v)[i];
	}
	delete v;
}



int main()
{

	setlocale(LC_ALL, "spanish");

	char stop;
	size_t tamtabla = 5000;
	EcoCityMoto aLaVergaTodo(0, tamtabla);
	IA(aLaVergaTodo);
	//THashCliente* funciona = aLaVergaTodo.getTabla();
	//cout << "TAM: " << funciona->numCliente() << endl;
	//cout << "FCARGA: " << funciona->factorCarga() << endl;
	//cout << "MAX COLISIONES: " << funciona->maxColisiones() << endl;
	//cout << "PROMEDIO COLISIONES: " << funciona->promedioColisiones() << endl;






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