// Practica3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AVL.h"

int main()
{
	AVL<int> arbolico;
	int t[11] = {10,9,8,7,6,5,4,3,2,1,0};
	for (int i = 10;  i >= 0; i--){
		arbolico.inserta(t[i]);
		arbolico.verArbol();
	}
	for (int i = 10; i < 10; i++)
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
