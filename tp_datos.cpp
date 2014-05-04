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
using namespace std;

int main() {

	LZ78 *lz78 = new LZ78();
	string texto = "ababababc";
	string textoComprimido = "001100001001100010100000000100000010001100010001100011";
	//lz78->comprimir(texto);
	lz78->descomprimir(textoComprimido);

//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	delete lz78;
	return 0;
}
