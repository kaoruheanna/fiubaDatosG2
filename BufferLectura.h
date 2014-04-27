/*
 * BufferLectura.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef BUFFERLECTURA_H_
#define BUFFERLECTURA_H_

#include "Buffer.h"

class BufferLectura : public Buffer {
public:
	BufferLectura(string archivo, size_t tamanio);
	virtual ~BufferLectura();

	void leer(CadenaDeBits* cadena);
	bool esFinDeArchivo();
};

#endif /* BUFFERLECTURA_H_ */
