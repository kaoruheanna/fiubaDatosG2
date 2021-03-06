/*
 * BufferLectura.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "BufferLectura.h"

BufferLectura::BufferLectura(size_t tamanio, bool esCompresion) : Buffer(tamanio, esCompresion){
	posFinDeArchivo = ((tamanio + 1)  * TAMANIO_BYTE); // Para que no llegue excepto que haya eof
}

BufferLectura::~BufferLectura() {
	this->cerrar();
	delete _file;
}

void BufferLectura::actualizarBuffer(){
	if(!_file->eof()){
		_file->read(_buffer,tamanioBuffer);
		_tamanioCurrentBuffer = _file->gcount();
		_index = 0;
		if((!esCompresion) && _file->eof()){
			if(_tamanioCurrentBuffer == 0){
				posFinDeArchivo = 0;
			} else {
				posFinDeArchivo = ((_tamanioCurrentBuffer * TAMANIO_BYTE) - 1);
				unsigned char marcaFinDeArchivo = 1;
				unsigned char aComparar = _buffer[_tamanioCurrentBuffer - 1];
				while(((aComparar & marcaFinDeArchivo) == 0) && (marcaFinDeArchivo != 0)){
					posFinDeArchivo --;
					marcaFinDeArchivo <<= 1;
				}
			}
		}
	}
}

void BufferLectura::leer(CadenaDeBits* cadena){
	short indexOnChar = _index % TAMANIO_BYTE;
	float bitsRestantesEnBuffer = (float)this->bitsRestantesEnBuffer();
	size_t tamanioEnBytes = cadena->tamanioEnBytes(indexOnChar);
	float bitsFaltantes =  -(bitsRestantesEnBuffer - cadena->tamanio);
	short bytesFaltantes = (bitsFaltantes > 0) ? ceil(bitsFaltantes/TAMANIO_BYTE) : 0;

	char* aux = new char [tamanioEnBytes];

	memcpy(aux,_buffer+(_index/TAMANIO_BYTE),tamanioEnBytes-bytesFaltantes);
	_index += cadena->tamanio;
	if(bytesFaltantes > 0){
		actualizarBuffer();
		memcpy(aux+(tamanioEnBytes-bytesFaltantes),_buffer,bytesFaltantes);
		_index += cadena->tamanio-bitsRestantesEnBuffer;
	}

	cadena->deserializar(aux,indexOnChar);
	delete[] aux;

	if((_index >= (_tamanioCurrentBuffer*TAMANIO_BYTE)) && !(bytesFaltantes > 0)){
		actualizarBuffer();
	}
}

bool BufferLectura::esFinDeArchivo(){
	return _file->eof() && ((_index >= (_tamanioCurrentBuffer*TAMANIO_BYTE)) || (_index >= posFinDeArchivo));
}

void BufferLectura::crearStream(string fileName){
	_file = new ifstream();
	_file->open(fileName.data(), ifstream::binary);
	actualizarBuffer();
}

void BufferLectura::cerrar(){
	_file->close();
}

bool BufferLectura::estaAbierto()
{
	return _file->is_open();
}

void BufferLectura::ImprimirEn(ostream& out) const{
}
