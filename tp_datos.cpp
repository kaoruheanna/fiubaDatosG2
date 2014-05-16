//============================================================================
// Name        : hello_world.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include "LZ78.h"
#include "Tabla.h"
#include "BufferLectura.h"
#include "Constantes.h"
#include "CadenaDeBits.h"

using namespace std;

int main() {

	BufferLectura *buffer = new BufferLectura(TAMANIO_BUFFER);
	buffer->crearStream("entrada.txt");
	while(!buffer->esFinDeArchivo()){
		CadenaDeBits *cadenaDeBits= new CadenaDeBits(8,0);
		buffer->leer(cadenaDeBits);
		cout << cadenaDeBits << endl;
		delete cadenaDeBits;
	}


	LZ78 *lz78 = new LZ78();
	string texto = "ababababc";
	string texto2 = "abcababa";
	string textoComprimido = "001100001001100010100000000100000010001100010001100011";
	string textoComprimido2 = "001100001001100010001100011100000000100000011";
	lz78->comprimir(texto2);
	//lz78->descomprimir(textoComprimido);
	delete lz78;
	
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	delete lz78;

	 //Pruebas de Tabla
//	Tabla* tabla = new Tabla();
//	tabla->agregarString("hola");
//	tabla->agregarString("chau");
//	tabla->agregarString("holas");
//	tabla->agregarString("a");
//	tabla->agregarString("b");
//	tabla->agregarString("c");
//	tabla->agregarString("d");
//	tabla->agregarString("e");
//	cout << endl;
//	cout << "holas exists " << tabla->exists("holas") << endl;
//	cout << "hola exists " << tabla->exists("hola") << endl;
//	cout << "random exists " << tabla->exists("random") << endl;
//	cout << "getBits(chau) " << tabla->getBits("chau").bits << endl;
//
//	cout << "Bits(hola) " << tabla->getBits("hola").bits << endl;
//	cout << "Tamaño(hola) " << tabla->getBits("hola").tamanio << endl;
//	cout << "Bits(chau) " << tabla->getBits("chau").bits << endl;
//	cout << "Tamaño(chau) " << tabla->getBits("chau").tamanio << endl;
//	cout << "Bits(holas) " << tabla->getBits("holas").bits << endl;
//	cout << "Tamaño(holas) " << tabla->getBits("holas").tamanio << endl;
//	cout << "Bits(a) " << tabla->getBits("a").bits << endl;
//	cout << "Tamaño(a) " << tabla->getBits("a").tamanio << endl;
//	cout << "Bits(b) " << tabla->getBits("b").bits << endl;
//	cout << "Tamaño(b) " << tabla->getBits("b").tamanio << endl;
//	cout << "Bits(c) " << tabla->getBits("c").bits << endl;
//	cout << "Tamaño(c) " << tabla->getBits("c").tamanio << endl;
//	cout << "Bits(d) " << tabla->getBits("d").bits << endl;
//	cout << "Tamaño(d) " << tabla->getBits("d").tamanio << endl;
//	cout << "Bits(e) " << tabla->getBits("e").bits << endl;
//	cout << "Tamaño(e) " << tabla->getBits("e").tamanio << endl;
//
//  cout << "getString(1) " << tabla->getString(CadenaDeBits(1,1)) << endl;
//	cout << "1 exists " << tabla->exists(CadenaDeBits(1,1)) << endl;
//	cout << "2 exists " << tabla->exists(CadenaDeBits(1,2)) << endl;
//	cout << "23 exists " << tabla->exists(CadenaDeBits(1,23)) << endl;
//
//	tabla->Imprimir(cout);
//	delete tabla;
	return 0;
}
