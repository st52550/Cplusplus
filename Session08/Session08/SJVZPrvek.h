#ifndef SJVZPRVEK_H
#define SJVZPRVEK_H

#include "APotrubniPrvek.h"

struct SJVZPrvek : APotrubniPrvek {
	bool JeKorektneZapojen(const IPotrubi* potrubi) const;
};

#endif // !SJVZPRVEK_H

