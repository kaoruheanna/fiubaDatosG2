/*
 * Buffer.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "Buffer.h"

using namespace std;

Buffer::Buffer(size_t tamanio): tamanioBuffer(tamanio) {
	_buffer = new char [tamanio];
	_index = 0;
}

Buffer::~Buffer() {
	delete[] _buffer;
}

short Buffer::bitsRestantesEnBuffer(){
	return (_tamanioCurrentBuffer*TAMANIO_BYTE) - _index;
}

