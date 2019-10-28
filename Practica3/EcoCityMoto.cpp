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

/**
	@brief Inserta una moto en el vector de motos
*/
EcoCityMoto& EcoCityMoto::insertaMoto(Moto& moto)
{
	motos->insertarDato(moto);
	return *this;
}

/**
	@brief Inserta un cliente en el arbol de clientes
*/
EcoCityMoto& EcoCityMoto::insertaCliente(Cliente& cliente)
{
	clientes->inserta(cliente);
	return *this;
}

/**
	@brief Inserta un itinerario a la lista del cliente indicado
*/
EcoCityMoto& EcoCityMoto::insertaItinerario(Itinerario& itinerario, std::string dni)
{
	buscaCliente(dni).getItinerarios().insertaFinal(itinerario);
	return *this;
}

/**
	@brief Busca la moto cuya ID coincida con la indicada
*/
Moto& EcoCityMoto::buscaMoto(std::string id)
{
	for(int i = (*motos).getTamL() - 1; i >= 0; i--){
		if ((*motos)[i].id == id)
			return (*motos)[i];
	}
	//TODO: hacer algo si no esta
}

/**
	@brief Busca el cliente cuyo DNI coicida con el indicado
*/
Cliente& EcoCityMoto::buscaCliente(std::string dni)
{
	Cliente encontrado;
	Cliente buscado(dni);
	if (clientes->busca(buscado, encontrado))
		return encontrado;
	//TODO: algo si no esta
}

/**
	@brief Elimina la moto de la posicion indicada
*/
EcoCityMoto& EcoCityMoto::borraMoto(int pos)
{
	motos->eliminarDato(pos);
	return *this;
}
/**
	@brief Elimina el itinerario de la posicion indicada del cliente
*/
EcoCityMoto& EcoCityMoto::borraItinerario(int pos, std::string dni)
{
	Iterador<Itinerario> it;
	it = buscaCliente(dni).getItinerarios().iterador();
	while(pos > 0){
		it++;
		pos--;
	}
	buscaCliente(dni).getItinerarios().borra(it);
	return *this;
}

/**
	@brief Devuelve la altura del arbol de clientes
*/
unsigned int EcoCityMoto::getAlturaAVL()
{
	return clientes->altura();
}

/**
	@brief Muestra el arbol de clientes en inorden
*/
EcoCityMoto& EcoCityMoto::recorreAVLInorden()
{
	clientes->recorreInorden();
	return *this;
}

/**
	@brief Muestra el arbol de clientes
*/
EcoCityMoto& EcoCityMoto::verArbolCliente()
{
	clientes->verArbol();
	return *this;
}
