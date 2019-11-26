#include <iostream>
#include <ctime>
#include "InterfazUsuario.h"
#include "EcoCityMoto.h"
#include "THashCliente.h"
#include "locale.h"
#include <string>
#include "leerFich.h"


int main()
{
	setlocale(LC_ALL, "spanish");
	//TODO: volver a crear itinerarios relacionando % de bateria y duracion
	size_t tamtabla = 5413;
	srand(time(0));
	EcoCityMoto app(0, tamtabla);
	/*string archivo = "clientes.csv";
	std::vector<Cliente*>* v = leerFich::ficheroaVector(archivo);
	app.vectorToTabla(v, 5413, 103, 467);*/
	cout << app.estadoTabla();
	//login(app);
	return 0;
}