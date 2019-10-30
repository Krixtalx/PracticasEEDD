#include <iostream>
#include "AVL.h"
#include "InterfazUsuario.h"
#include <locale>
#include "Moto.h"
#include "Cliente.h"

int main(){

	setlocale(LC_ALL, "spanish");

	EcoCityMoto appWapa;
	Cliente test("7");
	test.setAplicacion(&appWapa);
	UTM posTest(1,54);
	Moto motico("unamoto", posTest, {true,false,false,false});
	test.creaItinerario(motico);
	test.creaItinerario(motico);
	appWapa.insertaCliente(test);
	menuPrincipal(appWapa);
	return 0;
}
