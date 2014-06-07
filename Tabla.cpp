/*
 * Tabla.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "Tabla.h"
#include <math.h>
#include "Constantes.h"

Tabla::Tabla() {
	this->cantidadBitsTabla = 2;
	// La posicion 0 es el codigo de limpieza
	this->lastCode = 1;
	this->tabla = new vector<string>;
	this->mapa = new map<string,int>();
}

Tabla::~Tabla() {
	delete this->tabla;
	delete this->mapa;
}
CadenaDeBits Tabla::agregarString(string cadena){
	CadenaDeBits toReturn(this->cantidadBitsTabla, this->tabla->size());
	(*this->mapa)[cadena] = (int)this->tabla->size();
	this->tabla->push_back(cadena);
	this->lastCode++;
	int maxValor = (pow(2.0,(int)(this->cantidadBitsTabla)));
	if(this->lastCode >= maxValor){
		this->cantidadBitsTabla++;
	}
	return toReturn;
}

void Tabla::getBits(string cadena,CadenaDeBits* cadenaDeBits){
	cadenaDeBits->tamanio = this->cantidadBitsTabla;
	cadenaDeBits->bits = this->mapa->at(cadena) + 1;
}


string Tabla::getString(CadenaDeBits bits){
	if(Tabla::exists(bits)){
		return this->tabla->at(bits.bits - 1);
	}
	return "";
}

int Tabla::getLastCode(){
	return this->lastCode;
}

bool Tabla::exists(string cadena){
	return (this->mapa->find(cadena) != this->mapa->end());
}

bool Tabla::exists(CadenaDeBits bits){
	return (bits.bits < lastCode);
}

void Tabla::limpiar(){
	this->borrarTodo();
}

bool Tabla::hayQueLimpiar(){
	return (this->cantidadBitsTabla >= (TAMANIO_MAX_BITS_TABLA + 1));
}

size_t Tabla::getCantidadBitsTabla(){
	return this->cantidadBitsTabla;
}

void Tabla::Imprimir(ostream& out){
	this->ImprimirEn(out);
}

void Tabla::ImprimirEn(ostream & out) const{
	out << "Tabla:" << endl;
	for (unsigned int currentIndex = 0; currentIndex < this->tabla->size(); currentIndex++) {
		out << currentIndex << " => " << this->tabla->at(currentIndex) << endl;
	}
	out << "Fin Tabla"<< endl;
}

void Tabla::borrarTodo(){
	this->tabla->clear();
	this->mapa->clear();
	this->cantidadBitsTabla = 2;
	// La posicion 0 es el codigo de limpieza
	this->lastCode = 1;
}

bool Tabla::esCodigoLimpieza(CadenaDeBits *cadena){
	return (cadena->bits == 0);
}

void Tabla::obtenerCodigoLimpieza(CadenaDeBits *cadena){
	cadena->bits = 0;
	cadena->tamanio = this->cantidadBitsTabla;
}
