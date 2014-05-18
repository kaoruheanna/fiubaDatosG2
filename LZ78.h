/*
 * LZ78.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef LZ78_H_
#define LZ78_H_

#include "Compresor.h"
#include "Tabla.h"
#include "CadenaDeBits.h"
#include "Constantes.h"
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class LZ78 : public Compresor{
public:
	LZ78();
	virtual ~LZ78();
	virtual int comprimir(string path);
	virtual int descomprimir(string path);

protected:
	virtual void ImprimirEn(ostream & out) const;
	//virtual bool agregarCadenaATabla(string cadena);

private:
	Tabla tabla;
	//int lastCode;
	//int cantDeBits;
	ofstream fileTabla;
	ofstream fileSalida;

	string completarCadena(string cadena);
	void cargarTabla();
	//int getCodigoCadena(string cadena);
	//string getCadenaCodigo(int codigo);
	void imprimirCadena(string cadena);
	void imprimirCodigo(int codigo);
	void imprimirTabla(string cadena);
	int getNextCodigo(string::iterator &iterador);
	int binToInt(string codigoBinario);
//	string getNextChar();
//	string getCurrentChar();
//	bool isEndOfString();
};

#endif /* LZ78_H_ */
