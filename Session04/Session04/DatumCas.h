#ifndef DATUMCAS_H
#define DATUMCAS_H

#include "IComparable.h"
#include "Cas.h"
#include "Datum.h"

struct DatumCas : public IComparable {
private:
	Datum* _datum;
	Cas* _cas;
public:
	DatumCas(Datum *datum, Cas *cas);
	virtual std::string toString() const override;
	virtual int compareTo(IComparable* obj) const override;
};

#endif // !DATUMCAS_H

