/*
 * BufferLectura.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "BufferLectura.h"

BufferLectura::BufferLectura(size_t tamanio) : Buffer(tamanio){}

BufferLectura::~BufferLectura() {
	cerrar();
}

void BufferLectura::actualizarBuffer(){
	if(!_file->eof()){
		_file->read(_buffer,tamanioBuffer);
		_index += tamanioBuffer;
	}
}

void BufferLectura::leer(CadenaDeBits* cadena){
	cout << _buffer << endl;
	actualizarBuffer();
	/*
	int * p = new int;
	memcpy(p,_buffer,cadena->tamanio);
	cadena->bits = *p;
	delete[] p;*/
}

bool BufferLectura::esFinDeArchivo(){
	return _file->eof();
}

void BufferLectura::crearStream(string fileName){
	_file = new ifstream();
	_file->open(fileName.data(), ifstream::binary);
	actualizarBuffer();
}

void BufferLectura::cerrar(){
	_file->close();
}

void BufferLectura::ImprimirEn(ostream& out) const{
	out << "Buffer Tamanio: " << tamanioBuffer << endl;
}
