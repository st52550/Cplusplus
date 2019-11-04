#include "Hra.h"
#include "StatickyObjekt.h"

#include <iostream>

using namespace std;

static int citacObjektu = 0;

Hra::~Hra() {
	for (size_t i = 0; i < citacObjektu; i++)
	{
		delete objekty[i];
	}

	delete[] objekty;
}

void Hra::vlozObjekt(Objekt* o) {
	if (citacObjektu != 0) {
		Objekt** kopiePole = new Objekt * [citacObjektu + 1];

		for (int i = 0; i < citacObjektu; i++)
		{
			kopiePole[i] = objekty[i];
		}

		kopiePole[citacObjektu] = o;

		delete[] objekty;
		objekty = new Objekt * [citacObjektu + 1];
		objekty = kopiePole;
		citacObjektu++;
	}
	else {
		objekty = new Objekt * [1];
		objekty[0] = o;
		citacObjektu++;
	}
}

int* Hra::najdiIdStatickychObjektu(double xmin, double xmax, double ymin, double ymax, int *pocetObjektu) {
	int pocetShod = 0;

	for (int i = 0; i < citacObjektu; i++)
	{
		if (dynamic_cast<StatickyObjekt*>(objekty[i])){
			if ((objekty[i]->GetX() >= xmin && objekty[i]->GetY() <= xmax) &&
				(objekty[i]->GetY() >= ymin && objekty[i]->GetY() <= ymax))
			{
				pocetShod++;
			}
		}
	}

	int* poleNalezenychObjektu = new int[pocetShod];
	*pocetObjektu = pocetShod;
	int citac = 0;

	for (int i = 0; i < citacObjektu; i++)
	{
		if (dynamic_cast<StatickyObjekt*>(objekty[i])) {
			if ((objekty[i]->GetX() >= xmin && objekty[i]->GetY() <= xmax) &&
				(objekty[i]->GetY() >= ymin && objekty[i]->GetY() <= ymax))
			{
				poleNalezenychObjektu[citac] = dynamic_cast<StatickyObjekt*>(objekty[i])->GetId();
				citac++;
			}
		}
	}

	return poleNalezenychObjektu;
}

PohyblivyObjekt** Hra::najdiPohybliveObjektyVOblasti(double x, double y, double r, int* pocetObjektu) {
	int pocetShod = 0;

	for (int i = 0; i < citacObjektu; i++)
	{
		if (dynamic_cast<PohyblivyObjekt*>(objekty[i])) {
			if ((objekty[i]->GetX() * objekty[i]->GetX()) + (objekty[i]->GetY() * objekty[i]->GetY()) <= r*r)
			{
				pocetShod++;
			}
		}
	}
	
	PohyblivyObjekt** polePohyblivychObjektu = nullptr;
	*pocetObjektu = pocetShod;
	
	if (pocetShod > 0)
	{
		polePohyblivychObjektu = new PohyblivyObjekt * [pocetShod];
		int citac = 0;

		for (int i = 0; i < citacObjektu; i++)
		{
			if (dynamic_cast<PohyblivyObjekt*>(objekty[i])) {
				if ((objekty[i]->GetX() * objekty[i]->GetX()) + (objekty[i]->GetY() * objekty[i]->GetY()) <= r * r)
				{
					polePohyblivychObjektu[citac] = dynamic_cast<PohyblivyObjekt*>(objekty[i]);
					citac++;
				}
			}
		}
	}

	return polePohyblivychObjektu;
}

PohyblivyObjekt** Hra::najdiPohybliveObjektyVOblasti(double x, double y, double r, double umin, double umax, int* pocetObjektu) {
	int pocetShod = 0;

	for (int i = 0; i < citacObjektu; i++)
	{
		if (dynamic_cast<PohyblivyObjekt*>(objekty[i])) {
			if (
				((objekty[i]->GetX() * objekty[i]->GetX()) + (objekty[i]->GetY() * objekty[i]->GetY()) <= r * r)
				  && (dynamic_cast<PohyblivyObjekt*>(objekty[i])->GetUhelNatoceni() >= umin &&
					  dynamic_cast<PohyblivyObjekt*>(objekty[i])->GetUhelNatoceni() <= umax)
				)
			{
				pocetShod++;
			}
		}
	}

	PohyblivyObjekt** polePohyblivychObjektu = nullptr;
	*pocetObjektu = pocetShod;

	if (pocetShod > 0)
	{
		polePohyblivychObjektu = new PohyblivyObjekt * [pocetShod];
		int citac = 0;

		for (int i = 0; i < citacObjektu; i++)
		{
			if (dynamic_cast<PohyblivyObjekt*>(objekty[i])) {
				if (
					((objekty[i]->GetX() * objekty[i]->GetX()) + (objekty[i]->GetY() * objekty[i]->GetY()) <= r * r)
					&& (dynamic_cast<PohyblivyObjekt*>(objekty[i])->GetUhelNatoceni() >= umin &&
						dynamic_cast<PohyblivyObjekt*>(objekty[i])->GetUhelNatoceni() <= umax)
					)
				{
					polePohyblivychObjektu[citac] = dynamic_cast<PohyblivyObjekt*>(objekty[i]);
					citac++;
				}
			}
		}
	}
	return polePohyblivychObjektu;
}

void Hra::vypisObjekty() {
	cout << "Objekty v poli:" << endl;

	for (size_t i = 0; i < citacObjektu; i++)
	{
		cout << "ID: " << objekty[i]->GetId() << " x: " << objekty[i]->GetX() << " y: " << objekty[i]->GetY() << endl;
	}
}