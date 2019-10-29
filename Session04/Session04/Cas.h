#ifndef CAS_H
#define CAS_H

#include "IComparable.h"
#include <string>

struct Cas : public IComparable {
private:
	int _hodiny;
	int _minuty;
	int _sekundy;
public:
	Cas(int hodiny, int minuty, int sekundy);
	virtual std::string toString() const override;
	virtual int compareTo(IComparable* obj) const override;
};

#endif // !CAS_H
