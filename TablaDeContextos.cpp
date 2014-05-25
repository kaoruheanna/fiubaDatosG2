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
	char contexto = this->contexto;
	cout << "estoy en contexto " << contexto << " y busco " << cadena << endl;
	Tabla* tabla = this->getTablaActual();
	return tabla->exists(cadena);
}

/**
 * to do
 */
bool TablaDeContextos::exists(CadenaDeBits bits){
	return false;
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
//	return (this->contexto != NULL);
	return this->contextoSeteado;
}

Tabla* TablaDeContextos::getTablaActual(){
	if (!this->tengoContexto()){
		return NULL;
	}
	return this->mapaDeContextos[this->contexto];
}

/**
 * to do
 */
string TablaDeContextos::getString(CadenaDeBits bits){
	return "";
}

/**
 * to do
 */
void TablaDeContextos::limpiar(){

}

/**
 * to do
 */
bool TablaDeContextos::hayQueLimpiar(){
	return false;
}

/**
 * to do
 */
size_t TablaDeContextos::getCantidadBitsTabla(){
	return 0;
}




