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
        virtual CadenaDeBits getBits(string cadena) const = 0;
        virtual string getString(CadenaDeBits bits) const = 0;
        virtual bool exists(string cadena) const = 0;
        virtual bool exists(CadenaDeBits bits)const = 0;
        virtual void limpiar() const = 0;
        virtual bool hayQueLimpiar() const = 0;
        virtual size_t getTamanioTabla() const = 0;

        virtual ~InterfazTabla(){};
};


#endif /* INTERFAZTABLA_H_ */
