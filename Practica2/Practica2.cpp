#include <iostream>
#include <ctime>
#include "VDinamico.h"


using namespace std;
int main()
{
	VDinamico<int> ola;
	srand(time(0));
	for (int i = 10; i >= 0; i--)
	{
		int owo = rand() % 100;
		ola.insertarDato(owo);
	}

	for (int j = 0; j < ola.getTamL(); j++)
	{
		cout << ola[j] << endl;
	}

	
	cout << "I N C O M I N G OWOWOWOWOWOOWOWOWOWOOWOWOWOWO" << endl << endl;
	cout << "owo xd" << endl;
}
