/*
 * Tabla.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "Tabla.h"
#include <math.h>

Tabla::Tabla() {
	this->cantidadBitsTabla = 1;
	this->lastCode = 0;
	this->tabla = new vector<string>;
}

Tabla::~Tabla() {
	delete this->tabla;
}
CadenaDeBits Tabla::agregarString(string cadena){
	CadenaDeBits toReturn(this->cantidadBitsTabla, this->tabla->size());
	this->tabla->push_back(cadena);
	this->lastCode++;
	int maxValor = (pow(2.0,(int)(this->cantidadBitsTabla)));
	if(this->lastCode >= maxValor){
		this->cantidadBitsTabla++;
	}
	return toReturn;
}
//CadenaDeBits Tabla::getBits(string cadena){
//	bool encontrado = false;
//	unsigned int currentIndex = 0;
//	while((!encontrado) && (currentIndex < this->tabla->size())){
//		encontrado = (cadena.compare(this->tabla->at(currentIndex)) == 0);
//		currentIndex ++;
//	}
//	return (*new CadenaDeBits(this->bitsTabla, currentIndex - 1));
//}

void Tabla::getBits(string cadena,CadenaDeBits* cadenaDeBits){
	bool encontrado = false;
	unsigned int currentIndex = 0;
	while((!encontrado) && (currentIndex < this->tabla->size())){
		encontrado = (cadena.compare(this->tabla->at(currentIndex)) == 0);
		currentIndex ++;
	}
	cadenaDeBits->tamanio = this->cantidadBitsTabla;
	cadenaDeBits->bits = currentIndex - 1;
}


string Tabla::getString(CadenaDeBits bits){
	if(Tabla::exists(bits)){
		return this->tabla->at(bits.bits);
	}
	return "";
}

int Tabla::getLastCode(){
	return this->lastCode;
}

bool Tabla::exists(string cadena){
	bool encontrado = false;
	unsigned int currentIndex = 0;
	while((!encontrado) && (currentIndex < this->tabla->size())){
		encontrado = (cadena.compare(this->tabla->at(currentIndex)) == 0);
		currentIndex ++;
	}
	return encontrado;
}
bool Tabla::exists(CadenaDeBits bits){
	return (bits.bits < lastCode);
}
void Tabla::limpiar(){

}
bool Tabla::hayQueLimpiar(){
	return false;
}
size_t Tabla::getCantidadBitsTabla(){
	return this->cantidadBitsTabla;
}
void Tabla::Imprimir(ostream& out){
	this->ImprimirEn(out);
}

void Tabla::ImprimirEn(ostream & out) const{
	out << "Tabla:" << endl;
	for (int currentIndex = 0; currentIndex < this->tabla->size(); currentIndex++) {
		out << currentIndex << " => " << this->tabla->at(currentIndex) << endl;
	}
	out << "Fin Tabla"<< endl;
}
