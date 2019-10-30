#include <iostream>
#include "AVL.h"
#include "InterfazUsuario.h"
#include <locale>
#include "Moto.h"
#include "Cliente.h"

int main(){

	setlocale(LC_ALL, "spanish");

	EcoCityMoto appWapa;
	menuPrincipal(appWapa);
	return 0;
}
