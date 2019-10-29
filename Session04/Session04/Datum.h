#ifndef DATUM_H
#define DATUM_H

#include "IComparable.h"
#include <string>

struct Datum : public IComparable {
private:
	int _den;
	int _mesic;
	int _rok;
public:
	Datum(int den, int mesic, int rok);
	virtual std::string toString() const override;
	virtual int compareTo(IComparable* obj) const override;
};

#endif // !DATUM_H

