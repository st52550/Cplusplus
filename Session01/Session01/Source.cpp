#include <iostream>

using namespace std;

struct Trojuhelnik {
	int a;
	int b;
	int c;
};

//bool lzeSestrojit(Trojuhelnik* t);
bool lzeSestrojit(Trojuhelnik t);

int main() {
	int a;
	int b;
	int c;
	int pocet = 0;

	Trojuhelnik trojuhelnik;

	cout << "Zadejte mnozstvi trojuhelniku: ";
	cin >> pocet;
	/*cout << "a: ";
	cin >> trojuhelnik.a;
	cout << "b: ";
	cin >> trojuhelnik.b;
	cout << "c: ";
	cin >> trojuhelnik.c;

	Trojuhelnik* ukazatel = new Trojuhelnik;

	ukazatel->a = trojuhelnik.a;
	ukazatel->b = trojuhelnik.b;
	ukazatel->c = trojuhelnik.c;

	bool test = lzeSestrojit(ukazatel);

	delete ukazatel;*/

	//5
	Trojuhelnik* poleT = new Trojuhelnik[pocet];

	for (size_t i = 0; i < pocet; i++)
	{
		cout << "a: ";
		cin >> poleT[i].a;
		cout << "b: ";
		cin >> poleT[i].b;
		cout << "c: ";
		cin >> poleT[i].c;
		lzeSestrojit(poleT[i]);
	}

	delete[] poleT;
}

bool lzeSestrojit(Trojuhelnik t) {
	if (t.a + t.b > t.c&& t.a + t.c > t.b&& t.b + t.c > t.a) {
		int obvod = t.a + t.b + t.c;
		cout << "Obvod je " << obvod << endl;
		return true;
	}
	else {
		cout << "Trojuhelnik nelze sestrojit" << endl;
		return false;
	}
}

//bool lzeSestrojit(Trojuhelnik* t) {
//	if (t->a + t->b > t->c&& t->a + t->c > t->b&& t->b + t->c > t->a) {
//		int obvod = t->a + t->b + t->c;
//		cout << "Obvod je " << obvod << endl;
//		return true;
//	}
//	else {
//		cout << "Trojuhelnik nelze sestrojit" << endl;
//		return false;
//	}
//}