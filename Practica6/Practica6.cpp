#include <iostream>
#include "MallaRegular.h"

using namespace std;



int main()
{
	MallaRegular<unaPosicion> estoPeta(0, 0, 15, 15, 3, 3);
	unaPosicion a(4.7, 12), b(10.2, 10.2), c(4.7, 4.7), d(10.2, 4.7), hola(9,9);
	estoPeta.insertar(a);
	estoPeta.insertar(b);
	estoPeta.insertar(c);
	estoPeta.insertar(d);
	estoPeta.insertar(hola);
	unaPosicion cercano = estoPeta.buscarCercano(5.1, 5.1);
	cout << "Encontrao: " << cercano.getX() << " - " << cercano.getY() << endl;
	//cout << "Buscas " << x << " " << y << ": " << (int)((x - estoPeta.xMin) / estoPeta.interX) << " - " << (int)((y - estoPeta.yMin) / estoPeta.interY) << endl;
}