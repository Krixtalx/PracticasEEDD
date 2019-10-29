#include <iostream>
#include "AVL.h"
#include "InterfazUsuario.h"
#include <locale>
#include "Moto.h"
#include "Cliente.h"

int main(){

	setlocale(LC_ALL, "spanish");
	//EcoCityMoto test;
	//if (menuPrincipal(test))
	//	return 0;

	//AVL<int> arbol;
	//for (int i = 0; i <= 40; i++)
	//{
	//	arbol.inserta(i);
	//	arbol.verArbol();
	//	std::cout << "Altura " << i << " : " << arbol.altura() << std::endl;
	//}
	//std::cout<<arbol.altura();
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
