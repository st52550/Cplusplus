#include "Potrubi.h"

Potrubi::Potrubi(int rozmer, APotrubniPrvek*** potrubi) {
	this->rozmer = rozmer;
	this->potrubi = potrubi;
}

Potrubi::~Potrubi() {
	for (size_t i = 0; i < rozmer; i++) {
		for (size_t j = 0; j < rozmer; j++) {
			delete potrubi[i][j];
		}
		delete[] potrubi[i];
	}
	delete potrubi;
}

APotrubniPrvek* Potrubi::DejPrvek(int x, int y) const {
	if (x < 0 || x > rozmer || y < 0 || y > rozmer) {
		return nullptr;
	} else {
		return potrubi[x][y];
	}
}

bool Potrubi::JePotrubiOk() const {
	APotrubniPrvek* prvek = nullptr;

	for (size_t i = 0; i < rozmer; i++) {
		for (size_t j = 0; j < rozmer; j++) {
			prvek = DejPrvek(i, j);
			if (prvek != nullptr) {
				if (!prvek->JeKorektneZapojen(this)) {
					return false;
				}
			}
		}
	}

	return true;
}

bool JVZPrvek::JeKorektneZapojen(const IPotrubi* potrubi) const {
	if (potrubi->DejPrvek(_x, (_y - 1)) != nullptr && potrubi->DejPrvek(_x, (_y + 1)) != nullptr &&
		potrubi->DejPrvek((_x + 1), _y) != nullptr) {
		return true;
	}
	return false;
}

bool NicPrvek::JeKorektneZapojen(const IPotrubi* potrubi) const {
	return true;
}

bool SJVZPrvek::JeKorektneZapojen(const IPotrubi* potrubi) const {
	if (potrubi->DejPrvek(_x, (_y - 1)) != nullptr && potrubi->DejPrvek(_x, (_y + 1)) != nullptr &&
		potrubi->DejPrvek((_x - 1), _y) != nullptr && potrubi->DejPrvek((_x + 1), _y) != nullptr) {
		return true;
	}
	return false;
}

bool SJPrvek::JeKorektneZapojen(const IPotrubi* potrubi) const {
	if (potrubi->DejPrvek((_x - 1), _y) != nullptr && potrubi->DejPrvek((_x + 1), _y) != nullptr) {
		return true;
	}
	return false;
}

bool VZPrvek::JeKorektneZapojen(const IPotrubi* potrubi) const {
	if (potrubi->DejPrvek(_x, (_y - 1)) != nullptr && potrubi->DejPrvek(_x, (_y + 1)) != nullptr) {
		return true;
	}
	return false;
}