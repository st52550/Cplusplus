#pragma once
#ifndef POKLADNA_H

#include "Uctenka.h"

struct Pokladna {
private:
	Uctenka* poleUctenek;
	int pocetVydanychUctenek;
	static int citacId;
public:
	Pokladna();
	~Pokladna();

	Uctenka& VystavUctenku(double castka, double dph);
	Uctenka& DejUctenku(int cisloUctenky);
	double DejCastku() const;
	double DejCastkuVcDph() const;
};
#endif // !POKLADNA_H

