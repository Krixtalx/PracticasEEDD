#pragma once
#ifndef MOTO_H
#define MOTO_H

#include <string>
#include "UTM.h"

struct Estado {
	bool bloqueada=false;
	bool activa=false;
	bool sinbateria=false;
	bool roto=false;
};

class Moto{
private:
	std::string id;
	UTM posicion;
	Estado estatus;
};

#endif // !MOTO_H