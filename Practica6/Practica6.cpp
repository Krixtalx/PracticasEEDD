#include <iostream>
#include <ctime>
#include "EcoCityMoto.h"
#include "InterfazUsuario.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "spanish");
	size_t tamtabla = 15991;
	srand(time(0));
	EcoCityMoto app(0, tamtabla);
	login(app);
	return 0;
}