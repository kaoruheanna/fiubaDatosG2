/*
 * LZContextos.h
 *
 *  Created on: May 25, 2014
 *      Author: kaoru
 */

#ifndef LZCONTEXTOS_H_
#define LZCONTEXTOS_H_

#include "Compresor.h"
#include "CadenaDeBits.h"
#include "Constantes.h"
#include "BufferLectura.h"
#include "BufferEscritura.h"
#include "TablaDeContextos.h"
#include <map>
#include <iostream>
#include <fstream>

class LZContextos: public Compresor {
public:
	LZContextos();
	virtual ~LZContextos();

private:
	TablaDeContextos tabla;

	void imprimirCodigo(CadenaDeBits* tipo,CadenaDeBits* codigo, BufferEscritura* bufferEscritura);
	void setCadenaFromChar(CadenaDeBits* cadena, char caracter);
};

#endif /* LZCONTEXTOS_H_ */
