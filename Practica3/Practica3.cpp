// Practica3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AVL.h"

int main()
{
	AVL<int> arbolico;
	int t[11] = {11,0,9,12,4,1,7,5,3,6,2};
	for (int i = 10;  i >= 0; i--){
		arbolico.inserta(t[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		int algo;
		arbolico.verArbol();
		std::cin >> algo;
		arbolico.inserta(algo);
	}
	arbolico.verArbol();
	int resultado;
	if (arbolico.busca(t[7], resultado))
		std::cout << "Encontrao";
	//TODO: comprobar rotaciones correctas
	return 0;
}
