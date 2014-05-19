/*
 * BufferLectura.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef BUFFERLECTURA_H_
#define BUFFERLECTURA_H_

#include "Buffer.h"

class BufferLectura : public Buffer {
public:
	BufferLectura(size_t tamanio, bool esCompresion);
	virtual ~BufferLectura();

	void leer(CadenaDeBits* cadena);
	bool esFinDeArchivo();

	virtual void crearStream(string archivo);
	virtual void cerrar();

	virtual void ImprimirEn(ostream& out) const;
private:
	ifstream* _file;
	size_t posFinDeArchivo;
	void actualizarBuffer();
};

#endif /* BUFFERLECTURA_H_ */
