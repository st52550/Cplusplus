#include "PohyblivyObjekt.h"

PohyblivyObjekt::PohyblivyObjekt(int id, double uhelNatoceni) : Objekt(id) {
	this->uhelNatoceni = uhelNatoceni;
}

double PohyblivyObjekt::GetUhelNatoceni() const {
	return uhelNatoceni;
}

void PohyblivyObjekt::SetUhelNatoceni(double uhelNatoceni) {
	this->uhelNatoceni = uhelNatoceni;
}