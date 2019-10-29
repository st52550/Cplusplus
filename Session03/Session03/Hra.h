#ifndef HRA_H
#define HRA_H

#include "Objekt.h"
#include "PohyblivyObjekt.h"

struct Hra {
private:
	Objekt** objekty;
public:
	~Hra();
	void vlozObjekt(Objekt* o);
	int* najdiIdStatickychObjektu(double xmin, double xmax, double ymin, double ymax, int* pocetObjektu);
	PohyblivyObjekt** najdiPohybliveObjektyVOblasti(double x, double y, double r, int* pocetObjektu);
	PohyblivyObjekt** najdiPohybliveObjektyVOblasti(double x, double y, double r, double umin, double umax, int* pocetObjektu);
	void vypisObjekty();
};
#endif // !HRA_H
