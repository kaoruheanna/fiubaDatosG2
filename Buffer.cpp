/*
 * Buffer.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "Buffer.h"

using namespace std;

Buffer::Buffer(size_t tamanio, bool esCompresion): tamanioBuffer(tamanio), esCompresion(esCompresion) {
	_tamanioCurrentBuffer = tamanio;
	_buffer = new char [tamanio];
	_index = 0;
}

Buffer::~Buffer() {
	delete[] _buffer;
}

size_t Buffer::bitsRestantesEnBuffer(){
	return (_tamanioCurrentBuffer*TAMANIO_BYTE) - _index;
}

