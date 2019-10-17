#include "StatickyObjekt.h"

StatickyObjekt::StatickyObjekt(int id, TypPrekazky typPrekazky) : Objekt(id) {
	this->typPrekazky = typPrekazky;
}

StatickyObjekt::TypPrekazky StatickyObjekt::GetTypPrekazky() const {
	return typPrekazky;
}