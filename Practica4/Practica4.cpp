#include <iostream>
#include <ctime>
#include "InterfazUsuario.h"
#include "EcoCityMoto.h"

#include <sstream>

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "spanish");
	EcoCityMoto app;
	menuPrincipal(app);
}