#include "UTM.h"

UTM::UTM() : latitud(0), longitud(0) {

}

UTM::UTM(double _lat, double _long) : latitud(_lat), longitud(_long) {
}

std::string UTM::toCSV(){
	return std::to_string(latitud)+", "+std::to_string(longitud) ;
}
