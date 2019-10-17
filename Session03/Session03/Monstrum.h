#ifndef MONSTRUM_H
#define MONSTRUM_H

#include "PohyblivyObjekt.h"

struct Monstrum : public PohyblivyObjekt {
private:
	int hp;
	int maxHp;
public:
	Monstrum(int id, double uhelNatoceni, int hp, int maxHp);
	int GetHp() const;
	void SetHp(int hp);
	int GetMaxHp() const;
	void SetMaxHp(int maxHp);
};

#endif // !MONSTRUM_H
