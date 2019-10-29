#include "EcoCityMoto.h"
#include "Cliente.h"
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

/**
	@brief Busca la moto m�s cercana a la posicion indicada
	@pre Debe haber alguna moto disponible (bloqueada, no rota y con bateria)
*/
Moto& EcoCityMoto::localizaMotoCercana(UTM posicion)
{
	
	int masCercana = -1;
	UTM relativa;
	for (int i = motos->getTamL() - 1; i >= 0; i--)
	{
		if ((*motos)[i].estatus.bloqueada && !((*motos)[i].estatus.roto) && !((*motos)[i].estatus.sinbateria)) {
			if (i = motos->getTamL() - 1) {
				masCercana = i;
				relativa = (*motos)[i].posicion - posicion;
				relativa.latitud = abs(relativa.latitud);
				relativa.longitud = abs(relativa.longitud);
			}
			else {
				UTM temp = (*motos)[i].posicion - posicion;
				temp.latitud = abs(temp.latitud);
				temp.longitud = abs(temp.longitud);
				if (temp < relativa) {
					masCercana = i;
					relativa = (*motos)[i].posicion - posicion;
					relativa.latitud = abs(relativa.latitud);
					relativa.longitud = abs(relativa.longitud);
				}
			}
		}
	}
	return (*motos)[masCercana];
	
}

Moto& EcoCityMoto::localizaMotoCercana(Cliente& cliente){
	Moto* masCercana = 0;
	 double menorDistancia = 99999.99;
	 double distancia;
	for (int i = 0; i < motos->getTamL(); i++){		
		distancia = (*motos)[i].distanciaCliente(cliente);
		if (menorDistancia > distancia) {
			masCercana = &(*motos)[i];
			menorDistancia = distancia;
		}
	}
	return *masCercana;
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
	Cliente encontrado;
	buscaCliente(dni, encontrado);
	encontrado.getItinerarios().insertaFinal(itinerario);
	return *this;
}

/**
	@brief Busca la moto cuya ID coincida con la indicada
*/
bool EcoCityMoto::buscaMoto(std::string id, Moto& motoEncontrada)
{
	for(int i = (*motos).getTamL() - 1; i >= 0; i--){
		if ((*motos)[i].id == id) {
			motoEncontrada = (*motos)[i];
			return true;
		}
	}
	return false;
}

/**
	@brief Busca el cliente cuyo DNI coicida con el indicado
*/
bool EcoCityMoto::buscaCliente(std::string& dni, Cliente& clienteEncontrado)
{
	Cliente buscado(dni);
	if (clientes->busca(buscado, clienteEncontrado)) {
		return true;
	}
	else {
		return false;
	}
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
	Cliente encontrado;
	buscaCliente(dni, encontrado);
	Iterador<Itinerario> it(encontrado.getItinerarios().iterador());
	
	while(pos > 0){
		it++;
		pos--;
	}
	encontrado.getItinerarios().borra(it);
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
