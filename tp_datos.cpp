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

int ejecucionPorConsola(int argc, char **argv){
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
			int index = nombreEntrada.find_last_of(".");
			index = index > 0 ? index : 0;
			string extension = nombreEntrada.substr(index);

			if(extension == EXTENSION_ARCHIVO_COMPRIMIDO){
				nombreSalida = nombreEntrada.substr(0, nombreEntrada.find_last_of("."));
			} else {
				cout << "Error: El archivo que intenta descomprimir no fue comprimido previamente." << endl;
				return 0;
			}
		}


		Compresor *compresor;
		if (LZ_CONTEXTOS){
			compresor = new LZCtx();
		} else {
			compresor = new LZ78();
		}

		long int timeStart;
		long int timeEnd;
		time(&timeStart);
		if(esCompresion){
			cout << "Comprimiendo: " << nombreEntrada << " a " << nombreSalida << endl;
			if(compresor->comprimir(nombreEntrada,nombreSalida) != 0){
				cout << "No puede comprimirse el archivo" << endl;
				return 1;
			}
		} else {
			cout << "Descomprimiendo: " << nombreEntrada << " a " << nombreSalida << endl;
			if(compresor->descomprimir(nombreEntrada,nombreSalida) != 0){
				cout << "No puede descomprimirse el archivo" << endl;
				return 1;
			}
		}
		time(&timeEnd);
		cout << "Tardo en segundos: " << (timeEnd - timeStart) << endl;
		delete compresor;
	}
	return 0;
}

int ejecucionModoDebug(bool esCompresion){
	string aComprimir = "debug_entrada.txt";
	string comprimido = "debug_comprimido.txt.13";
	string descomprimido = "debug_salida.txt";
	string nombreEntrada = "";
	string nombreSalida = "";

	if(esCompresion) {
		nombreEntrada = aComprimir;
		nombreSalida = comprimido;
	} else {
		nombreEntrada = comprimido;
		nombreSalida = descomprimido;
	}

	Compresor *compresor;
	if (LZ_CONTEXTOS){
		compresor = new LZCtx();
	} else {
		compresor = new LZ78();
	}

	long int timeStart;
	long int timeEnd;
	time(&timeStart);
	if(esCompresion){
		cout << "Comprimiendo: " << nombreEntrada << " a " << nombreSalida << endl;
		compresor->comprimir(nombreEntrada,nombreSalida);
	} else {
		cout << "Descomprimiendo: " << nombreEntrada << " a " << nombreSalida << endl;
		compresor->descomprimir(nombreEntrada,nombreSalida);
	}
	time(&timeEnd);
	cout << "Tardo en segundos: " << (timeEnd - timeStart) << endl;
	delete compresor;

	return 0;
}

int main(int argc, char **argv) {
	if (MODO_DEBUG){
		bool esCompresion = true;
		return ejecucionModoDebug(esCompresion);
	} else {
		return ejecucionPorConsola(argc,argv);
	}
}

