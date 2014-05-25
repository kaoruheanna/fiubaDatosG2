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
#include "BufferEscritura.h"
#include "Constantes.h"
#include "CadenaDeBits.h"

using namespace std;

int main(int argc, char **argv) {
	Compresor *compresor = new LZ78();

	if(strcmp(argv[1], "-c") == 0){
		cout << "Comprimiendo: " << argv[2] << " a " << argv[3] << endl;
		compresor->comprimir(argv[2],argv[3]);
	} else {
		cout << "Desomprimiendo: " << argv[2] << " a " << argv[3] << endl;
		compresor->descomprimir(argv[2],argv[3]);
	}
	delete compresor;


	return 0;
}
