#include "Datum.h"

using namespace std;

Datum::Datum() { _den = _mesic = _rok = 0; };

Datum::Datum(int den, int mesic, int rok) {
	this->_den = den;
	this->_mesic = mesic;
	this->_rok = rok;
}

int Datum::GetDen() const {
	return _den;
}

void Datum::SetDen(int den) {
	this->_den = den;
}

int Datum::GetMesic() const {
	return _mesic;
}

void Datum::SetMesic(int mesic) {
	this->_mesic = mesic;
}

int Datum::GetRok() const {
	return _rok;
}

void Datum::SetRok(int rok) {
	this->_rok = rok;
}

ostream& operator<<(ostream& os, const Datum& datum) {
	os << datum.GetDen() << "." << datum.GetMesic() << "." << datum.GetRok();
	return os;
}
istream& operator>>(istream& is, Datum& datum) {
	int den;
	int mesic;
	int rok;

	is >> den;
	is >> mesic;
	is >> rok;

	datum.SetDen(den);
	datum.SetMesic(mesic);
	datum.SetRok(rok);

	return is;
}