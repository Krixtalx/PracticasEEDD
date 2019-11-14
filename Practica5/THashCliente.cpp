#include "THashCliente.h"

unsigned long djb2(std::string& palabra){
	unsigned long hash = 5381;
		int c;

        for(int i=0 ; i<palabra.length() ; i++){
			c=(unsigned long)palabra[i];
            hash = ((hash << 5) + hash) + c; 
			}

        return hash;
}

bool THashCliente::insertar(unsigned long clave, string& dni, Cliente& cliente)
{

	return false;
}
