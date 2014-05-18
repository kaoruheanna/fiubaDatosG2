/*
 * BufferEscritura.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "BufferEscritura.h"

using namespace std;

BufferEscritura::BufferEscritura(size_t tamanio) : Buffer(tamanio){
}

BufferEscritura::~BufferEscritura() {
	this->cerrar();
}

void BufferEscritura::escribir(const CadenaDeBits* cadena){
	//Escribir en el buffer
	short indexOnChar = _index % TAMANIO_BYTE;
	float bitsRestantesEnBuffer = (float)this->bitsRestantesEnBuffer();
	size_t tamanioEnBytes = cadena->tamanioEnBytes(indexOnChar);
	float bitsFaltantes =  -(bitsRestantesEnBuffer - cadena->tamanio);
	short bytesFaltantes = (bitsFaltantes > 0) ? ceil(bitsFaltantes/TAMANIO_BYTE) : 0;

	char* aux = new char [tamanioEnBytes];
	cadena->serializar(aux,indexOnChar);

	memcpy(_buffer+(_index/TAMANIO_BYTE),aux,tamanioEnBytes-bytesFaltantes);
	_index += cadena->tamanio;

	if(bytesFaltantes > 0){
		this->guardarEnDisco();
		memcpy(_buffer,aux+(tamanioEnBytes-bytesFaltantes),bytesFaltantes);
		_index = cadena->tamanio-bitsRestantesEnBuffer;
	}

	delete[] aux;
}

void BufferEscritura::crearStream(string fileName){
	_file = new ofstream();
	_file->open(fileName.data(), ofstream::binary);
}

void BufferEscritura::cerrar(){
	this->agregarFinDeArchivo();
	this->guardarEnDisco();
	_file->close();
}

void BufferEscritura::agregarFinDeArchivo(){
	//Poner bits de fin de archivo
}

void BufferEscritura::guardarEnDisco(){
	_file->write(_buffer,tamanioBuffer);
}



void BufferEscritura::ImprimirEn(ostream& out) const{
	out << "Buffer Escritura Tamanio: " << tamanioBuffer << endl;
}
