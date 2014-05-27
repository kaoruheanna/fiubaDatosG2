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
		cout << "char leido: " << charLeido << endl;
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

			//si es el primer caracter no lo guardo
			if (!esPrimerCaracter){
				this->tabla.agregarString(nuevoString);
			}
			this->tabla.setContexto(charLeidoAnterior.at(0));
			stringLeido = "";

			if (bufferLectura->esFinDeArchivo()){
				cout << "1) el ultimo codigo que imprimo es: " <<codigoGuardado->bits<<endl;
			}

		} else {
			cout << "nuevoString: " << nuevoString << endl;
			this->tabla.getBits(nuevoString,codigoGuardado);
			codigoTipoEscritura->bits = CODIGO_CONTEXTO;
			stringLeido = nuevoString;
			bufferLectura->leer(cadenaLeida);
			charLeidoAnterior = charLeido;
			charLeido = cadenaLeida->getAsChar();

			if (bufferLectura->esFinDeArchivo()){
				cout << "2) el ultimo codigo que imprimo es: " <<codigoGuardado->bits<<endl;
				this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);

//				codigoTipoEscritura->bits = CODIGO_LITERAL;
//				this->setCadenaFromChar(codigoGuardado,charLeido.at(0));
//				cout << "EL ULTIMO QUE PONGO ES: " << charLeido << " " << codigoGuardado->bits << endl;
//				this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
//				cout << "ya no deberia imprimir nada mas (excepto el fin de archivo)" << endl;
			}
		}
		esPrimerCaracter = false;
	}

	delete codigoGuardado;
	delete bufferLectura;
	delete bufferEscritura;
	delete cadenaLeida;
	return 0;
}

int LZCtx::descomprimir(string archivoEntrada, string archivoSalida){
//	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, true);
//	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, true);
//	bufferLectura->crearStream(archivoEntrada);
//	bufferEscritura->crearStream(archivoSalida);
//
//	CadenaDeBits *tipoCodigo = new CadenaDeBits(TAMANIO_TIPO_CODIGO,0);
//	CadenaDeBits *nuevoCodigo = new CadenaDeBits(0,0);
//	size_t cuantosLeer;
//	string nuevoString;
//	string contextoActual;
//	string stringSinTerminar = "";
//	string stringTerminado;
//	bool hayUnStringSinTerminar = false;
//	bool esUnLiteral;
//	pair<pair<int,string>,string> paraAgregar;
//	paraAgregar.first.first = 0;
//	paraAgregar.second = "";
//	int codigoSinTerminar;
//
//	//Leo el primer caracter (se que es un char), lo imprimo y seteo el contexto
//	bufferLectura->leer(tipoCodigo);
//	cuantosLeer = TAMANIO_BYTE;
//	nuevoCodigo->tamanio = cuantosLeer;
//	bufferLectura->leer(nuevoCodigo);
//	nuevoString = this->getStringFromCode(nuevoCodigo->bits);
//	this->imprimirCadena(nuevoString,bufferEscritura);
//
//	this->tabla.setContexto(nuevoString.at(0));
//	contextoActual = nuevoString;
//
//	cout << "Primer caracter :" << nuevoString << endl;
//
//	//A partir del segundo caracter:
//	while (!bufferLectura->esFinDeArchivo()){
//		bufferLectura->leer(tipoCodigo);
//		cout << "TIPO CODIGO: " << tipoCodigo-> bits << endl;
//		if (tipoCodigo->bits == CODIGO_LITERAL){
//			cuantosLeer = TAMANIO_BYTE;
//			esUnLiteral = true;
//		}
//		else {
//			cuantosLeer = this->tabla.getCantidadBitsTabla();
//			cout << "Cant de bits" << cuantosLeer << endl;
//			int maxValor = (pow(2.0,(int)(cuantosLeer)));
//			cout << maxValor<< endl;
//			cout << paraAgregar.first.first << endl;
//			if ((hayUnStringSinTerminar) && (maxValor <= (paraAgregar.first.first)+1)){
//				cuantosLeer++;
//			}
//			cout << "Cant de bits" << cuantosLeer << endl;
//			esUnLiteral = false;
//		}
//
//		nuevoCodigo->tamanio = cuantosLeer;
//		bufferLectura->leer(nuevoCodigo);
//
//		if (((int)nuevoCodigo->bits == paraAgregar.first.first) && (contextoActual == paraAgregar.first.second )){
//			cout << "Es una cadena que no esta completa" << endl;
//			nuevoString = this->completarCadena(paraAgregar.second);
//			this->tabla.setContexto(paraAgregar.first.second.at(0));
//			this->tabla.agregarString(nuevoString);
//			cout << "AGREGO " << nuevoString ;
//			this->tabla.setContexto(nuevoString.at(0));
//		}
//		else{
//			if (esUnLiteral){
//				cout << "Es un literal "<< endl;
//				nuevoString = this->getStringFromCode(nuevoCodigo->bits);
//				cout << nuevoString << endl;
//			}
//			else{
//				cout << "Es un valor de tabla "<< endl;
//				nuevoString = this->tabla.getString(*nuevoCodigo);
//			}
//			if (hayUnStringSinTerminar){
//				cout << "De la iteracion anterior hay que agregar ";
//				stringTerminado = paraAgregar.second + nuevoString.at(0);
//				this->tabla.setContexto(paraAgregar.first.second.at(0));
//				this->tabla.agregarString(stringTerminado);
//				cout << "AGREGO " << stringTerminado ;
//				hayUnStringSinTerminar = false;
//			}
//		}
//		if (esUnLiteral){
//			cout << "Agrego a la tabla "<< nuevoString << endl;
//			this->tabla.agregarString(nuevoString);
//			cout << "AGREGO " << nuevoString ;
//			this->tabla.setContexto(nuevoString.at(0));
//			contextoActual = nuevoString.at(0);
//			this->imprimirCadena(nuevoString,bufferEscritura);
//		}
//		else{
//			this->imprimirCadena(nuevoString,bufferEscritura);
//			cout << "La prox iteracion voy a dar de alta "<< nuevoString << " mas algo" << endl;
//			cout << "en el contexto" << contextoActual << endl;
//			paraAgregar.first.second = contextoActual;
//			stringSinTerminar = nuevoString;
//			this->tabla.setContexto(contextoActual.at(0));
//			codigoSinTerminar = this->tabla.getLastCode();
//			paraAgregar.first.first = codigoSinTerminar;
//			paraAgregar.second = stringSinTerminar;
//			std::string::iterator it= --(nuevoString.end());
//			this->tabla.setContexto(*it);
//			contextoActual = *it;
//			hayUnStringSinTerminar = true;
//		}
//	}
//	delete bufferLectura;
//	delete bufferEscritura;
//	delete tipoCodigo;
//	delete nuevoCodigo;
	return 0;
}

void LZCtx::imprimirCodigo(CadenaDeBits* tipo,CadenaDeBits* codigo, BufferEscritura* bufferEscritura){
	bufferEscritura->escribir(tipo);
	bufferEscritura->escribir(codigo);
	cout << "ESCRIBO: " << tipo->bits << " " << codigo->tamanio << " " << codigo->bits << endl;
}

void LZCtx::imprimirCadena(string cadena, BufferEscritura* bufferEscritura){
	CadenaDeBits *paraGuardar = new CadenaDeBits(TAMANIO_BYTE,0);
	string::iterator textIterator = cadena.begin();
	int i=0;
	while (textIterator != cadena.end()){
		char caracter = cadena[i];
		i++;
		textIterator++;
		paraGuardar->bits = (int)caracter;
		bufferEscritura->escribir(paraGuardar);
		cout << "ESCRIBO: " << caracter << endl;
	}
	delete paraGuardar;
}


void LZCtx::setCadenaFromChar(CadenaDeBits* cadena, char caracter){
	cadena->tamanio = TAMANIO_BYTE;
	cadena->bits = (int)caracter;
}

string LZCtx::getStringFromCode(int codigo){
	string toReturn = "";
	char letra;
	letra = (char)codigo;
	return (toReturn+letra);

}

void LZCtx::ImprimirEn(ostream & out) const{
	out << "LZCtx";
}

string LZCtx::completarCadena(string cadena){
	string::iterator textIterator = cadena.begin();
	cadena = cadena + (*textIterator);
	return cadena;
}

