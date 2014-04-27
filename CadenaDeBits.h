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
	CadenaDeBits(size_t tamanio, int bits);
	virtual ~CadenaDeBits();
	size_t tamanio;
	bool esUno();
	//compare(&CadenaDeBits otraCadena);
	void serializar(void*);
	void deserializar(void*);

protected:
	virtual void ImprimirEn(ostream & out) const;
private:
	int bits;
};

#endif /* CADENADEBITS_H_ */
