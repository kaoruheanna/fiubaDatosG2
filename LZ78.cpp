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
		this->fileSalida << cadena << endl;
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



int LZ78::getNextCodigo(string::iterator &codeIterator){
	string charLeido;
	string codigoLeido = "";
	int cantDeBits = 9; //ojo con esto
	for(int i=0;i<cantDeBits;i++){
			charLeido = (*codeIterator);
			codigoLeido = codigoLeido + charLeido;
			++codeIterator;
		}
	int codigoInt = this->binToInt(codigoLeido);
	return codigoInt;
}

int  LZ78::binToInt(string codigoBinario){
	string::iterator textIterator = codigoBinario.end();
	textIterator--;
	int result = 0;
	float dos = 2;
	string charLeido;
	int tamanio = codigoBinario.size();
	for(int i=0;i<tamanio;i++){
		charLeido = (*textIterator);
		if (charLeido == "1"){
			result = result + (pow(dos,i));
		}
	textIterator--;
	}
		return result;
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

int LZ78::descomprimir(string &path){
	this->cargarTabla();
	int ultimoCodigo = 255;

	string codigoParaDescomprimir = path;
	string::iterator codeIterator = codigoParaDescomprimir.begin();

	string cadenaSinTerminar;
	int codigoSinTerminar;

	string cadenaTerminada;
	int codigoTerminado;

	string nuevaCadena;
	CadenaDeBits *nuevoCodigo = new CadenaDeBits(0,0);

	CadenaDeBits *primerCodigo = new CadenaDeBits(0,0);
	primerCodigo->bits = this->getNextCodigo(codeIterator);
	string primerCaracter = this->tabla.getString(*primerCodigo);
	this->imprimirCadena(primerCaracter);

	cout << "Primer código leído: " << primerCodigo->bits << endl;
	cout << "Imprime caracter: " << primerCaracter << endl;
	cout << "" << endl;

	cadenaSinTerminar = primerCaracter;
	cout << "Cadena a agregar: " << cadenaSinTerminar << ", mas algo ";
	codigoSinTerminar = ultimoCodigo+1 ;
	cout << "en el código: " << codigoSinTerminar <<endl;

	while (codeIterator != codigoParaDescomprimir.end()){
		nuevoCodigo->bits = this->getNextCodigo(codeIterator);
		cout << "Siguiente código leído: " << nuevoCodigo->bits << endl;
		if (nuevoCodigo->bits == codigoSinTerminar){
			cout << "Es una cadena que no está completa" << endl;
			cadenaTerminada = this->completarCadena(cadenaSinTerminar);
			cout << "Imprime cadena: " << cadenaTerminada;
			cout << "" << endl;
			this->imprimirCadena(cadenaTerminada);
			codigoTerminado = codigoSinTerminar;

			this->tabla.agregarString(cadenaTerminada);
			this->imprimirTabla(cadenaTerminada);

			cout << "Agrego a la tabla: " << cadenaTerminada;
			cout << " con el código: " << codigoTerminado <<endl;

			cadenaSinTerminar = cadenaTerminada;
			cout << "Cadena a agregar: " << cadenaSinTerminar << ", mas algo ";
			codigoSinTerminar = ++codigoTerminado;
			cout << "en el código: " << codigoSinTerminar<<endl;
		}
		else{
			nuevaCadena = this->tabla.getString(*nuevoCodigo);
			cout << "Imprime caracter/cadena: " << nuevaCadena << endl;
			cout << "" << endl;
			this->imprimirCadena(nuevaCadena);
			cadenaTerminada = cadenaSinTerminar + nuevaCadena[0];
			cout << "Agrego a la tabla: " << cadenaTerminada;
			codigoTerminado = codigoSinTerminar;
			cout << " con el código: " << codigoTerminado << endl;

			this->tabla.agregarString(cadenaTerminada);
			this->imprimirTabla(cadenaTerminada);

			cadenaSinTerminar = nuevaCadena;
			cout << "Cadena a agregar: " << cadenaSinTerminar << ", mas algo ";
			codigoSinTerminar = ++codigoTerminado;
			cout << "en el código: " << codigoSinTerminar <<endl;
		}
	}
delete primerCodigo;
delete nuevoCodigo;
return 0;
}

void LZ78::ImprimirEn(ostream & out) const{
	out << "LZ78";
}


