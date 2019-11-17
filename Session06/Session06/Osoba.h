#ifndef OSOBA_H
#define OSOBA_H

#include <string>
#include <iostream>

#include "Datum.h"
#include "Adresa.h"

struct Osoba {
private:
	std::string _jmeno;
	std::string _prijmeni;
	Adresa* _trvaleBydliste;
	Datum* _datumNarozeni;
public:
	Osoba(){};
	Osoba(std::string jmeno, std::string prijmeni, Adresa* trvaleBydliste, Datum* datumNarozeni);
	std::string GetJmeno() const;
	void SetJmeno(std::string jmeno);
	std::string GetPrijmeni() const;
	void SetPrijmeni(std::string prijmeni);
	Adresa GetAdresa() const;
	void SetAdresa(Adresa* trvaleBydliste);
	Datum GetDatum() const;
	void SetDatum(Datum* datumNarozeni);
};

std::ostream& operator<<(std::ostream& os, const Osoba& osoba);
std::istream& operator>>(std::istream& is, Osoba& osoba);

#endif // !OSOBA_H
