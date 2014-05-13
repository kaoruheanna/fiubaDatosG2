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
#include "math.h"
#include "Imprimible.h"

using namespace std;

class Compresor : public Imprimible{
    public:
		Compresor(){}
		virtual ~Compresor(){}
        virtual int comprimir(string &path) = 0;
        virtual int descomprimir(string &path) = 0;

    protected:
        //virtual bool agregarCadenaATabla(string cadena) = 0;
};

#endif /* COMPRESOR_H_ */
