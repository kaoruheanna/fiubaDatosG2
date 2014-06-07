/*
 * Compresor.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef COMPRESOR_H_
#define COMPRESOR_H_
#include <string>
#include <iostream>
#include "Imprimible.h"

using namespace std;

class Compresor : public Imprimible{
    public:
		Compresor(){}
		virtual ~Compresor(){}
        virtual int comprimir(string archivoEntrada, string archivoSalida) = 0;
        virtual int descomprimir(string archivoEntrada, string archivoSalida) = 0;
};

#endif /* COMPRESOR_H_ */
