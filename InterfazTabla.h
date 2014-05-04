/*
 * InterfazTabla.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef INTERFAZTABLA_H_
#define INTERFAZTABLA_H_

#include "CadenaDeBits.h"

class InterfazTabla {
	public:
        virtual CadenaDeBits getBits(string cadena) = 0;
        virtual string getString(CadenaDeBits bits) = 0;
        virtual CadenaDeBits agregarString(string cadena) = 0;
        virtual bool exists(string cadena) = 0;
        virtual bool exists(CadenaDeBits bits) = 0;
        virtual void limpiar() = 0;
        virtual bool hayQueLimpiar() = 0;
        virtual size_t getTamanioTabla() = 0;

        virtual ~InterfazTabla(){};
};


#endif /* INTERFAZTABLA_H_ */
