#ifndef APOTRUBNIPRVEK_H
#define APOTRUBNIPRVEK_H

#include "IPotrubi.h"

struct APotrubniPrvek {
	virtual ~APotrubniPrvek() { }
	virtual bool JeKorektneZapojen(const IPotrubi* potrubi) const = 0;
	int _x;
	int _y;
};

#endif // !APOTRUBNIPRVEK_H

