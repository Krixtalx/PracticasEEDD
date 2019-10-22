// Practica3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AVL.h"

int main()
{
	AVL<int> arbolico;
	int t[10] = {11,0,9,12,4,1,7,5,3,6};
	for (int i = 9;  i >= 0; i--)
	{
		arbolico.inserta(t[i]);
	}
	arbolico.verArbol();
	//TODO: comprobar rotaciones correctas
	return 0;
}
