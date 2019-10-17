#ifndef POHYBLIVY_OBJEKT_H
#define POHYBLIVY_OBJEKT_H

#include "Objekt.h"

struct PohyblivyObjekt : public Objekt {
private:
	double uhelNatoceni;
public:
	PohyblivyObjekt(int id, double uhelNatoceni);
	double GetUhelNatoceni() const;
	void SetUhelNatoceni(double uhelNatoceni);
};

#endif // !POHYBLIVY_OBJEKT_H
