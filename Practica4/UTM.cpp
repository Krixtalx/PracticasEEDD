#include "UTM.h"

UTM::UTM() : latitud(0), longitud(0) {

}

UTM::UTM(double _lat, double _long) : latitud(_lat), longitud(_long) {
}

std::string UTM::toCSV(){
	return std::to_string(latitud)+":"+std::to_string(longitud) ;
}

bool UTM::operator<(UTM& right)
{
	if (latitud < right.latitud && longitud < right.longitud)
		return true;
	return false;
}

UTM UTM::operator-(UTM& right)
{
	UTM resta;
	resta.latitud = latitud - right.latitud;
	resta.longitud = longitud - right.longitud;
	return resta;
}
