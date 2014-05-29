/*
 * TablaDeContextos.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef TABLADECONTEXTOS_H_
#define TABLADECONTEXTOS_H_

#include "InterfazTabla.h"
#include <map>
#include "Tabla.h"

class TablaDeContextos: public InterfazTabla {
public:
	TablaDeContextos();
	virtual ~TablaDeContextos();
	void setContexto(char contexto);
	virtual CadenaDeBits agregarString(string cadena);
	virtual void getBits(string cadena,CadenaDeBits* cadenaDeBits);
	virtual string getString(CadenaDeBits bits);
	virtual bool exists(string cadena);
	virtual bool exists(CadenaDeBits bits);
	virtual void limpiar();
	virtual bool hayQueLimpiar();
	virtual size_t getCantidadBitsTabla();
	int getLastCode();
	char getContextoActual();

private:
	map<char,Tabla*> mapaDeContextos;
	char contexto;
	bool contextoSeteado;

	bool tengoContexto();
	Tabla* getTablaActual();

//	string getChar(CadenaDeBits bits);

};



#endif /* TABLADECONTEXTOS_H_ */
