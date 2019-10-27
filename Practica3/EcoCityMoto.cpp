#include "EcoCityMoto.h"

/**
	@brief Constructor por defecto
*/
EcoCityMoto::EcoCityMoto()
{
	motos = new VDinamico<Moto>;
	clientes = new AVL<Cliente>;
}

/**
	@brief Constructor parametrizado
	@param _idUltimo Id del ultimo itinerario
*/
EcoCityMoto::EcoCityMoto(unsigned _idUltimo) : idUltimo(_idUltimo)
{
	motos = new VDinamico<Moto>;
	clientes = new AVL<Cliente>;
}

/**
	@brief Destructor
*/
EcoCityMoto::~EcoCityMoto()
{
	delete motos;
	delete clientes;
}

/**
	@brief Constructor de copia
	@param orig Objeto del que copiar
*/
EcoCityMoto::EcoCityMoto(EcoCityMoto& orig) : idUltimo(orig.idUltimo)
{
	motos = new VDinamico<Moto>(*(orig.motos));
	clientes = new AVL<Cliente>(*(orig.clientes));
}

/**
	@brief Operador de asignacion
	@param right Objeto cuyos atributos se van a asignar
*/
EcoCityMoto& EcoCityMoto::operator=(EcoCityMoto& right)
{
	idUltimo = right.idUltimo;
	motos = right.motos;
	clientes = right.clientes;
	return *this;
}


Moto EcoCityMoto::localizaMotoCercana(UTM posicion)
{
	Moto masCercana;
	UTM temp, temp2;
	for (int i = motos->getTamL(); i > 1; i--)
	{
		if ((*motos)[i].estatus.bloqueada && !((*motos)[i].estatus.roto) && !((*motos)[i].estatus.sinbateria)) {
			if ((*motos)[i - 1].estatus.bloqueada && !((*motos)[i - 1].estatus.roto) && !((*motos)[i - 1].estatus.sinbateria)) {
				temp.latitud = abs((*motos)[i].posicion.latitud - posicion.latitud);
				temp.longitud = abs((*motos)[i].posicion.longitud - posicion.longitud);
				temp2.latitud = abs((*motos)[i-1].posicion.latitud - posicion.latitud);
				temp2.longitud = abs((*motos)[i-1].posicion.longitud - posicion.longitud);
				if (temp < temp2)
					masCercana = (*motos)[i];
				else
					masCercana = (*motos)[i - 1];
			}
			else
				masCercana = (*motos)[i];
		}
	}
	return masCercana;
}

void EcoCityMoto::desbloqueaMoto(Moto m, Cliente cli)
{
	m.seActiva(cli);
}
