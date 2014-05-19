/*
 * TablaDeContextos.h
 *
 *  Created on: Apr 27, 2014
 *      Author: kaoru
 */

#ifndef TABLADECONTEXTOS_H_
#define TABLADECONTEXTOS_H_

#include "InterfazTabla.h"

class TablaDeContextos: public InterfazTabla {
public:
	TablaDeContextos();
	virtual ~TablaDeContextos();
	void setContexto(char contexto);

private:
	map<char,Tabla*> mapaDeContextos;
	char contexto;
//	string getChar(CadenaDeBits bits);

};



#endif /* TABLADECONTEXTOS_H_ */
