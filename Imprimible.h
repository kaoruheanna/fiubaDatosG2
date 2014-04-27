#ifndef IMPRIMIBLE_H
#define IMPRIMIBLE_H

#include <ostream>
#include <iostream>

using namespace std;

class Imprimible {
protected:
	virtual void ImprimirEn(ostream& out) const = 0;

public:
	Imprimible(){}
	virtual ~Imprimible(){}

	friend ostream& operator<<(ostream& out, Imprimible const & reg);
	};


	inline ostream& operator<<(ostream& out, Imprimible const & reg){
	reg.ImprimirEn(out);
	return out;
}

#endif
