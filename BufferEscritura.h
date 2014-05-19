/*
 * BufferEscritura.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef BUFFERESCRITURA_H_
#define BUFFERESCRITURA_H_

#include "Buffer.h"

class BufferEscritura: public Buffer {
public:
	BufferEscritura(size_t tamanio, bool esCompresion);
	virtual ~BufferEscritura();

	void escribir(const CadenaDeBits* cadena);

	virtual void crearStream(string archivo);
	virtual void cerrar();

	virtual void ImprimirEn(ostream& out) const;
private:
	ofstream* _file;

	void agregarFinDeArchivo();
	void guardarEnDisco();
};

#endif /* BUFFERESCRITURA_H_ */
