// Practica3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
	AVL<int> arbolico;
	int t[10] = {11,0,9,12,4,1,7,5,3,6};
	for (int i = 3;  i >= 0; i--)
	{
		arbolico.inserta(t[i]);
	}
	//TODO: comprobar rotaciones correctas
	arbolico.recorreInorden();
	cout << endl << arbolico.altura();
	return 0;
}
