/*
 * BufferLectura.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "BufferLectura.h"
#include "Constantes.h"
#include <cmath>

BufferLectura::BufferLectura(size_t tamanio) : Buffer(tamanio){}

BufferLectura::~BufferLectura() {
	cerrar();
}

void BufferLectura::actualizarBuffer(){
	if(!_file->eof()){
		_file->read(_buffer,tamanioBuffer);
		_tamanioCurrentBuffer = _file->gcount();
		_index = 0;
	}
}

void BufferLectura::leer(CadenaDeBits* cadena){
	cout << _buffer << endl;

	cout << "ingreso con index " << (_index/TAMANIO_BYTE) << endl;
	short indexOnChar = _index % TAMANIO_BYTE;
	short bitsRestantesEnBuffer = this->bitsRestantesEnBuffer();
	size_t tamanioEnBytes = cadena->tamanioEnBytes(indexOnChar);
	float bitsFaltantes =  (float)-(bitsRestantesEnBuffer - cadena->tamanio);
	short bytesFaltantes = (bitsFaltantes > 0) ? ceil(bitsFaltantes/TAMANIO_BYTE) : 0;

	cout << "bitsfaltantes"<<bitsFaltantes <<  " bitsrestantes " << bitsRestantesEnBuffer << " bytesFaltantes" << bytesFaltantes << "Tamanio " << cadena->tamanio << " chars " << tamanioEnBytes << endl;
	char* aux = new char [tamanioEnBytes];
	memcpy(aux,_buffer+(_index/TAMANIO_BYTE),tamanioEnBytes-bytesFaltantes);

	if(bytesFaltantes > 0){
		actualizarBuffer();
		memcpy(aux+(tamanioEnBytes-bytesFaltantes),_buffer,bytesFaltantes);
	}

	cadena->deserializar(aux,indexOnChar);
	delete[] aux;

	_index += (bytesFaltantes > 0) ? cadena->tamanio-bitsRestantesEnBuffer : cadena->tamanio;
	cout << "index " << _index << " tamanio current buffer " << _tamanioCurrentBuffer << endl;

	if((_index >= (_tamanioCurrentBuffer*TAMANIO_BYTE)) && !(bytesFaltantes > 0)){
		actualizarBuffer();
	}

}

bool BufferLectura::esFinDeArchivo(){
	return _file->eof() && (_index>=(_tamanioCurrentBuffer*8));
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
