#ifndef JVZPRVEK_H
#define JVZPRVEK_H

#include "APotrubniPrvek.h"

struct JVZPrvek : APotrubniPrvek {
	bool JeKorektneZapojen(const IPotrubi* potrubi) const;
};
#endif // !JVZPRVEK_H

