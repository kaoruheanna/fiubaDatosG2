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
};

#endif /* TABLADECONTEXTOS_H_ */
