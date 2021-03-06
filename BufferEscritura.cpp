/*
 * BufferEscritura.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "BufferEscritura.h"

using namespace std;

BufferEscritura::BufferEscritura(size_t tamanio, bool esCompresion) : Buffer(tamanio, esCompresion){
}

BufferEscritura::~BufferEscritura() {
	this->cerrar();
	delete _file;
}

void BufferEscritura::escribir(const CadenaDeBits* cadena){
	//Escribir en el buffer
	short indexOnChar = _index % TAMANIO_BYTE;
	float bitsRestantesEnBuffer = (float)this->bitsRestantesEnBuffer();
	size_t tamanioEnBytes = cadena->tamanioEnBytes(indexOnChar);
	float bitsFaltantes =  -(bitsRestantesEnBuffer - cadena->tamanio);
	short bytesFaltantes = (bitsFaltantes > 0) ? ceil(bitsFaltantes/TAMANIO_BYTE) : 0;

	char* aux = new char [tamanioEnBytes];
	memcpy(aux,_buffer+(_index/TAMANIO_BYTE),tamanioEnBytes-bytesFaltantes);
	cadena->serializar(aux,indexOnChar);

	memcpy(_buffer+(_index/TAMANIO_BYTE),aux,tamanioEnBytes-bytesFaltantes);
	_index += cadena->tamanio;

	if((bytesFaltantes > 0) || ((_index/(long) TAMANIO_BYTE) >= _tamanioCurrentBuffer)){
		this->guardarEnDisco();
		if(bytesFaltantes > 0){
			memcpy(_buffer,aux+(tamanioEnBytes-bytesFaltantes),bytesFaltantes);
			_index += cadena->tamanio-bitsRestantesEnBuffer;
		}
	}

	delete[] aux;
}

string hola;
void BufferEscritura::crearStream(string fileName){
	_file = new ofstream();
	_file->open(fileName.data(), ofstream::binary);
	hola = fileName;
}

void BufferEscritura::cerrar(){
	this->agregarFinDeArchivo();
	this->guardarEnDisco();
	_file->close();
}

void BufferEscritura::agregarFinDeArchivo(){
	if(esCompresion){
		unsigned char finDeArchivo = 1;
		int tamanioDeFinDeArchivo = TAMANIO_BYTE - (_index % TAMANIO_BYTE);
		if(tamanioDeFinDeArchivo < 1){
			tamanioDeFinDeArchivo = TAMANIO_BYTE;
		}
		finDeArchivo <<= (tamanioDeFinDeArchivo - 1);
		CadenaDeBits bitsDeFinDeArchivo(tamanioDeFinDeArchivo, (int) finDeArchivo);
		escribir(&bitsDeFinDeArchivo);
	}
}

void BufferEscritura::guardarEnDisco(){
	float tamanioElegido = 0;
	if(_index < (tamanioBuffer * TAMANIO_BYTE)){
		tamanioElegido = ceil(((float) _index)/TAMANIO_BYTE);
	} else {
		tamanioElegido = tamanioBuffer;
	}

	_file->write(_buffer,tamanioElegido);
	_index = 0;
}



void BufferEscritura::ImprimirEn(ostream& out) const{
}
