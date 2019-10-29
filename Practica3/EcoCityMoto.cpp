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
	@brief Busca la moto más cercana a la posicion indicada
	@pre Debe haber alguna moto disponible (bloqueada, no rota y con bateria)
*/
Moto& EcoCityMoto::localizaMotoCercana(UTM posicion)
{
	Moto* masCercana = 0;
	double menorDistancia = 99999, distancia;
	Cliente temp("", "", "", "", "", posicion.latitud, posicion.longitud);
	for (int i = motos->getTamL() - 1; i >= 0; i--) {
		distancia = (*motos)[i].distanciaCliente(temp);
		if (distancia < menorDistancia) {
			masCercana = &(*motos)[i];
			menorDistancia = distancia;
		}
	}
	return *masCercana;
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

void EcoCityMoto::desbloqueaMoto(Moto& m, Cliente& cli)
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

std::string& EcoCityMoto::verItinerario(Cliente& cliente){
	string *aux=new string;
	ListaDEnlazada<Itinerario> lista;
	try {
		lista = cliente.getItinerarios();
	}
	catch (std::logic_error& e) {
		throw std::logic_error("El cliente no tiene ningun itinerario");
	}
	Iterador<Itinerario> iterator = lista.iterador();
	for (unsigned int i = 0; i < lista.getTam(); i++) {
		try {
			*aux += (iterator.getNodo()->toCSV() + "\n");
			if (i+1<lista.getTam())
				iterator++;
		}
		catch (std::exception & e) {
			std::cerr << e.what();
		}
	}
	return *aux;
}

const std::string& EcoCityMoto::verCliente(std::string& dni){
	Cliente aux;
	if (buscaCliente(dni, aux)) {
		return aux.GetNombreCompleto();
	}
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

int EcoCityMoto::idItinerario()
{
	idUltimo++;
	return idUltimo - 1;
}
