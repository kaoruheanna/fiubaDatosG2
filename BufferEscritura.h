/*
 * BufferEscritura.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef BUFFERESCRITURA_H_
#define BUFFERESCRITURA_H_

#include "Buffer.h"

class BufferEscritura: public Buffer {
public:
	BufferEscritura(size_t tamanio);
	virtual ~BufferEscritura();

	void escribir(const CadenaDeBits* cadena);

};

#endif /* BUFFERESCRITURA_H_ */
