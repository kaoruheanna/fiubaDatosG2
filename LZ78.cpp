/*
 * LZ78.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "LZ78.h"


LZ78::LZ78() {
	this->lastCode = 255;
	this->cantDeBits = 9;
	map<string,int>::iterator mapIterator;

	this->fileTabla.open("tabla.txt");
	this->fileSalida.open("salida.txt");

}

LZ78::~LZ78() {
	cout << "cierrro toodo";
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

int LZ78::getCodigoCadena(string cadena){
	if (cadena.length() == 1){
		char caracter = cadena.at(0);
		return (int)caracter;
	}

	map<string,int>::iterator iterador = this->table.find(cadena);
	return (iterador != this->table.end()) ? (*iterador).second : -1;
}


bool LZ78::agregarCadenaATabla(string cadena){
	pair<map<string,int>::iterator,bool> ret;
	int codigo = this->lastCode + 1;

	ret = this->table.insert(pair<string,int>(cadena,codigo));


	if (ret.second){
		if (this->fileTabla.is_open()){
			this->fileTabla << cadena << "        " << codigo << endl;
		}
		this->lastCode = codigo;
	}
	return ret.second;
}

int LZ78::comprimir(string &path){
	string textoParaComprimir = path;

	string textoComprimido = "";
	string leido = "";
	string charLeido;
	int codigoParaImprimir;

	string::iterator textIterator = textoParaComprimir.begin();

	while (textIterator != textoParaComprimir.end()){
		charLeido = (*textIterator);
		cout << "leo el caracter: " << charLeido << endl;
		string nuevaCadena = leido+charLeido;
		cout << "busco la cadena: " << nuevaCadena << endl;
		int codigoGuardado = this->getCodigoCadena(nuevaCadena);

		if (codigoGuardado == -1){
			this->imprimirCodigo(codigoParaImprimir);
			this->agregarCadenaATabla(nuevaCadena);
			leido = "";
			cout << "no la encuentro" << endl;
			cout << "imprimo el codigo: " << codigoParaImprimir <<endl<<endl;
		} else {
			leido = nuevaCadena;
			codigoParaImprimir = codigoGuardado;
			cout << "la encuentro" << endl;
			++textIterator;

			if (textIterator == textoParaComprimir.end()){
				this->imprimirCodigo(codigoParaImprimir);
				cout << "como es fin de archivo imprimo el codigo " << codigoParaImprimir << endl;
			}
		}
	}
	return 0;
}

//string LZ78::getNextChar(){
//	if (!this->isTextIteratorInitialized){
//		this->textIterator = this->textoParaComprimir.begin();
//		this->isTextIteratorInitialized = true;
//	} else if (!this->isEndOfString()){
//		this->textIterator++;
//	}
//
//	if (this->isEndOfString()){
//		return "";
//	} else {
//		return (*(this->textIterator));
//	}
////	return (!this->isEndOfString()) ? (*this->textIterator) : empty;
//}
//
//string LZ78::getCurrentChar(){
//	if ((this->isTextIteratorInitialized) && (!this->isEndOfString())){
//		return (*this->textIterator);
//	}
//	return "";
//}

//bool LZ78::isEndOfString(){
////	if (!this->isTextIteratorInitialized){
////		return false;
////	}
//	return (this->textIterator == this->textoParaComprimir.end());
//}


string LZ78::getCadenaCodigo(int codigo){
	if (codigo < 256){
			char caracter = (char)codigo;
			string c = "";
			c = c+caracter;
			return c;
		}
	map<string,int>::iterator iterador = table.begin();
	bool encontrado = false;
	string cadena ="";
	while (iterador != table.end() && !(encontrado)){
		if (((*iterador).second) == codigo){
			cadena = (*iterador).first;
			encontrado = true;
		}
	iterador++;
	}
	return cadena;
}

int LZ78::getNextCodigo(string::iterator &codeIterator){
	string charLeido;
	string codigoLeido;
	for(int i=0;i<(this->cantDeBits);i++){
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
	string charLeido;
	int tamanio = codigoBinario.size();
	for(int i=0;i<tamanio;i++){
		charLeido = (*textIterator);
		if (charLeido == "1"){
			result = result + (pow(2,i));
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

int LZ78::descomprimir(string &path){
	this->table.clear();

	string codigoParaDescomprimir = path;
	string::iterator codeIterator = codigoParaDescomprimir.begin();

	string cadenaSinTerminar;
	int codigoSinTerminar;

	string cadenaTerminada;
	int codigoTerminado;

	string nuevaCadena;
	int nuevoCodigo;

	int primerCodigo = this->getNextCodigo(codeIterator);
	string primerCaracter = this->getCadenaCodigo(primerCodigo);
	this->imprimirCadena(primerCaracter);

	cout << "Primer código leído: " << primerCodigo << endl;
	cout << "Imprime caracter: " << primerCaracter << endl;
	cout << "" << endl;

	cadenaSinTerminar = primerCaracter;
	cout << "Cadena a agregar: " << cadenaSinTerminar << ", mas algo ";
	codigoSinTerminar = this->lastCode+1 ;
	cout << "en el código: " << codigoSinTerminar <<endl;

	while (codeIterator != codigoParaDescomprimir.end()){
		nuevoCodigo = this->getNextCodigo(codeIterator);
		cout << "Siguiente código leído: " << nuevoCodigo << endl;
		if (nuevoCodigo == codigoSinTerminar){
			cout << "Es una cadena que no está completa" << endl;
			cadenaTerminada = this->completarCadena(cadenaSinTerminar);
			cout << "Imprime cadena: " << cadenaTerminada;
			cout << "" << endl;
			codigoTerminado = codigoSinTerminar;


			this->agregarCadenaATabla(cadenaTerminada);
			this->imprimirCadena(cadenaTerminada);

			cout << "Agrego a la tabla: " << cadenaTerminada;
			cout << " con el código: " << codigoTerminado <<endl;

			cadenaSinTerminar = cadenaTerminada;
			cout << "Cadena a agregar: " << cadenaSinTerminar << ", mas algo ";
			codigoSinTerminar = ++codigoTerminado;
			cout << "en el código: " << codigoSinTerminar <<endl;
		}
		else{
			nuevaCadena = this->getCadenaCodigo(nuevoCodigo);
			cout << "Imprime caracter/cadena: " << nuevaCadena << endl;
			cout << "" << endl;
			cadenaTerminada = cadenaSinTerminar + nuevaCadena[0];
			cout << "Agrego a la tabla: " << cadenaTerminada;
			codigoTerminado = codigoSinTerminar;
			cout << " con el código: " << codigoTerminado << endl;

			this->agregarCadenaATabla(cadenaTerminada);
			this->imprimirCadena(cadenaTerminada);

			cadenaSinTerminar = nuevaCadena;
			cout << "Cadena a agregar: " << cadenaSinTerminar << ", mas algo ";
			codigoSinTerminar = ++codigoTerminado;
			cout << "en el código: " << codigoSinTerminar <<endl;
		}
	}
return 0;
}

void LZ78::ImprimirEn(ostream & out) const{
	out << "LZ78";
}


