/*
 * LZ78.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "LZ78.h"

LZ78::LZ78() {
}

LZ78::~LZ78() {
}

void LZ78::imprimirCadena(string cadena, BufferEscritura* bufferEscritura){
	CadenaDeBits *paraGuardar = new CadenaDeBits(TAMANIO_BYTE,0);
	string::iterator textIterator = cadena.begin();
	int i=0;
	while (textIterator != cadena.end()){
		char caracter = cadena[i];
		i++;
		textIterator++;
		paraGuardar->bits = (int)caracter;
		bufferEscritura->escribir(paraGuardar);
	}
	delete paraGuardar;
}

void LZ78::imprimirCodigo(CadenaDeBits* codigo, BufferEscritura* bufferEscritura){
	bufferEscritura->escribir(codigo);
}

void LZ78::imprimirTabla(string cadena){
}

int LZ78::comprimir(string archivoEntrada, string archivoSalida){
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, true);
	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, true);
	bufferLectura->crearStream(archivoEntrada);
	if(!bufferLectura->estaAbierto()){
		//No existe el archivo
		return 1;
	}

	bufferEscritura->crearStream(archivoSalida);
	this->cargarTabla();

	string textoComprimido = "";
	string stringLeido = "";
	string charLeido = "";
	bool esPrimerCaracter = false;
	CadenaDeBits *codigoGuardado = new CadenaDeBits();
	CadenaDeBits *cadenaLeida = new CadenaDeBits();

	if (!bufferLectura->esFinDeArchivo()){
		bufferLectura->leer(cadenaLeida);
		charLeido = cadenaLeida->getAsChar();
		esPrimerCaracter = true;
	}

	while ( (!bufferLectura->esFinDeArchivo()) || esPrimerCaracter){
		esPrimerCaracter = false;
		string nuevoString = stringLeido+charLeido;

		if (!(this->tabla.exists(nuevoString))){
			this->imprimirCodigo(codigoGuardado,bufferEscritura);
			this->tabla.agregarString(nuevoString);

			if(this->tabla.hayQueLimpiar()){

				this->tabla.obtenerCodigoLimpieza(codigoGuardado);
				this->imprimirCodigo(codigoGuardado,bufferEscritura);
				this->tabla.limpiar();
				this->cargarTabla();
			}

			stringLeido = "";
		} else {
			this->tabla.getBits(nuevoString,codigoGuardado);
			stringLeido = nuevoString;
			bufferLectura->leer(cadenaLeida);
			charLeido = cadenaLeida->getAsChar();

			if (bufferLectura->esFinDeArchivo()){
				this->imprimirCodigo(codigoGuardado,bufferEscritura);
				nuevoString = charLeido;
				this->tabla.getBits(nuevoString,codigoGuardado);
				this->imprimirCodigo(codigoGuardado,bufferEscritura);
			}
		}
	}

	delete codigoGuardado;
	delete bufferLectura;
	delete bufferEscritura;
	delete cadenaLeida;
	return 0;
}

string LZ78::completarCadena(string cadena){
	string::iterator textIterator = cadena.begin();
	cadena = cadena + (*textIterator);
	return cadena;
}

void LZ78::cargarTabla(){
	this->tabla.borrarTodo();
	char c;
	string caracter;
	for (int codigo=0;codigo<256;codigo++){
		c = (char)codigo;
		caracter = "";
		caracter = caracter+c;
		this->tabla.agregarString(caracter);
		this->imprimirTabla(caracter);
	}
}

int LZ78::descomprimir(string archivoEntrada, string archivoSalida){
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, false);
	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, false);
	bufferLectura->crearStream(archivoEntrada);
	if(!bufferLectura->estaAbierto()){
		//No existe el archivo
		return 1;
	}
	bufferEscritura->crearStream(archivoSalida);
	this->cargarTabla();

	string stringSinTerminar = "";
	string stringTerminado;
	size_t cuantosLeer;
	string primerCaracter;
	string nuevoString;
	CadenaDeBits *nuevoCodigo = new CadenaDeBits(0,0);

	if (!bufferLectura->esFinDeArchivo()){
		cuantosLeer = this->tabla.getCantidadBitsTabla();
		nuevoCodigo->tamanio = cuantosLeer;
		bufferLectura->leer(nuevoCodigo);

		primerCaracter = this->tabla.getString(*nuevoCodigo);
		this->imprimirCadena(primerCaracter,bufferEscritura);

		stringSinTerminar = primerCaracter;
	}
	while (!bufferLectura->esFinDeArchivo()){
		cuantosLeer = this->tabla.getCantidadBitsTabla();
		int maxValor = (pow(2.0,(int)(cuantosLeer)));
		if(maxValor <= (this->tabla.getLastCode() + 1)){
			cuantosLeer ++;
		}
		nuevoCodigo->tamanio = cuantosLeer;
		bufferLectura->leer(nuevoCodigo);

		if(this->tabla.esCodigoLimpieza(nuevoCodigo)){
			this->tabla.limpiar();
			this->cargarTabla();
			// Leo de vuelta para determinar el primer caracter del nuevo string
			cuantosLeer = this->tabla.getCantidadBitsTabla();
			nuevoCodigo->tamanio = cuantosLeer;
			bufferLectura->leer(nuevoCodigo);

			primerCaracter = this->tabla.getString(*nuevoCodigo);
			this->imprimirCadena(primerCaracter,bufferEscritura);

			stringSinTerminar = primerCaracter;
		} else if (nuevoCodigo->bits == this->tabla.getLastCode()){
			//si el codigo que leo es el que todavia no termine de dar de alta
			stringTerminado = this->completarCadena(stringSinTerminar);

			this->imprimirCadena(stringTerminado,bufferEscritura);

			this->tabla.agregarString(stringTerminado);

			stringSinTerminar = stringTerminado;
		} else {
			nuevoString = this->tabla.getString(*nuevoCodigo);
			this->imprimirCadena(nuevoString,bufferEscritura);
			stringTerminado = stringSinTerminar + nuevoString[0];
			this->tabla.agregarString(stringTerminado);
			stringSinTerminar = nuevoString;
		}
	}
	delete nuevoCodigo;
	delete bufferLectura;
	delete bufferEscritura;
	return 0;
}

void LZ78::ImprimirEn(ostream & out) const{
	out << "LZ78";
}


