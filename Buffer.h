/*
 * Buffer.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <iostream>

#include <string>
#include "Imprimible.h"
#include "CadenaDeBits.h"

using namespace std;

class Buffer : public Imprimible{
public:
	Buffer(string archivo, size_t tamanio);
	virtual ~Buffer();

	size_t tamanioBuffer;
	iostream* file;

	virtual bool crearStream(string archivo) const = 0;
	virtual void cerrar() const = 0;
};

#endif /* BUFFER_H_ */
