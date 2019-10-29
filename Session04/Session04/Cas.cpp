#include "Cas.h"
#include <string>
#include <stdexcept>

using namespace std;

Cas::Cas(int hodiny, int minuty, int sekundy) {
	this->_hodiny = hodiny;
	this->_minuty = minuty;
	this->_sekundy = sekundy;
}

std::string Cas::toString() const {
	return to_string(_hodiny) + ":" + to_string(_minuty) + ":" + to_string(_sekundy);
}

int Cas::compareTo(IComparable* obj) const {
	Cas* casObj = dynamic_cast<Cas*>(obj);

	if (!casObj)
	{
		throw invalid_argument("Invalid argument");
	}

	if (_hodiny > casObj->_hodiny)
	{
		return 1;
	}

	if (_hodiny < casObj->_hodiny)
	{
		return -1;
	}

	if (_minuty > casObj->_minuty)
	{
		return 1;
	}

	if (_minuty < casObj->_minuty)
	{
		return -1;
	}

	if (_sekundy > casObj->_sekundy)
	{
		return 1;
	}

	if (_sekundy < casObj->_sekundy)
	{
		return -1;
	}

	return 0;
}