/*
 * LZ78.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "LZ78.h"


LZ78::LZ78() {
	this->lastCode = 255;
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

int LZ78::descomprimir(string path){
	return 0;
}

void LZ78::ImprimirEn(ostream & out) const{
	out << "LZ78";
}


