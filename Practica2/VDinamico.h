#ifndef VDINAMICO_H
#define VDINAMICO_H

#include <climits>
#include <stdexcept>


template<class T>
class VDinamico {
private:
	unsigned int tamL, tamF; //Tamaño lógico y tamaño fisico
	T* buffer;
	bool sorted = false;
	void aumentarTamF();
	void disminuirTamF();

public:
	VDinamico();
	VDinamico(unsigned int atamL);
	VDinamico(VDinamico<T>& orig);
	VDinamico(const VDinamico& orig, unsigned int inicio, unsigned int num);
	virtual ~VDinamico();
	int getTamF();
	int getTamL();
	VDinamico<T>& operator=(VDinamico<T>& asig);
	T& operator[](unsigned int pos);
	VDinamico<T>& insertarDato(T& dato, unsigned int pos = UINT_MAX);
	VDinamico<T>& eliminarDato(unsigned int pos = UINT_MAX);
	void ordenar();
	int busca(T& dato);
};

/**
 * @brief Constructor por defecto
 * @post Crea un nuevo vector dinamico de tamF = 1
 */
template<class T>
VDinamico<T>::VDinamico() : tamF(1), tamL(0) {
	buffer = new T[tamF];
}

/**
 * @brief Constructor parametrizado
 * @param atamL Tamanio logico del vector a crear
 * @post Crea un nuevo vector dinamico con capacidad para el numero de datos indicado
 */
template<class T>
VDinamico<T>::VDinamico(unsigned int atamL) : tamL(atamL), tamF(1) {
	while (tamF < tamL)
		tamF *= 2;
	buffer = new T[tamF];
}

/**
 * @brief Constructor por copia
 * @param orig Vector a copiar
 * @post Crea un nuevo vector dinamico igual al vector dado
 */
template<class T>
VDinamico<T>::VDinamico(VDinamico<T>& orig) : tamF(orig.tamF), tamL(orig.tamL) {
	buffer = new T[tamF];
	for (int i = 0; i < tamL; i++) {
		buffer[i] = orig[i];
	}
}

/**
 * @brief Constructor por copia parcial
 * @param orig Vector a copiar
 * @param inicio Comienzo del fragmento a copiar
 * @param num Numero de elementos a copiar
 * @post Crea un nuevo vector dinamico cuyo contenido es el fragmento indicado del vector dado
 */
template<class T>
VDinamico<T>::VDinamico(const VDinamico& orig, unsigned int inicio, unsigned int num) : tamL(num), tamF(orig.tamF) {
	//TODO: Excep. si el fragmento a copiar esta fuera de los limites del vector
	buffer = new T[tamF];
	for (int i = 0; i < num; i++) {
		buffer[i] = orig[inicio++];
	}
}

/**
 * @brief Destructor
 */
template<class T>
VDinamico<T>::~VDinamico() {
	delete[] buffer;
}

/**
 * @brief Getter del atributo TamF
 * @return TamF
 */
template<class T>
int VDinamico<T>::getTamF() {
	return tamF;
}

/**
 * @brief Getter del atributo TamL
 * @return TamL
 */
template<class T>
int VDinamico<T>::getTamL() {
	return tamL;
}

/**
 * @brief Operador de asignacion
 * @param asig Vector a copiar
 * @post Recrea el vector dinamico igual al vector dado
 * @return Propio vector para permitir operaciones en cascada
 */
template<class T>
VDinamico<T>& VDinamico<T>::operator=(VDinamico<T>& asig) {
	if (this = &asig) {
		return *this;
	}
	else {
		delete[] buffer;
		tamF = asig.tamF;
		tamL = asig.tamL;
		buffer = new T[tamF];
		for (int i = 0; i < tamL; i++) {
			buffer[i] = asig[i];
		}
		return *this;
	}
}

/**
 * @brief Operador []
 * @param pos Posicion a acceder en el vector
 * @return Valor almacenado en la posicion indicada
 */
template<class T>
T& VDinamico<T>::operator[](unsigned int pos) {
	if (pos >= tamF) {
		throw std::out_of_range("Posicion no valida");
	}
	else
		return buffer[pos];
}

/**
 * @brief Inserta un dato en el vector
 * @param dato Dato a insertar
 * @param pos Posicion donde colocar el dato
 * @post Inserta el dato en la posicion indicada, desplazando el resto de datos
 */
template<class T>
VDinamico<T>& VDinamico<T>::insertarDato(T& dato, unsigned int pos) {
	if ((pos < 0 || pos >= tamF) && pos != UINT_MAX) {
		throw std::out_of_range("Posicion no valida");
	}
	else {
		if (tamL == tamF) {
			aumentarTamF();
		}
		if (pos == UINT_MAX) {
			buffer[tamL++] = dato;
		}
		else {
			tamL++;
			for (unsigned int i = tamL; i > pos; i--) {
				buffer[i] = buffer[i - 1];
			}
			buffer[pos] = dato;
		}
	}
	sorted = false;
	return *this;
}

/**
 * @brief Elimina un dato del vector
 * @param pos Posicion del dato a borrar
 * @post Elimina el dato indicado y reorganiza los elementos del vector
 */
template<class T>
VDinamico<T>& VDinamico<T>::eliminarDato(unsigned int pos) {
	if (this->tamL == 0) {
		throw(std::out_of_range("[VDinamico<T>::eliminarDato] No hay datos en el vector"));
	}
	if ((pos < 0 || pos >= tamF) && pos != UINT_MAX) {
		throw std::out_of_range("Posicion no valida");
	}
	else {
		if (pos != UINT_MAX) {
			for (int i = pos; i + 1 < tamL; i++) {
				buffer[i] = buffer[i + 1];
			}
		}

		tamL--;

		if (tamL * 3 <= tamF)
			disminuirTamF();
	}
	sorted = false;
	return *this;
}

/**
 * @brief Crea un nuevo buffer con el doble de tamaño físico, copia todos los elementos del buffer anterior y borra el anterior buffer
 * @post  El anterior buffer queda eliminado
 */
template <class T>
void VDinamico<T>::aumentarTamF() {
	T* NuevoBuffer = new T[tamF *= 2];
	for (unsigned int i = 0; i < tamL; i++) {
		NuevoBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = NuevoBuffer;
}

/**
 * @brief Crea un nuevo buffer con la mitad de tamaño físico, copia todos los elementos del buffer anterior y borra el anterior buffer
 * @post  El anterior buffer queda eliminado
 */
template <class T>
void VDinamico<T>::disminuirTamF() {
	T* NuevoBuffer = new T[tamF /= 2];
	for (int i = 0; i < tamF; i++) {
		NuevoBuffer[i] = buffer[i];
	}
	delete[] buffer;
	buffer = NuevoBuffer;
}

/**
 * @brief Ordena el contenido del vector
 * @pre La clase T debe tener la función menorQue() definida
 * @post Ordena crecientemente los datos almacenados en el buffer
 */
template<class T>
void VDinamico<T>::ordenar() {
	for (int i = 0; i < tamL - 1; i++) {
		for (int j = i + 1; j < tamL; j++) {
			if (!(buffer[i].menorQue(buffer[j]))) {
				T temp = buffer[i];
				buffer[i] = buffer[j];
				buffer[j] = temp;
			}
		}
	}
	sorted = true;
}

/**
 * @brief Busca el dato en el vector dinámico utilizando la busqueda dicotómica
 * @param dato: Dato a buscar
 * @prev El vector dinámico debe de estar ordenado (Si no, se ordenará antes de comenzar la busqueda)
 * @return La posición del dato si es encontrado o -1 si no se encuentra
 */
template<class T>
int VDinamico<T>::busca(T& dato) {
	if (!sorted) {
		VDinamico<T>::ordenar();
	}
	int inicio = 0, final = tamL - 1, encontrado = 0;

	while (inicio <= final) {
		encontrado = (inicio + final) / 2;

		if (buffer[encontrado] < dato) {
			inicio = encontrado + 1;
		}
		else if (dato < buffer[encontrado]) {
			final = encontrado - 1;
		}
		else {
			return encontrado;
		}
	}
	return -1;
}
#endif /* VDINAMICO_H */
