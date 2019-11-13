#include <iostream>
#include <ctime>
#include "InterfazUsuario.h"
#include "EcoCityMoto.h"

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "spanish");
	EcoCityMoto app;
	menuPrincipal(app);
	return 0;
}