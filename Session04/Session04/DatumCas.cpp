#include "DatumCas.h"
#include <stdexcept>

using namespace std;

DatumCas::DatumCas(Datum *datum, Cas *cas) {
	this->_datum = datum;
	this->_cas = cas;
}

std::string DatumCas::toString() const {
	return _datum->toString() + " " + _cas->toString();
}

int DatumCas::compareTo(IComparable* obj) const {
	DatumCas* datumCasObj = dynamic_cast<DatumCas*>(obj);

	if (!datumCasObj)
	{
		throw invalid_argument("Invalid argument");
	}

	if (_datum->compareTo(datumCasObj->_datum) > 0)
	{
		return 1;
	}
	
	if (_datum->compareTo(datumCasObj->_datum) < 0)
	{
		return -1;
	}

	if (_cas->compareTo(datumCasObj->_cas) > 0)
	{
		return 1;
	}

	if (_cas->compareTo(datumCasObj->_cas) < 0)
	{
		return -1;
	}

	return 0;
}