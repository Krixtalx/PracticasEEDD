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
	if (!prueba.insertar(prueba.djb2(cliDNI), cliDNI, test))
		std::cerr << "NO SE PUDO INSERTAR" << std::endl;
	prueba.verTabla();
	Cliente* buscado = 0;
	if (!prueba.buscar(prueba.djb2(cliDNI), cliDNI, buscado))
		std::cerr << "NO SE ENCONTRO EL CLIENTE" << std::endl;
	else {
		if (buscado)
			std::cout << buscado->toCSV() << std::endl;
	}
	/*srand(time(0));
	setlocale(LC_ALL, "spanish");
	EcoCityMoto app;
	menuPrincipal(app);*/
	return 0;
}