/*
 * LZContextos.cpp
 *
 *  Created on: May 25, 2014
 *      Author: kaoru
 */

#include "LZCtx.h"

LZCtx::LZCtx() {
	// TODO Auto-generated constructor stub

}

LZCtx::~LZCtx() {
	// TODO Auto-generated destructor stub
}

int LZCtx::comprimir(string archivoEntrada, string archivoSalida){
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, true);
	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, true);
	bufferLectura->crearStream(archivoEntrada);
	bufferEscritura->crearStream(archivoSalida);

	string textoComprimido = "";
	string stringLeido = "";
	string charLeido = "";
	string charLeidoAnterior = "";
	bool esPrimerCaracter = false;
	CadenaDeBits *codigoGuardado = new CadenaDeBits();
	CadenaDeBits *codigoTipoEscritura = new CadenaDeBits();
	codigoTipoEscritura->tamanio = TAMANIO_TIPO_CODIGO;
	CadenaDeBits *cadenaLeida = new CadenaDeBits();

	if (!bufferLectura->esFinDeArchivo()){
		bufferLectura->leer(cadenaLeida);
		charLeido = cadenaLeida->getAsChar();
		esPrimerCaracter = true;
		codigoTipoEscritura->bits = CODIGO_LITERAL;
	}

	while ( (!bufferLectura->esFinDeArchivo()) || esPrimerCaracter){
		esPrimerCaracter = false;

		string nuevoString = stringLeido+charLeido;
		if (!(this->tabla.exists(nuevoString))){
			//si tengo un solo caracter
			if (nuevoString.length() == 1){
				codigoTipoEscritura->bits = CODIGO_LITERAL;
				this->setCadenaFromChar(codigoGuardado,charLeido.at(0));
				bufferLectura->leer(cadenaLeida);
				charLeidoAnterior = charLeido;
				charLeido = cadenaLeida->getAsChar();

			}

			this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
			this->tabla.agregarString(nuevoString);
			this->tabla.setContexto(charLeidoAnterior.at(0));
			stringLeido = "";
		} else {
			this->tabla.getBits(nuevoString,codigoGuardado);
			codigoTipoEscritura->bits = CODIGO_CONTEXTO;
			stringLeido = nuevoString;
			bufferLectura->leer(cadenaLeida);
			charLeidoAnterior = charLeido;
			charLeido = cadenaLeida->getAsChar();

			if (bufferLectura->esFinDeArchivo()){
				this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
				codigoTipoEscritura->bits = CODIGO_LITERAL;
				this->setCadenaFromChar(codigoGuardado,charLeido.at(0));
				this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
			}

		}
	}

	delete codigoGuardado;
	delete bufferLectura;
	delete bufferEscritura;
	delete cadenaLeida;
	return 0;
}

int LZCtx::descomprimir(string archivoEntrada, string archivoSalida){
	return 0;
}

void LZCtx::imprimirCodigo(CadenaDeBits* tipo,CadenaDeBits* codigo, BufferEscritura* bufferEscritura){
	bufferEscritura->escribir(tipo);
	bufferEscritura->escribir(codigo);
	cout << "ESCRIBO: " << tipo->bits << " " << codigo->bits << endl;
}


void LZCtx::setCadenaFromChar(CadenaDeBits* cadena, char caracter){
	cadena->tamanio = TAMANIO_BYTE;
	cadena->bits = (int)caracter;
}

