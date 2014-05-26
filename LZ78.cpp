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
		//cout << "ESCRIBO: " << caracter << endl;
	}
	delete paraGuardar;
}

void LZ78::imprimirCodigo(CadenaDeBits* codigo, BufferEscritura* bufferEscritura){
	bufferEscritura->escribir(codigo);
	//cout << "ESCRIBO: " << codigo->bits << endl;
}

void LZ78::imprimirTabla(string cadena){
//	if (this->fileTabla.is_open()){
//		int codigo = this->tabla.getBits(cadena).bits;
//		this->fileTabla << cadena << "  " << codigo << endl;
//	}
}

int LZ78::comprimir(string archivoEntrada, string archivoSalida){
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, true);
	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, true);
	bufferLectura->crearStream(archivoEntrada);
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
//		cout << "leo el caracter: " << charLeido << endl;
	}

	while ( (!bufferLectura->esFinDeArchivo()) || esPrimerCaracter){
		esPrimerCaracter = false;
		string nuevoString = stringLeido+charLeido;
//		cout << "busco la cadena: " << nuevoString << endl;

		if (!(this->tabla.exists(nuevoString))){
			this->imprimirCodigo(codigoGuardado,bufferEscritura);
			this->tabla.agregarString(nuevoString);

			if(this->tabla.hayQueLimpiar()){

				this->tabla.obtenerCodigoLimpieza(codigoGuardado);
				//cout << "Nuevo string sin terminar " << charLeido << endl;
				//cout << "Codigo de limpieza de " << codigoGuardado->tamanio << " bits" << endl;
				this->imprimirCodigo(codigoGuardado,bufferEscritura);
				this->tabla.limpiar();
				this->cargarTabla();
			}

//			this->imprimirTabla(nuevoString);
			stringLeido = "";
//			cout << "no la encuentro" << endl;
//			cout << "imprimo el codigo: " << codigoGuardado->bits <<endl<<endl;
		} else {
			this->tabla.getBits(nuevoString,codigoGuardado);
			stringLeido = nuevoString;
//			cout << "la encuentro" << endl;
			bufferLectura->leer(cadenaLeida);
			charLeido = cadenaLeida->getAsChar();

			if (bufferLectura->esFinDeArchivo()){
				this->imprimirCodigo(codigoGuardado,bufferEscritura);
				nuevoString = charLeido;
				this->tabla.getBits(nuevoString,codigoGuardado);
				this->imprimirCodigo(codigoGuardado,bufferEscritura);
				//cout << "como es fin de archivo imprimo el codigo " << codigoGuardado->bits << endl;
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

		//cout << "Primer código leído: " << nuevoCodigo->bits << endl;

		stringSinTerminar = primerCaracter;
//		cout << "Cadena a agregar: " << stringSinTerminar << ", mas algo " <<endl;;
	}
	//cout << "Primer caracter " << stringSinTerminar << endl;
	while (!bufferLectura->esFinDeArchivo()){
		cuantosLeer = this->tabla.getCantidadBitsTabla();
		int maxValor = (pow(2.0,(int)(cuantosLeer)));
		if(maxValor <= (this->tabla.getLastCode() + 1)){
			//cout << "Leyendo codigos de " << cuantosLeer + 1 << "bits" << endl;
			cuantosLeer ++;
		}
		nuevoCodigo->tamanio = cuantosLeer;
		bufferLectura->leer(nuevoCodigo);
	//	cout << "código leído: " << nuevoCodigo->bits << endl;

		if(this->tabla.esCodigoLimpieza(nuevoCodigo)){
			this->tabla.limpiar();
			this->cargarTabla();
			//cout << "Limpiando tabla... " <<endl;
			// Leo devuelta para determinar el primer caracter del nuevo string
			cuantosLeer = this->tabla.getCantidadBitsTabla();
			nuevoCodigo->tamanio = cuantosLeer;
			bufferLectura->leer(nuevoCodigo);

			primerCaracter = this->tabla.getString(*nuevoCodigo);
			this->imprimirCadena(primerCaracter,bufferEscritura);

			//cout << "Primer código leído: " << nuevoCodigo->bits << endl;

			stringSinTerminar = primerCaracter;
		} else if (nuevoCodigo->bits == this->tabla.getLastCode()){
			//si el codigo que leo es el que todavia no termine de dar de alta
//			cout << "Es una cadena que no está completa" << endl;
			stringTerminado = this->completarCadena(stringSinTerminar);

			this->imprimirCadena(stringTerminado,bufferEscritura);

			this->tabla.agregarString(stringTerminado);

//			this->imprimirTabla(stringTerminado);

//			cout << "Agrego a la tabla: " << stringTerminado << endl;;

			stringSinTerminar = stringTerminado;
//			cout << "Cadena a agregar: " << stringSinTerminar << ", mas algo " << endl;
		} else {
			nuevoString = this->tabla.getString(*nuevoCodigo);
			this->imprimirCadena(nuevoString,bufferEscritura);
			stringTerminado = stringSinTerminar + nuevoString[0];
//			cout << "Agrego a la tabla: " << stringTerminado;


			this->tabla.agregarString(stringTerminado);
//			this->imprimirTabla(stringTerminado);

			stringSinTerminar = nuevoString;
//			cout << "Cadena a agregar: " << stringSinTerminar << ", mas algo " << endl;
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


