/*
 * LZ78.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef LZ78_H_
#define LZ78_H_

#include "Compresor.h"
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class LZ78 : public Compresor{
public:
	LZ78();
	virtual ~LZ78();
	virtual int comprimir(string &path);
	virtual int descomprimir(string &path);

protected:
	virtual void ImprimirEn(ostream & out) const;
	virtual bool agregarCadenaATabla(string cadena);

private:
	map<string,int> table;
	int lastCode;
	int cantDeBits;
	ofstream fileTabla;
	ofstream fileSalida;

	string completarCadena(string cadena);
	//seguramente dsp haya que cambiar esto por "cadenaDeBits"
	int getCodigoCadena(string cadena);
	string getCadenaCodigo(int codigo);
	void imprimirCadena(string cadena);
	void imprimirCodigo(int codigo);
	int getNextCodigo(string::iterator &iterador);
	int binToInt(string codigoBinario);
//	string getNextChar();
//	string getCurrentChar();
//	bool isEndOfString();
};

#endif /* LZ78_H_ */
