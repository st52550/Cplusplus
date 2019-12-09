#ifndef SJPRVEK_H
#define SJPRVEK_H

#include "APotrubniPrvek.h"

struct SJPrvek : APotrubniPrvek {
	bool JeKorektneZapojen(const IPotrubi* potrubi) const;
};

#endif // !SJPRVEK_H

