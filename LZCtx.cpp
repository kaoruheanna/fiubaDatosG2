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
			bool esUnicoCaracter = (nuevoString.length() == 1);
			//si tengo un solo caracter
			if (esUnicoCaracter){
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
				if (esUnicoCaracter){
					codigoTipoEscritura->bits = CODIGO_LITERAL;
					this->setCadenaFromChar(codigoGuardado,charLeido.at(0));
					this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
				}
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

				codigoTipoEscritura->bits = CODIGO_LITERAL;
				this->setCadenaFromChar(codigoGuardado,charLeido.at(0));
				cout << "EL ULTIMO QUE PONGO ES: " << charLeido << " " << codigoGuardado->bits << endl;
				this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
				cout << "ya no deberia imprimir nada mas (excepto el fin de archivo)" << endl;
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

//int LZCtx::comprimir(string archivoEntrada, string archivoSalida){
//	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, true);
//	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, true);
//	bufferLectura->crearStream(archivoEntrada);
//	bufferEscritura->crearStream(archivoSalida);
//
//	string stringLeido = "";
//	string charLeido = "";
//	string charLeidoAnterior = "";
//	bool esPrimerCaracter = false;
//	CadenaDeBits *codigoGuardado = new CadenaDeBits();
//	CadenaDeBits *codigoTipoEscritura = new CadenaDeBits();
//	codigoTipoEscritura->tamanio = TAMANIO_TIPO_CODIGO;
//	CadenaDeBits *cadenaLeida = new CadenaDeBits();
////	bool faltaImprimir = false;
//
//	if (!bufferLectura->esFinDeArchivo()){
//		bufferLectura->leer(cadenaLeida);
////		faltaImprimir = true;
//		charLeido = cadenaLeida->getAsChar();
////		esPrimerCaracter = true;
//		codigoTipoEscritura->bits = CODIGO_LITERAL;
//		this->setCadenaFromChar(codigoGuardado,charLeido.at(0));
//		cout << "imprimo el primer caracter que viene" << endl;
//		this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
//		this->tabla.setContexto(charLeido.at(0));
//	}
//
//	while (!bufferLectura->esFinDeArchivo()){
////		charLeidoAnterior = charLeido;
//		bufferLectura->leer(cadenaLeida);
//		charLeido = cadenaLeida->getAsChar();
//		cout << "lei el caracter: '"<<charLeido<<"'"<<endl;
//		string nuevoString = stringLeido+charLeido;
//
//		cout<<"busco nuevoString: '"<<nuevoString<<"'";
//		cout<<" en contexto: '"<<this->tabla.getContextoActual()<<"'"<<endl;
//
//		if (!(this->tabla.exists(nuevoString))){
//
//			//si no lo encuentro en la tabla tengo que imprimir
//			bool esUnSoloCaracter = (nuevoString.length() == 1);
//
//			if (esUnSoloCaracter){
//				//si tengo un solo caracter y no lo encontre en la tabla uso el codigo del literal
//				codigoTipoEscritura->bits = CODIGO_LITERAL;
//				this->setCadenaFromChar(codigoGuardado,charLeido.at(0));
//			}
//
//			this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
//			stringLeido = "";
//			this->tabla.agregarString(nuevoString);
//			cout<<"Agrego '"<<nuevoString <<"' en el contexto '"<<this->tabla.getContextoActual()<<"'"<<endl;
//			this->tabla.setContexto(charLeido.at(0));
//			cout<<"seteo el nuevo contexto:'"<<charLeido.at(0)<<"'"<<endl;
//
//
//		} else {
//
//			//si lo encuentro en la tabla guardo el codigo.
//			this->tabla.getBits(nuevoString,codigoGuardado);
//			codigoTipoEscritura->bits = CODIGO_CONTEXTO;
//			//y me guardo el string que llevo leido hasta el momento
//			stringLeido = nuevoString;
//		}
//	}
//
//	delete codigoGuardado;
//	delete bufferLectura;
//	delete bufferEscritura;
//	delete cadenaLeida;
//	return 0;
//
//}

int LZCtx::descomprimir(string archivoEntrada, string archivoSalida){
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, false);
	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, false);
	bufferLectura->crearStream(archivoEntrada);
	bufferEscritura->crearStream(archivoSalida);

	CadenaDeBits *tipoCodigo = new CadenaDeBits(TAMANIO_TIPO_CODIGO,0);
	CadenaDeBits *nuevoCodigo = new CadenaDeBits(0,0);
	size_t cuantosLeer;
	string nuevoString;
	string contextoActual;
	string stringTerminado;
	bool hayUnStringSinTerminar = false;
	bool esUnLiteral;
	int paraAgregarCodigo = 0;
	string paraAgregarContexto = "";
	string paraAgregarString = "";

	/* ANALIZAR EL CASO DE ARCHIVO VACIO */

	//Leo el primer caracter (se que es un char), lo imprimo y seteo el contexto
	if (!bufferLectura->esFinDeArchivo()){
		bufferLectura->leer(tipoCodigo);
		if (tipoCodigo->bits == CODIGO_LITERAL){
			cuantosLeer = TAMANIO_BYTE;
			nuevoCodigo->tamanio = cuantosLeer;
			bufferLectura->leer(nuevoCodigo);
			nuevoString = this->getStringFromCode(nuevoCodigo->bits);
			this->imprimirCadena(nuevoString,bufferEscritura);
			this->tabla.setContexto(nuevoString.at(0));
		}
	}

	//A partir del segundo caracter:
	while (!bufferLectura->esFinDeArchivo()){
		bufferLectura->leer(tipoCodigo);
		if (tipoCodigo->bits == CODIGO_LITERAL){
			cuantosLeer = TAMANIO_BYTE;
			esUnLiteral = true;
		}
		else {
			cuantosLeer = this->tabla.getCantidadBitsTabla();
			int maxValor = (pow(2.0,(int)(cuantosLeer)));
			if ((hayUnStringSinTerminar) && (maxValor <= (paraAgregarCodigo)+1)  && (this->tabla.getContextoActual() == paraAgregarContexto.at(0))){
				cuantosLeer++;
			}
			cout << "cantidad de bits a leer: " << cuantosLeer << endl;
			esUnLiteral = false;
		}

		nuevoCodigo->tamanio = cuantosLeer;
		bufferLectura->leer(nuevoCodigo);

		if (((int)nuevoCodigo->bits == paraAgregarCodigo) && (this->tabla.getContextoActual() == paraAgregarContexto.at(0))){
			cout << "Es una cadena que no esta completa" << endl;
			nuevoString = this->completarCadena(paraAgregarString);
			this->tabla.setContexto(paraAgregarContexto.at(0));
			this->tabla.agregarString(nuevoString);
			this->tabla.setContexto(nuevoString.at(0));
		}
		else{
			if (esUnLiteral){
				nuevoString = this->getStringFromCode(nuevoCodigo->bits);
			}
			else{
				nuevoString = this->tabla.getString(*nuevoCodigo);
			}
			if (hayUnStringSinTerminar){
				stringTerminado = paraAgregarString + nuevoString.at(0);
				contextoActual = this->tabla.getContextoActual();
				this->tabla.setContexto(paraAgregarContexto.at(0));
				this->tabla.agregarString(stringTerminado);
				this->tabla.setContexto(contextoActual.at(0));
				hayUnStringSinTerminar = false;
			}
		}
		if (esUnLiteral){
			this->tabla.agregarString(nuevoString);
			this->tabla.setContexto(nuevoString.at(0));
			this->imprimirCadena(nuevoString,bufferEscritura);
		}
		else{
			this->imprimirCadena(nuevoString,bufferEscritura);
			paraAgregarContexto = this->tabla.getContextoActual();
			paraAgregarCodigo = this->tabla.getLastCode();
			paraAgregarString = nuevoString;
			std::string::iterator it= --(nuevoString.end());
			this->tabla.setContexto(*it);
			hayUnStringSinTerminar = true;
		}
	}
	delete bufferLectura;
	delete bufferEscritura;
	delete tipoCodigo;
	delete nuevoCodigo;
	return 0;
}

void LZCtx::imprimirCodigo(CadenaDeBits* tipo,CadenaDeBits* codigo, BufferEscritura* bufferEscritura){
	bufferEscritura->escribir(tipo);
	bufferEscritura->escribir(codigo);
	cout << "ESCRIBO: " << tipo->bits << ", y uso " << codigo->tamanio << " bits para el codigo " << codigo->bits << endl;
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

