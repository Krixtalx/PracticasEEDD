#pragma once
#ifndef UTM_H
#define UTM_H

using namespace std;

/*
 coordenadas UTM formadas por latitud y longitud
 */

struct UTM {
	double latitud;
	double longitud;

	UTM();
	UTM(double _lat, double _long);
};


#endif // !UTM_H