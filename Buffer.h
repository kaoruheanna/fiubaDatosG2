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
	Buffer(size_t tamanio);
	virtual ~Buffer();

	size_t tamanioBuffer;
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
