#include "Pokladna.h"
#include "Uctenka.h"
#include <stdexcept>

#define POCET_UCTENEK 10

int Pokladna::citacId = 1000;

Pokladna::Pokladna() {
	pocetVydanychUctenek = 0;
	poleUctenek = new Uctenka[POCET_UCTENEK];
}

Pokladna::~Pokladna() {
	delete[] poleUctenek;
}

Uctenka& Pokladna::VystavUctenku(double castka, double dph) {
	if (pocetVydanychUctenek > POCET_UCTENEK)
	{
		throw std::overflow_error("Prekrocen limit.");
	}

	poleUctenek[pocetVydanychUctenek].SetCisloUctenky(citacId);
	poleUctenek[pocetVydanychUctenek].SetCastka(castka);
	poleUctenek[pocetVydanychUctenek].SetDph(dph);

	pocetVydanychUctenek++;
	citacId++;

	return poleUctenek[pocetVydanychUctenek];
}

Uctenka& Pokladna::DejUctenku(int cisloUctenky) {
	for (size_t i = 0; i < pocetVydanychUctenek; i++)
	{
		if (poleUctenek[i].GetCisloUctenky() == cisloUctenky)
		{
			return poleUctenek[i];
		}
	}

	return poleUctenek[0];
}

double Pokladna::DejCastku() const {
	double suma = 0;

	for (size_t i = 0; i < pocetVydanychUctenek; i++)
	{
		suma += poleUctenek[i].GetCastka();
	}

	return suma;
}

double Pokladna::DejCastkuVcDph() const {
	double suma = 0;

	for (size_t i = 0; i < pocetVydanychUctenek; i++)
	{
		suma += (poleUctenek[i].GetCastka() * (1 + poleUctenek[i].GetDph()));
	}

	return suma;
}