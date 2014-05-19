/*
 * LZ78.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "LZ78.h"
#include "BufferLectura.h"

LZ78::LZ78() {
	this->fileTabla.open("tabla.txt");
	this->fileSalida.open("salida.txt");
}

LZ78::~LZ78() {
	this->fileTabla.close();
	this->fileSalida.close();
}

void LZ78::imprimirCadena(string cadena){
	if(this->fileSalida.is_open()){
		cout << "Imprime cadena: " << cadena << endl << endl;
		this->fileSalida << cadena;
	}
}

void LZ78::imprimirCodigo(int codigo){
	if(this->fileSalida.is_open()){
		this->fileSalida << codigo << endl;
	}
}

void LZ78::imprimirTabla(string cadena){
//	if (this->fileTabla.is_open()){
//		int codigo = this->tabla.getBits(cadena).bits;
//		this->fileTabla << cadena << "  " << codigo << endl;
//	}
}

//int LZ78::getCodigoCadena(string cadena){
//	if (cadena.length() == 1){
//		char caracter = cadena.at(0);
//		return (int)caracter;
//	}
//
//	map<string,int>::iterator iterador = this->table.find(cadena);
//	return (iterador != this->table.end()) ? (*iterador).second : -1;
//}

//bool LZ78::agregarCadenaATabla(string cadena){
//	pair<map<string,int>::iterator,bool> ret;
//	int codigo = this->lastCode + 1;
//
//	ret = this->table.insert(pair<string,int>(cadena,codigo));
//
//	if (ret.second){
//		if (this->fileTabla.is_open()){
//			this->fileTabla << cadena << "        " << codigo << endl;
//		}
//		this->lastCode = codigo;
//	}
//	return ret.second;
//}

int LZ78::comprimir(string path){
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER);
	bufferLectura->crearStream(path);
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
		cout << "leo el caracter: " << charLeido << endl;
	}

	while ( (!bufferLectura->esFinDeArchivo()) || esPrimerCaracter){
		esPrimerCaracter = false;
		string nuevoString = stringLeido+charLeido;
		cout << "busco la cadena: " << nuevoString << endl;

		if (!(this->tabla.exists(nuevoString))){
			this->imprimirCodigo(codigoGuardado->bits);
			this->tabla.agregarString(nuevoString);
//			this->imprimirTabla(nuevoString);
			stringLeido = "";
			cout << "no la encuentro" << endl;
			cout << "imprimo el codigo: " << codigoGuardado->bits <<endl<<endl;
		} else {
			this->tabla.getBits(nuevoString,codigoGuardado);
			stringLeido = nuevoString;
			cout << "la encuentro" << endl;
			bufferLectura->leer(cadenaLeida);
			charLeido = cadenaLeida->getAsChar();

			if (bufferLectura->esFinDeArchivo()){
				this->imprimirCodigo(codigoGuardado->bits);
				cout << "como es fin de archivo imprimo el codigo " << codigoGuardado->bits << endl;
			}
		}
	}
	delete codigoGuardado;
	delete bufferLectura;
	delete cadenaLeida;
	return 0;
}

string LZ78::completarCadena(string cadena){
	string::iterator textIterator = cadena.begin();
	cadena = cadena + (*textIterator);
	return cadena;
}

void LZ78::cargarTabla(){
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

int LZ78::descomprimir(string path){
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER);
	bufferLectura->crearStream(path);
	this->cargarTabla();

	CadenaDeBits *codigoParaDescomprimir = new CadenaDeBits();

	string stringSinTerminar = "";
	int codigoSinTerminar;

	string stringTerminado;
//	int codigoTerminado;
	size_t cuantosLeer;
	string nuevoString;
	CadenaDeBits *nuevoCodigo = new CadenaDeBits(0,0);

	if (!bufferLectura->esFinDeArchivo()){
		cuantosLeer = this->tabla.getCantidadBitsTabla();
		cout << "Cant bits tabla: " << cuantosLeer << endl;
		nuevoCodigo->tamanio = cuantosLeer;
		bufferLectura->leer(nuevoCodigo);

		string primerCaracter = this->tabla.getString(*nuevoCodigo);
		this->imprimirCadena(primerCaracter);

		cout << "Primer código leído: " << nuevoCodigo->bits << endl;
//		cout << "Imprime caracter: " << primerCaracter << endl;
//		cout << "" << endl;

		stringSinTerminar = primerCaracter;
		cout << "Cadena a agregar: " << stringSinTerminar << ", mas algo ";
//		codigoSinTerminar = (this->tabla.getLastCode())+1;
//		cout << "en el código: " << codigoSinTerminar <<endl;
	}

	while (!bufferLectura->esFinDeArchivo()){
		cuantosLeer = this->tabla.getCantidadBitsTabla();
		cout << "Cant bits tabla: " << cuantosLeer << endl;
		nuevoCodigo->tamanio = cuantosLeer;
		bufferLectura->leer(nuevoCodigo);
		cout << "código leído: " << nuevoCodigo->bits << endl;

		//si el codigo que leo es el que todavia no termine de dar de alta
		if (nuevoCodigo->bits == ((this->tabla.getLastCode())+1)){
			cout << "Es una cadena que no está completa" << endl;
			stringTerminado = this->completarCadena(stringSinTerminar);

			this->imprimirCadena(stringTerminado);
//			codigoTerminado = codigoSinTerminar;

			this->tabla.agregarString(stringTerminado);
//			this->imprimirTabla(stringTerminado);

//			cout << "Agrego a la tabla: " << stringTerminado;
//			cout << " con el código: " << codigoTerminado <<endl;

			stringSinTerminar = stringTerminado;
//			cout << "Cadena a agregar: " << stringSinTerminar << ", mas algo ";
//			codigoSinTerminar = ++codigoTerminado;
//			cout << "en el código: " << codigoSinTerminar<<endl;
		} else {
			nuevoString = this->tabla.getString(*nuevoCodigo);
			this->imprimirCadena(nuevoString);
			stringTerminado = stringSinTerminar + nuevoString[0];
			cout << "Agrego a la tabla: " << stringTerminado;
//			codigoTerminado = codigoSinTerminar;
//			cout << " con el código: " << codigoTerminado << endl;

			this->tabla.agregarString(stringTerminado);
//			this->imprimirTabla(stringTerminado);

			stringSinTerminar = nuevoString;
			cout << "Cadena a agregar: " << stringSinTerminar << ", mas algo ";
//			codigoSinTerminar = ++codigoTerminado;
//			cout << "en el código: " << codigoSinTerminar <<endl;
		}
	}
	delete nuevoCodigo;
	delete bufferLectura;
	delete codigoParaDescomprimir;
	return 0;
}

void LZ78::ImprimirEn(ostream & out) const{
	out << "LZ78";
}


