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
	cout << "entra " << outputString << endl;

	unsigned long aux = 0;
	unsigned long auxBits = this->bits;
	cout << "bits " << bits << endl;
	for(unsigned int i = 0 ; i < this->tamanioEnBytes(index) ; i++){
		memcpy(&aux, &outputString[i], 1);
		aux <<= 8;
		cout << "aux: " << aux << " outputString[" << i << "] = " << outputString[i] << endl;
	}
	aux >>= 8;
	cout << "aux leido " << aux << " index " << index << endl;

	aux >>= ((this->tamanioEnBytes(index)*TAMANIO_BYTE)-index);
	aux <<= ((this->tamanioEnBytes(index)*TAMANIO_BYTE)-index);

	auxBits <<= ((this->tamanioEnBytes(index)*TAMANIO_BYTE)-tamanio);
	auxBits >>= index;
	aux |= auxBits;
	cout << "aux parseado " << aux << " auxBits " << auxBits << endl;

	for(unsigned int i = this->tamanioEnBytes(index) ; i > 0 ; i--){
		memcpy(&outputString[i-1],&aux,1);
		cout << "aux: " << aux << " outputString[" << i-1 << "] = " << outputString[i-1] << endl;
		aux >>= 8;
	}
	cout << "Tengo " << this->bits << " Sale " << outputString << endl;
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

	aux <<= offset + index;
	aux >>= offset;
	this->bits = aux;
	this->bits >>= shift;
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
