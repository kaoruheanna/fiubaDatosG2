/*
 * CadenaDeBits.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef CADENADEBITS_H_
#define CADENADEBITS_H_

#include "Imprimible.h"

class CadenaDeBits: public Imprimible {
public:
	CadenaDeBits(); //lo inicializa para char
	CadenaDeBits(size_t tamanio, int bits);
	virtual ~CadenaDeBits();
	size_t tamanio;
	bool esUno();
	//compare(&CadenaDeBits otraCadena);
	void serializar(void* output, short index) const;
	void deserializar(void* input, short index);
	size_t  tamanioEnBytes(short index) const;
	char getAsChar() const;

	unsigned int bits;

protected:
	virtual void ImprimirEn(ostream & out) const;
};

#endif /* CADENADEBITS_H_ */
