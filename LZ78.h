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
#include "BufferLectura.h"
#include "BufferEscritura.h"
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class LZ78 : public Compresor{
public:
	LZ78();
	virtual ~LZ78();
	virtual int comprimir(string archivoEntrada, string archivoSalida);
	virtual int descomprimir(string archivoEntrada, string archivoSalida);

protected:
	virtual void ImprimirEn(ostream & out) const;

private:
	Tabla tabla;
	ofstream fileTabla;
	ofstream fileSalida;

	string completarCadena(string cadena);
	void cargarTabla();
	void imprimirCadena(string cadena, BufferEscritura* bufferEscritura);
	void imprimirCodigo(CadenaDeBits* codigo, BufferEscritura* bufferEscritura);
	void imprimirTabla(string cadena);
};

#endif /* LZ78_H_ */
