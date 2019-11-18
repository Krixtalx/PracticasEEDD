#include <iostream>
#include <ctime>
#include "InterfazUsuario.h"
#include "EcoCityMoto.h"
#include "THashCliente.h"

int main()
{
	Cliente test("100", "test", "Test", "xx", "yy", 5, 7);
	string cliDNI = test.getDni();
	THashCliente prueba(5);
	prueba.insertar(prueba.djb2(cliDNI), cliDNI, test);
	prueba.verTabla();
	/*srand(time(0));
	setlocale(LC_ALL, "spanish");
	EcoCityMoto app;
	menuPrincipal(app);*/
	return 0;
}