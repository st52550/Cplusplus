#ifndef HRA_H
#define HRA_H

#include "Objekt.h"
#include "PohyblivyObjekt.h"

struct Hra {
private:
	Objekt** objekty;
public:
	void vlozObjekt(Objekt* o);
	int* najdiIdStatickychObjektu(double xmin, double xmax, double ymin, double ymax);
	PohyblivyObjekt** najdiPohybliveObjektyVOblasti(double x, double y, double r);
	PohyblivyObjekt** najdiPohybliveObjektyVOblasti(double x, double y, double r, double umin, double umax);
	void vypisObjekty();
};
#endif // !HRA_H
