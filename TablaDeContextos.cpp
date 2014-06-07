/*
 * TablaDeContextos.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "TablaDeContextos.h"

TablaDeContextos::TablaDeContextos() {
	char c;
	for (int codigo=0;codigo<256;codigo++){
		c = (char)codigo;
		this->mapaDeContextos[c] = new Tabla();
	}
	this->contexto = NULL;
	this->contextoSeteado = false;
}

TablaDeContextos::~TablaDeContextos() {
	char c;
	for (int codigo=0;codigo<256;codigo++){
		c = (char)codigo;
		delete (this->mapaDeContextos[c]);
	}
}

void TablaDeContextos::setContexto(char contexto){
	this->contexto = contexto;
	this->contextoSeteado = true;

}

bool TablaDeContextos::exists(string cadena){
	if (!this->tengoContexto()){
		return false;
	}
	Tabla* tabla = this->getTablaActual();
	return tabla->exists(cadena);
}

bool TablaDeContextos::exists(CadenaDeBits bits){
	if (!this->tengoContexto()){
		cout << "quiero agregar y no tengo contexto" << endl;
		throw "contexto vacio";
	}
	Tabla* tabla = this->getTablaActual();
	return tabla->exists(bits);
}

CadenaDeBits TablaDeContextos::agregarString(string cadena){
	if (!this->tengoContexto()){
		cout << "quiero agregar y no tengo contexto" << endl;
		throw "contexto vacio";
	}
	Tabla* tabla = this->getTablaActual();
	return tabla->agregarString(cadena);
}

void TablaDeContextos::getBits(string cadena,CadenaDeBits* cadenaDeBits){
	if (!this->tengoContexto()){
		cout << "quiero obtener el codigo y no tengo contexto" << endl;
		throw "contexto vacio";
	}
	Tabla* tabla = this->getTablaActual();
	tabla->getBits(cadena,cadenaDeBits);
}

bool TablaDeContextos::tengoContexto(){
	return this->contextoSeteado;
}

Tabla* TablaDeContextos::getTablaActual(){
	if (!this->tengoContexto()){
		return NULL;
	}
	return this->mapaDeContextos[this->contexto];
}

string TablaDeContextos::getString(CadenaDeBits bits){
	if (!this->tengoContexto()){
		cout << "quiero obtener el codigo y no tengo contexto" << endl;
		throw "contexto vacio";
		return "";
	}
	Tabla* tabla = this->getTablaActual();
	string toReturn = tabla->getString(bits);
	return toReturn;
}

void TablaDeContextos::limpiar(){
	this->getTablaActual()->limpiar();
}

bool TablaDeContextos::hayQueLimpiar(){
	return this->getTablaActual()->hayQueLimpiar();
}

size_t TablaDeContextos::getCantidadBitsTabla(){
	 return (this->mapaDeContextos[this->contexto]->getCantidadBitsTabla());
}

int TablaDeContextos::getLastCode(){
	return (this->mapaDeContextos[this->contexto]->getLastCode());
}

char TablaDeContextos::getContextoActual(){
	return this->contexto;
}

void TablaDeContextos::Imprimir(ostream& out){
	this->getTablaActual()->Imprimir(out);
}
bool TablaDeContextos::esCodigoLimpieza(CadenaDeBits *cadena){
	return this->getTablaActual()->esCodigoLimpieza(cadena);
}
void TablaDeContextos::obtenerCodigoLimpieza(CadenaDeBits *cadena){
	this->getTablaActual()->obtenerCodigoLimpieza(cadena);
}

