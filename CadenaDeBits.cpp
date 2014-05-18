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

using namespace std;

CadenaDeBits::CadenaDeBits(size_t tamanio, int bits) {
	// TODO Auto-generated constructor stub
	this->bits = bits;
	this->tamanio = tamanio;
}

CadenaDeBits::~CadenaDeBits() {
	// TODO Auto-generated destructor stub
}

void CadenaDeBits::serializar(void* output, short index){
	sprintf((char*)output,"%d",this->bits);
}

void CadenaDeBits::deserializar(void* input, short index){
	char *inputString = (char*)input;

	unsigned long aux = ntohs(*reinterpret_cast<unsigned long*>(inputString));
	short offset = (sizeof(long)-this->tamanioEnBytes(index))*TAMANIO_BYTE;
	short shift = (this->tamanioEnBytes(index) * TAMANIO_BYTE) - this->tamanio;

	aux <<= offset + index;
	aux >>= offset;
	this->bits = aux;
	this->bits >>= shift;
	cout << "offset " << offset << " index shift " << index << " shift " << shift << "Entra " << inputString << " Sale " << this->bits << endl;
}

size_t CadenaDeBits::tamanioEnBytes(short index){
	float aux = (float)this->tamanio+index;
	return ceil(aux/TAMANIO_BYTE);
}

void CadenaDeBits::ImprimirEn(ostream & out) const{
	out << "Cadena de Bits";
}
