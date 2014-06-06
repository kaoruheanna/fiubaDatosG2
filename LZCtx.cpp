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
	if(!bufferLectura->estaAbierto()){
		return 1;
	}

	bufferEscritura->crearStream(archivoSalida);

	string stringLeido = "";
//	string charLeido = "";
	char charLeido, charLeidoAnterior;
//	string charLeidoAnterior = "";
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
		this->setCadenaFromChar(codigoGuardado,charLeido);
		//cout << "Bits leidos " << codigoGuardado->tamanio + 1 << endl;
		//cout << "Leido un char: " << charLeido << endl;
		this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
		this->tabla.setContexto(charLeido);
		charLeidoAnterior = charLeido;
		bufferLectura->leer(cadenaLeida);
		charLeido = cadenaLeida->getAsChar();
	}

	while ( (!bufferLectura->esFinDeArchivo()) || esPrimerCaracter){
		//cout << "char leido: " << charLeido << endl;
		string nuevoString = stringLeido+charLeido;
		if (!(this->tabla.exists(nuevoString) || (nuevoString.length() == 1))){
			/*if(codigoTipoEscritura->bits == CODIGO_LITERAL){
				cout << "Bits leidos " << codigoGuardado->tamanio + 1 << endl;
				cout << "Leido un char: " << nuevoString.substr(0, nuevoString.length() - 1) << endl;
			} else{
				//cout << "Contexto: " << this->tabla.getContextoActual() << " Last code:" << this->tabla.getLastCode() << endl;
				cout << "Bits leidos " << codigoGuardado->tamanio + 1 << endl;
				cout << "Leido codigo: " << codigoGuardado->bits << endl;
				cout << "Leido un string: " << nuevoString.substr(0, nuevoString.length() - 1) << endl;
			}*/
			this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
			bool limpiarTabla = false;
			this->tabla.agregarString(nuevoString);
			if(this->tabla.hayQueLimpiar() && (this->tabla.getContextoActual() != charLeidoAnterior)){
				this->tabla.limpiar();
				limpiarTabla = true;
				//cout << "Contexto: " << this->tabla.getContextoActual() << " Tabla limpiada." << endl;
			} else {
				//cout << "Contexto: " << this->tabla.getContextoActual() <<" Agrego: " << nuevoString << endl;
				//this->tabla.Imprimir(cout);
			}
			if(limpiarTabla || (this->tabla.hayQueLimpiar() && (this->tabla.getContextoActual() == charLeidoAnterior))){
				this->tabla.setContexto(charLeidoAnterior);
				this->tabla.obtenerCodigoLimpieza(codigoGuardado);
				//cout << "Nuevo string sin terminar " << charLeido << endl;
				//cout << "Codigo de limpieza de " << codigoGuardado->tamanio << " bits" << endl;
				codigoTipoEscritura->bits = CODIGO_CONTEXTO;
				this->imprimirCodigo(codigoTipoEscritura, codigoGuardado,bufferEscritura);
				if(!limpiarTabla){
					this->tabla.limpiar();
				}
				limpiarTabla = false;
			}
			this->tabla.setContexto(charLeidoAnterior);
			stringLeido = "";

		} else {
			//cout << "nuevoString: " << nuevoString << endl;
			if(nuevoString.length() == 1){
				this->setCadenaFromChar(codigoGuardado,nuevoString.at(0));
				codigoTipoEscritura->bits = CODIGO_LITERAL;
			} else {
				this->tabla.getBits(nuevoString,codigoGuardado);
				codigoTipoEscritura->bits = CODIGO_CONTEXTO;
			}
			stringLeido = nuevoString;
			bufferLectura->leer(cadenaLeida);
			charLeidoAnterior = charLeido;
			charLeido = cadenaLeida->getAsChar();


			if (bufferLectura->esFinDeArchivo()){
//				cout << "2) el ultimo codigo que imprimo es: " <<codigoGuardado->bits<<endl;
				this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);

				codigoTipoEscritura->bits = CODIGO_LITERAL;
				this->setCadenaFromChar(codigoGuardado,charLeido);
	//			cout << "EL ULTIMO QUE PONGO ES: " << charLeido << " " << codigoGuardado->bits << endl;
				this->imprimirCodigo(codigoTipoEscritura,codigoGuardado,bufferEscritura);
		//		cout << "ya no deberia imprimir nada mas (excepto el fin de archivo)" << endl;
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
	BufferLectura* bufferLectura = new BufferLectura(TAMANIO_BUFFER, false);
	BufferEscritura* bufferEscritura = new BufferEscritura(TAMANIO_BUFFER, false);
	bufferLectura->crearStream(archivoEntrada);
	if(!bufferLectura->estaAbierto()){
		//No existe el archivo
		return 1;
	}
	bufferEscritura->crearStream(archivoSalida);

	CadenaDeBits *tipoCodigo = new CadenaDeBits(TAMANIO_TIPO_CODIGO,0);
	CadenaDeBits *nuevoCodigo = new CadenaDeBits(0,0);
	bool esPrimerChar = true;
	bool esLiteral = false;
	bool anteriorEsLiteral = false;
	bool leidoUnCodigoDeTabla = false;
	bool esCodigoLimpieza = false;
	bool casoEspecial = false; // Para el caso que la cadena empieza y termina con el mismo char
	size_t tamanioALeer;
	char contextoActual;
	char contextoAnterior;
	string nuevoString = ""; // String que contiene lo anteriormente descomprimido
	string descompresion = "";
	// Leo el primer char y lo pongo como contexto
	if(!bufferLectura->esFinDeArchivo()){
		bufferLectura->leer(tipoCodigo);
		esLiteral = (tipoCodigo->bits == CODIGO_LITERAL);
		if (tipoCodigo->bits == CODIGO_LITERAL){
			tamanioALeer = TAMANIO_BYTE;
			nuevoCodigo->tamanio = tamanioALeer;
			bufferLectura->leer(nuevoCodigo);
			nuevoString = this->getStringFromCode(nuevoCodigo->bits);
			this->imprimirCadena(nuevoString,bufferEscritura);
			this->tabla.setContexto(nuevoString.at(0));
			contextoActual = nuevoString.at(0);
			//cout << "Bits leidos " << nuevoCodigo->tamanio + 1 << endl;
			//cout << "Leido un char: " << nuevoString << endl;
		}
		bufferLectura->leer(tipoCodigo);
	}
	while(!bufferLectura->esFinDeArchivo()){
		esCodigoLimpieza = false;
		if(tipoCodigo->bits == CODIGO_LITERAL){ // Leo un char
			tamanioALeer = TAMANIO_BYTE;
			nuevoCodigo->tamanio = tamanioALeer;
			bufferLectura->leer(nuevoCodigo);
			descompresion = this->getStringFromCode(nuevoCodigo->bits);
			//cout << "Bits leidos " << nuevoCodigo->tamanio + 1 << endl;
			//cout << "Leido un char: " << descompresion << endl;
		} else { // Leo un codigo de tabla
			tamanioALeer = this->tabla.getCantidadBitsTabla();
			int maxValor = (pow(2.0,(int)(tamanioALeer)));
			//cout << "Contexto: " << this->tabla.getContextoActual() << " Last code:" << this->tabla.getLastCode() << endl;
			if ((contextoActual == contextoAnterior) && (maxValor <= (this->tabla.getLastCode() + 1))){
				tamanioALeer++;
				//cout << "Bits supuestos " << tamanioALeer + 2 << endl;
			}
			nuevoCodigo->tamanio = tamanioALeer;
			bufferLectura->leer(nuevoCodigo);
			esCodigoLimpieza = this->tabla.esCodigoLimpieza(nuevoCodigo);
			//cout << "Bits leidos " << nuevoCodigo->tamanio + 1 << endl;
			//cout << "Leido codigo: " << nuevoCodigo->bits << endl;
			if(esCodigoLimpieza){
				this->tabla.setContexto(contextoAnterior);
				this->tabla.limpiar();
				//cout << "Contexto: " << this->tabla.getContextoActual() << " Tabla limpiada." << endl;
				this->tabla.setContexto(contextoActual);
				//cout << "Codigo de limpieza de " << nuevoCodigo->tamanio << " bits" << endl;
				casoEspecial = true;
				//casoEspecial = ((tamanioALeer == this->tabla.getCantidadBitsTabla()) || (contextoActual != contextoAnterior));
				nuevoString = nuevoString.substr(nuevoString.size() - 1);
			} else {
				//this->tabla.Imprimir(cout);
				if(this->tabla.exists(*nuevoCodigo)){
					//cout << "String Existia! " << endl;
					descompresion = this->tabla.getString(*nuevoCodigo);
					//cout << "Leido un string: " << descompresion << endl;
				} else {
					descompresion = this->completarCadena(nuevoString);
					//cout << "Leido un string: " << descompresion << " desde el string " << nuevoString << endl;
					//cout << "String no existia" << endl;
					//cout << "Contexto: " << contextoActual <<" Agrego: " << descompresion << endl;
					this->tabla.agregarString(descompresion);
					//this->tabla.Imprimir(cout);
					casoEspecial = true;
				}
				//cout << "Leido un string: " << descompresion << endl;
			}
		}
		if(!esCodigoLimpieza){
			//cout << "Escribo: " << descompresion << endl;
			this->imprimirCadena(descompresion,bufferEscritura);
			if(esPrimerChar){ // Caso especial: sin contexto anterior
				esPrimerChar = false;
			} else {
				if(!casoEspecial){
					this->tabla.setContexto(contextoAnterior);
					//cout << "Contexto: " << contextoAnterior <<" Agrego: " << nuevoString + descompresion.at(0) << endl;
					this->tabla.agregarString(nuevoString + descompresion.at(0));
					//this->tabla.Imprimir(cout);
				}
				casoEspecial = false;
			}
			anteriorEsLiteral = esLiteral;
			nuevoString = descompresion;
			descompresion = "";
			contextoAnterior = contextoActual;
			contextoActual = nuevoString.at(nuevoString.length() - 1);
			this->tabla.setContexto(contextoActual);
		}
		bufferLectura->leer(tipoCodigo);
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
	//cout << "ESCRIBO: " << tipo->bits << ", y uso " << codigo->tamanio << " bits para el codigo " << codigo->bits << endl;
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
		//cout << "ESCRIBO: " << caracter << endl;
	}
	delete paraGuardar;
}


void LZCtx::setCadenaFromChar(CadenaDeBits* cadena, char caracter){
	unsigned char caracterAux = (unsigned char)caracter;
	cadena->tamanio = TAMANIO_BYTE;
	cadena->bits = (unsigned int)caracterAux;
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
	cadena = cadena + cadena.at(0);
	return cadena;
}

