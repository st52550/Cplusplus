#include "Adresa.h"

using namespace std;

Adresa::Adresa() { _mesto = _ulice = "", _psc = 0; };

Adresa::Adresa(string ulice, string mesto, int psc) {
	this->_ulice = ulice;
	this->_mesto = mesto;
	this->_psc = psc;
}

string Adresa::GetUlice() const {
	return _ulice;
}

void Adresa::SetUlice(string ulice) {
	this->_ulice = ulice;
}

string Adresa::GetMesto() const {
	return _mesto;
}

void Adresa::SetMesto(string mesto) {
	this->_mesto = mesto;
}

int Adresa::GetPsc() const {
	return _psc;
}

void Adresa::SetPsc(int psc) {
	this->_psc = psc;
}

ostream& operator<<(ostream& os, const Adresa& adresa) {
	os << adresa.GetUlice() << ";" << adresa.GetMesto() << ";" << adresa.GetPsc();
	return os;
}

istream& operator>>(istream& is, Adresa& adresa) {
	string mesto;
	string ulice;
	int psc;

	is >> mesto;
	is >> ulice;
	is >> psc;

	adresa.SetMesto(mesto);
	adresa.SetUlice(ulice);
	adresa.SetPsc(psc);

	return is;
}