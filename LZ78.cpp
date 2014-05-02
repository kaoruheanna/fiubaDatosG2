/*
 * LZ78.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#include "LZ78.h"


LZ78::LZ78() {
	this->lastCode = -1;
	map<string,int>::iterator mapIterator;

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

map<string,int>::iterator LZ78::getCodigoCadena(string cadena){
	return this->table.find(cadena);
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
	} else {
		cout << "ya existia el elemeto: " << cadena << endl;
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
		string nuevaCadena = leido+charLeido;

		if (nuevaCadena.length() > 1){
			cout << "entro al if con la nuevaCadena: " << nuevaCadena << endl;
			map<string,int>::iterator cadenaGuardada = this->getCodigoCadena(nuevaCadena);


			if (cadenaGuardada == this->table.end()){
				this->imprimirCadena(leido);
				this->agregarCadenaATabla(nuevaCadena);
				leido = charLeido;
			} else {
				leido = nuevaCadena;
			}
		} else {
			cout << "entro al else con la nuevaCadena: " << nuevaCadena << endl;
			leido = nuevaCadena;
		}

		++textIterator;
		cout << leido << endl;
	}

//	while (it != path.end()){
//
//		if (leido.length() > 1){
//			map<string,int>::iterator cadenaGuardada = this->getCodigoCadena(leido);
//
//			if (cadenaGuardada == this->table.end()){
//				this->imprimirCadena(leido);
//				this->agregarCadenaATabla(leido);
//			} else {
//				codigoParaImprimir = (*cadenaGuardada).second;
//
//
//			}
//		}
//
//	}


//	cout << "Leido: " << leido << endl;
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


