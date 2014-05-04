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
using namespace std;

int main() {

	LZ78 *lz78 = new LZ78();
	string texto = "ababababc";

	lz78->comprimir(texto);

//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	delete lz78;

	// Pruebas de Tabla
	Tabla* tabla = new Tabla();
	tabla->agregarString("hola");
	tabla->agregarString("chau");
	tabla->agregarString("holas");
	cout << endl;
	cout << "holas exists " << tabla->exists("holas") << endl;
	cout << "hola exists " << tabla->exists("hola") << endl;
	cout << "random exists " << tabla->exists("random") << endl;
	cout << "getBits(chau) " << tabla->getBits("chau").bits << endl;
	cout << "getString(1) " << tabla->getString(CadenaDeBits(1,1)) << endl;
	cout << "1 exists " << tabla->exists(CadenaDeBits(1,1)) << endl;
	cout << "2 exists " << tabla->exists(CadenaDeBits(1,2)) << endl;
	cout << "23 exists " << tabla->exists(CadenaDeBits(1,23)) << endl;
	tabla->Imprimir(cout);
	delete tabla;
	return 0;
}
