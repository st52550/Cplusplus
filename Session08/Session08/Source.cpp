#include <iostream>
#include <fstream>
#include <sstream>
#include "Potrubi.h"

using namespace std;

int main() {
	ifstream in{};
	in.open("potrubi5.txt");
	string radek;
	int rozmer = 0;
	APotrubniPrvek*** potrubi = nullptr;

	if (in.is_open()) {
		getline(in, radek);
		rozmer = stoi(radek);

		potrubi = new APotrubniPrvek * *[rozmer];
		for (size_t i = 0; i < rozmer; i++) {
			potrubi[i] = new APotrubniPrvek * [rozmer];
		}

		for (size_t i = 0; i < rozmer; i++) {
			getline(in, radek);
			for (size_t j = 0; j < rozmer; j++)
			{
				switch (radek[j]) {
				case '-': potrubi[i][j] = new VZPrvek();
					potrubi[i][j]->_x = i;
					potrubi[i][j]->_y = j;
					break;
				case 'I': potrubi[i][j] = new SJPrvek();
					potrubi[i][j]->_x = i;
					potrubi[i][j]->_y = j;
					break;
				case '+': potrubi[i][j] = new SJVZPrvek();
					potrubi[i][j]->_x = i;
					potrubi[i][j]->_y = j;
					break;
				case 'O': potrubi[i][j] = new NicPrvek();
					potrubi[i][j]->_x = i;
					potrubi[i][j]->_y = j;
					break;
				case 'T': potrubi[i][j] = new JVZPrvek();
					potrubi[i][j]->_x = i;
					potrubi[i][j]->_y = j;
					break;
				default: potrubi[i][j] = nullptr;
						 break;
				}
			}
		}
	} else {
		cerr << "Soubor se nepodarilo otevrit";
	}

	in.close();

	Potrubi* schema = new Potrubi(rozmer, potrubi);

	if (schema->JePotrubiOk()) {
		cout << "Potrubi je spravne zapojene." << endl;
	} else {
		cout << "Potrubi je spatne zapojene." << endl;
	}

	delete schema;
}