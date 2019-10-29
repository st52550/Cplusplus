#include "Datum.h"
#include <stdexcept>

using namespace std;

Datum::Datum(int den, int mesic, int rok) {
	this->_den = den;
	this->_mesic = mesic;
	this->_rok = rok;
}

std::string Datum::toString() const {
	return to_string(_den) + ". " + to_string(_mesic) + ". " + to_string(_rok);
}

int Datum::compareTo(IComparable* obj) const {
	Datum* datObj = dynamic_cast<Datum*>(obj);

	if (!datObj)
	{
		throw invalid_argument("Invalid argument");
	}

	if (_rok > datObj->_rok)
	{
		return 1;
	}

	if (_rok < datObj->_rok)
	{
		return -1;
	}

	if (_mesic > datObj->_mesic)
	{
		return 1;
	}

	if (_mesic < datObj->_mesic)
	{
		return -1;
	}

	if (_den > datObj->_den)
	{
		return 1;
	}

	if (_den < datObj->_den)
	{
		return -1;
	}

	return 0;
}