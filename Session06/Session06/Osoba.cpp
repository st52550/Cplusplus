#include "Osoba.h"
#include "Datum.h"
#include "Adresa.h"

using namespace std;

Osoba::Osoba(string jmeno, string prijmeni, Adresa* trvaleBydliste, Datum* datumNarozeni) {
	this->_jmeno = jmeno;
	this->_prijmeni = prijmeni;
	this->_trvaleBydliste = trvaleBydliste;
	this->_datumNarozeni = datumNarozeni;
}

string Osoba::GetJmeno() const {
	return _jmeno;
}

void Osoba::SetJmeno(string jmeno) {
	this->_jmeno = jmeno;
}

string Osoba::GetPrijmeni() const {
	return _prijmeni;
}

void Osoba::SetPrijmeni(string prijmeni) {
	this->_prijmeni = prijmeni;
}

Adresa Osoba::GetAdresa() const {
	return *_trvaleBydliste;
}

void Osoba::SetAdresa(Adresa* trvaleBydliste) {
	this->_trvaleBydliste = trvaleBydliste;
}

Datum Osoba::GetDatum() const {
	return *_datumNarozeni;
}

void Osoba::SetDatum(Datum* datumNarozeni) {
	this->_datumNarozeni = datumNarozeni;
}

ostream& operator<<(ostream& os, const Osoba& osoba) {
	os << osoba.GetPrijmeni() << ";" << osoba.GetJmeno() << ";" << osoba.GetDatum() << ";" << osoba.GetAdresa();
	return os;
}

istream& operator>>(istream& is, Osoba& osoba) {
	string jmeno;
	string prijmeni;
	Adresa adresa;
	Datum datum;

	is >> jmeno;
	is >> prijmeni;
	is >> adresa;
	is >> datum;

	osoba.SetJmeno(jmeno);
	osoba.SetPrijmeni(prijmeni);
	osoba.SetAdresa(&adresa);
	osoba.SetDatum(&datum);

	return is;
}