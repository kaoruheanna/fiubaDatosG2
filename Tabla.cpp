/*
 * Tabla.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "Tabla.h"

Tabla::Tabla() {
	this->bitsTabla = 1;
	this->lastCode = 0;
	this->tabla = new vector<string>;
}

Tabla::~Tabla() {
	delete this->tabla;
}
CadenaDeBits Tabla::agregarString(string cadena){
	CadenaDeBits toReturn(this->bitsTabla, this->tabla->size());
	this->tabla->push_back(cadena);
	this->lastCode++;
	if(this->lastCode >= (this->bitsTabla * 2)){
		this->bitsTabla++;
	}
	return toReturn;
}
CadenaDeBits Tabla::getBits(string cadena){
	bool encontrado = false;
	unsigned int currentIndex = 0;
	while((!encontrado) && (currentIndex < this->tabla->size())){
		encontrado = (cadena.compare(this->tabla->at(currentIndex)) == 0);
		currentIndex ++;
	}
	return (*new CadenaDeBits(this->bitsTabla, currentIndex - 1));
}
string Tabla::getString(CadenaDeBits bits){
	if(Tabla::exists(bits)){
		return this->tabla->at(bits.bits);
	}
	return "";
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
size_t Tabla::getTamanioTabla(){
	return (this->bitsTabla * 2);
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
