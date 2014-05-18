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

CadenaDeBits::CadenaDeBits() {
	this->bits = 0;
	this->tamanio = TAMANIO_BYTE;
}

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
//	cout << "entra " << output;

	sprintf((char*)output,"%d",this->bits);

	cout << "Tengo " << this->bits << " Sale " << output << endl;
}

void CadenaDeBits::deserializar(void* input, short index){
	char *inputString = (char*)input;

	unsigned long aux = 0;

	for(unsigned int i = 0 ; i<this->tamanioEnBytes(index) ; i++){
		memcpy(&aux, &inputString[i], 1);
		aux <<= 8;
	}
	aux >>= 8;

	short offset = (sizeof(long)-this->tamanioEnBytes(index))*TAMANIO_BYTE;
	short shift = (this->tamanioEnBytes(index) * TAMANIO_BYTE) - this->tamanio;
//	cout << "aux antes " << aux  << "char pos 0 " << inputString[0] << endl;

	aux <<= offset + index;
	aux >>= offset;
	this->bits = aux;
	this->bits >>= shift;
//	cout << "aux " << aux <<  " offset " << offset << " index shift " << index << " shift " << shift << "Entra " << inputString << " Sale " << this->bits << endl;
}

size_t CadenaDeBits::tamanioEnBytes(short index) const{
	float aux = (float)this->tamanio+index;
	return ceil(aux/TAMANIO_BYTE);
}

char CadenaDeBits::getAsChar() const{
	return (char)this->bits;
}
void CadenaDeBits::ImprimirEn(ostream & out) const{
	out << "Cadena de Bits";
}
