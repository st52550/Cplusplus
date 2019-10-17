#include "Monstrum.h"

Monstrum::Monstrum(int id, double uhelNatoceni, int hp, int maxHp) : PohyblivyObjekt(id, uhelNatoceni) {
	this->hp = hp;
	this->maxHp = maxHp;
}

int Monstrum::GetHp() const {
	return hp;
}

void Monstrum::SetHp(int hp) {
	this->hp = hp;
}

int Monstrum::GetMaxHp() const {
	return maxHp;
}

void Monstrum::SetMaxHp(int maxHp) {
	this->maxHp = maxHp;
}