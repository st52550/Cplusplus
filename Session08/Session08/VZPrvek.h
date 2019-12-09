#ifndef VZPRVEK_H
#define VZPRVEK_H

#include "APotrubniPrvek.h"

struct VZPrvek : APotrubniPrvek {
	bool JeKorektneZapojen(const IPotrubi* potrubi) const;
};

#endif // !VZPRVEK_H

