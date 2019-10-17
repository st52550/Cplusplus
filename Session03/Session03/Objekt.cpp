#include "Objekt.h"

Objekt::Objekt(int id) : x(0.0), y(0.0) {
	this->id = id;
}

Objekt::~Objekt() {

}

int Objekt::GetId() const {
	return id;
}

void Objekt::SetId(int id) {
	this->id = id;
}

double Objekt::GetX() const {
	return x;
}

void Objekt::SetX(double x) {
	this->x = x;
}

double Objekt::GetY() const  {
	return y;
}

void Objekt::SetY(double y) {
	this->y = y;
}