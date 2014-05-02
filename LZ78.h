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
	virtual int descomprimir(string path);

protected:
	virtual void ImprimirEn(ostream & out) const;
	virtual bool agregarCadenaATabla(string cadena);

private:
	map<string,int> table;
	int lastCode;
	ofstream fileTabla;
	ofstream fileSalida;

	//seguramente dsp haya que cambiar esto por "cadenaDeBits"
	map<string,int>::iterator getCodigoCadena(string cadena);
	void imprimirCadena(string cadena);
//	string getNextChar();
//	string getCurrentChar();
//	bool isEndOfString();
};

#endif /* LZ78_H_ */
