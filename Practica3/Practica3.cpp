#include <iostream>
#include "AVL.h"
#include "InterfazUsuario.h"
#include <locale>

int main(){

	setlocale(LC_ALL, "spanish");
	EcoCityMoto test;
	if (menuPrincipal(test))
		return 0;

	//AVL<int> arbol;
	//for (int i = 0; i <= 40; i++)
	//{
	//	arbol.inserta(i);
	//	arbol.verArbol();
	//	std::cout << "Altura " << i << " : " << arbol.altura() << std::endl;
	//}
	//std::cout<<arbol.altura();

	return 0;
}
