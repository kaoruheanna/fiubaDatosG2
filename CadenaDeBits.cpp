/*
 * CadenaDeBits.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "CadenaDeBits.h"
#include <cstdio>
#include <stdlib.h>
#include "Constantes.h"
#include <cmath>
#include <arpa/inet.h>
#include <string.h> // memcpy

using namespace std;

CadenaDeBits::CadenaDeBits(size_t tamanio, int bits) {
	// TODO Auto-generated constructor stub
	this->bits = bits;
	this->tamanio = tamanio;
}

CadenaDeBits::~CadenaDeBits() {
	// TODO Auto-generated destructor stub
}

void CadenaDeBits::serializar(void* output, short index) const{
	char *outputString = (char*)output;
	cout << "entra " << output;

	sprintf((char*)output,"%d",this->bits);

	cout << "Tengo " << this->bits << " Sale " << output << endl;
}

void CadenaDeBits::deserializar(void* input, short index){
	char *inputString = (char*)input;

	//unsigned long aux = ntohs(*reinterpret_cast<unsigned long*>(inputString));
	unsigned long aux = 0;
	memcpy(&aux, input, this->tamanioEnBytes(index));

	short offset = (sizeof(long)-this->tamanioEnBytes(index))*TAMANIO_BYTE;
	short shift = (this->tamanioEnBytes(index) * TAMANIO_BYTE) - this->tamanio;
	cout << "aux antes " << aux << endl;

	aux <<= offset + index;
	aux >>= offset;
	this->bits = aux;
	this->bits >>= shift;
	cout << "aux " << aux <<  " offset " << offset << " index shift " << index << " shift " << shift << "Entra " << inputString << " Sale " << this->bits << endl;
}

size_t CadenaDeBits::tamanioEnBytes(short index) const{
	float aux = (float)this->tamanio+index;
	return ceil(aux/TAMANIO_BYTE);
}

void CadenaDeBits::ImprimirEn(ostream & out) const{
	out << "Cadena de Bits";
}
