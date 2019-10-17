#ifndef STATICKY_OBJEKT_H
#define STATICKY_OBJEKT_H

#include  "Objekt.h"

struct StatickyObjekt : public Objekt {
public:
	enum class TypPrekazky {
		Skala,
		MalaRostlina,
		VelkaRostlina
	};
private:
	TypPrekazky typPrekazky;
public:
	StatickyObjekt(int id, TypPrekazky typPrekazky);
	TypPrekazky GetTypPrekazky() const;
};

#endif // !STATICKY_OBJEKT_H

