#include <iostream>
#include <ctime>
#include "InterfazUsuario.h"
#include "EcoCityMoto.h"
#include "THashCliente.h"

int main()
{
	
	Cliente testA("123A", "passA", "PacoA", "xAx", "yAy", 10, 1);
	Cliente testB("231B", "passB", "PacoB", "xBx", "yBy", 11, 11);
	Cliente testC("312C", "passC", "PacoC", "xCx", "yCy", 12, 21);
	Cliente testD("213D", "passD", "PacoD", "xDx", "yDy", 13, 31);
	Cliente testE("321E", "passE", "PacoE", "xEx", "yEy", 14, 41);
	Cliente testF("132F", "passF", "PacoF", "xFx", "yFy", 15, 51);
	Cliente tests[6] = { testA, testB, testC, testD, testE, testF };
	char stop;
	THashCliente tabla(10);
	for (size_t i = 0; i < 6; i++)
	{
		cout << "Cliente " << i << " " << tabla.djb2(tests[i].getDni()) << endl;
		tabla.insertar(tabla.djb2(tests[i].getDni()), tests[i].getDni(), tests[i]);
	}
	tabla.verTabla();
	cout << "Clientes: " << tabla.numCliente() << endl;
	cout << "Maximo de colisiones: " << tabla.maxColisiones() << endl;
	cout << "Promedio de colisiones: " << tabla.promedioColisiones() << endl;
	cout << "Factor de carga: " << tabla.factorCarga() << endl;
	tabla.redispersar(tabla.tamaTabla() * 2);
	tabla.verTabla();
	/*srand(time(0));
	setlocale(LC_ALL, "spanish");
	EcoCityMoto app;
	menuPrincipal(app);*/
	return 0;
}