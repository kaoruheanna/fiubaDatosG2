/*
 * Tabla.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef TABLA_H_
#define TABLA_H_

#include "InterfazTabla.h"
#include <vector>

class Tabla : public InterfazTabla{
public:
	Tabla();
	virtual ~Tabla();
	// Metodos de InterfazTabla
//	virtual CadenaDeBits getBits(string cadena);
	virtual void getBits(string cadena,CadenaDeBits* cadenaDeBits);
	virtual string getString(CadenaDeBits bits);
	virtual CadenaDeBits agregarString(string cadena);
	virtual bool exists(string cadena);
	virtual bool exists(CadenaDeBits bits);
	virtual void limpiar();
	virtual bool hayQueLimpiar();
	virtual size_t getCantidadBitsTabla();
	int getLastCode();
	void Imprimir(ostream& out);
protected:
	virtual void ImprimirEn(ostream& out) const;
private:
	int lastCode;
	size_t cantidadBitsTabla;
	vector<string>* tabla;
};

#endif /* TABLA_H_ */
