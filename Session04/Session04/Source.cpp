#include "Cas.h"
#include "Datum.h"
#include "DatumCas.h"

#include <iostream>

#define N 10
using namespace std;

void SeraditPole(IComparable** pole, int velikostPole);
void VypisPole(IComparable** pole, int velikostPole);

int main() {
	cout << "Seznam casu:" << endl;

	IComparable** pole = new IComparable*[N];
 
	for (size_t i = 0; i < N; i++)
	{
		pole[i] = new Cas(rand() % 24, rand() % 60, rand() % 60);
	}

	SeraditPole(pole, N);
	VypisPole(pole, N);

	delete[] pole;

	cout << "Seznam datumu:" << endl;

	pole = new IComparable * [N];

	for (size_t i = 0; i < N; i++)
	{
		pole[i] = new Datum(rand() % 28 + 1, rand() % 12 + 1, rand() % 19 + 2000);
	}

	SeraditPole(pole, N);
	VypisPole(pole, N);

	delete[] pole;

	cout << "Seznam datumu a casu soucasne:" << endl;

	pole = new IComparable * [N];

	for (size_t i = 0; i < N; i++)
	{
		pole[i] = new DatumCas(
						new Datum(rand() % 28 + 1, rand() % 12 + 1, rand() % 19 + 2000),
						new Cas(rand() % 24, rand() % 60, rand() % 60)
					);
	}

	SeraditPole(pole, N);
	VypisPole(pole, N);

	delete[] pole;
}

void SeraditPole(IComparable** pole, int velikostPole) {
	for (size_t i = 0; i < velikostPole; i++)
	{
		for (size_t j = 0; j < velikostPole - 1; j++) {
			if (pole[j]->compareTo(pole[j + 1]) > 0)
			{
				swap(pole[j], pole[j + 1]);
			}
		}
	}
}

void VypisPole(IComparable** pole, int velikostPole) {
	for (size_t i = 0; i < N; i++)
	{
		cout << pole[i]->toString() << endl;
	}
}