#include "Osoba.h"

using namespace std;
using namespace Entity;

Osoba::Osoba(std::string jmeno, std::string telefon, int id) {
	this->_jmeno = jmeno;
	this->_telefon = telefon;
	this->_id = id;
}

string Osoba::GetJmeno() const {
	return _jmeno;
}

string Osoba::GetTelefon() const {
	return _telefon;
}

int Osoba::GetId() const {
	return _id;
}