#ifndef NICPRVEK_H
#define NICPRVEK_H

#include "APotrubniPrvek.h"

struct NicPrvek : APotrubniPrvek {
	bool JeKorektneZapojen(const IPotrubi* potrubi) const;
};

#endif // !NICPRVEK_H

