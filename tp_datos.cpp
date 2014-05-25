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
#include "LZCtx.h"
#include "Tabla.h"
#include "BufferLectura.h"
#include "BufferEscritura.h"
#include "Constantes.h"
#include "CadenaDeBits.h"

using namespace std;

int main(int argc, char **argv) {
	if((argc != 3) || !((strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "-d") == 0))){
		// Imprimir ayuda
		cout << "Los parametros son incorrectos." << endl;
		cout << "Uso del comando: tpDatos [-c/-d] nombreArchivo" << endl;
		cout << "Use -c para compresion y -d para descompresion" << endl;
	} else {
		bool esCompresion = (strcmp(argv[1], "-c") == 0);
		// Generar nombre salida
		string nombreSalida;
		string nombreEntrada(argv[2]);
		if(esCompresion) {
			nombreSalida = nombreEntrada + EXTENSION_ARCHIVO_COMPRIMIDO;
		} else {
			string extension = nombreEntrada.substr(nombreEntrada.find_last_of("."));
			if(extension == EXTENSION_ARCHIVO_COMPRIMIDO){
				nombreSalida = nombreEntrada.substr(0, nombreEntrada.find_last_of("."));
			} else {
				cout << "Error: El archivo que intenta descomprimir no fue comprimido previamente." << endl;
				return 0;
			}
		}
		//Compresor *compresor = new LZ78();
		Compresor *compresor = new LZCtx();
		if(esCompresion){
			cout << "Comprimiendo: " << nombreEntrada << " a " << nombreSalida << endl;
			compresor->comprimir(nombreEntrada,nombreSalida);
		} else {
			cout << "Desomprimiendo: " << nombreEntrada << " a " << nombreSalida << endl;
			compresor->descomprimir(nombreEntrada,nombreSalida);
		}
		delete compresor;
	}
	return 0;
}
