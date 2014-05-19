/*
 * Buffer.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>     /* malloc, free, rand */
#include "Imprimible.h"
#include "CadenaDeBits.h"
#include "Constantes.h"
#include <cmath>

using namespace std;

class Buffer : public Imprimible{
public:
	Buffer(size_t tamanio, bool esCompresion);
	virtual ~Buffer();

	size_t tamanioBuffer;
	/**
	 * Indica si el buffer esta siendo usado para compresion o descompresion
	 * NOTA IMPORTANTE: Tanto el buffer de lectura como de escritura tienen
	 *  que estar en el mismo estado (los dos comprimiendo o descomprimiendo)
	 */
	bool esCompresion;
	iostream* file;

	virtual void crearStream(string archivo) = 0;
	virtual void cerrar() = 0;
protected:
	char* _buffer;
	size_t _index;
	size_t _tamanioCurrentBuffer;

	short bitsRestantesEnBuffer();
};

#endif /* BUFFER_H_ */
