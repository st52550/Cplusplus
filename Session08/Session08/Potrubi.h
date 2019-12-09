#ifndef POTRUBI_H
#define POTRUBI_H

#include "IPotrubi.h"
#include "JVZPrvek.h"
#include "NicPrvek.h"
#include "SJPrvek.h"
#include "SJVZPrvek.h"
#include "VZPrvek.h"

struct Potrubi : IPotrubi {
private:
	int rozmer;
	APotrubniPrvek*** potrubi;
public:
	Potrubi(int rozmer, APotrubniPrvek*** potrubi);
	~Potrubi();
	APotrubniPrvek* DejPrvek(int x, int y) const;
	bool JePotrubiOk() const;
};

#endif // !POTRUBI_H

