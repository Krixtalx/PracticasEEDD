#pragma once
#ifndef UTM_H
#define UTM_H

#include <string>
using namespace std;

/*
 coordenadas UTM formadas por latitud y longitud
 */

struct UTM {
	double latitud;
	double longitud;

	UTM();
	UTM(double _lat, double _long);
	std::string toCSV();
	bool operator<(UTM& right);
	UTM operator-(UTM& right);
};


#endif // !UTM_H