#define _CRTDBG_MAP_ALLOC
#include "Matrix.h"

#include <iostream>
#include <crtdbg.h>
void Function() {
	Matrix<int> m{ 3,3 };

	m.Printout();
	std::cout << std::endl;
	m.Set(0, 0, 5);
	m.Printout();
	std::cout << std::endl;

	int array[] = { 0,1,2,3,4,5,6,7,8 };

	m.SetCells(array);
	m.Printout();
	std::cout << std::endl;
	std::cout << m.Get(1, 0) << std::endl << std::endl;

	Matrix<int> copyM = Matrix<int>(m);
	copyM.Printout();
	std::cout << std::endl;
	Matrix<int> mt = m.Transposition();
	mt.Printout();
	std::cout << std::endl;
	Matrix<int> mmt = m.Product(mt);
	mmt.Printout();
	std::cout << std::endl;
	Matrix<double> mmt_d = mmt.TypeCast<double>();
	mmt_d.Printout();
	std::cout << std::endl;
	Matrix<double> n_d{ 3,3 };
	double array_d[] = { 4.6,5,0,2,-0.5,7,1.5,9,6 };
	n_d.SetCells(array_d);
	n_d.Printout();
	std::cout << std::endl;

	double scalar = 0.5;
	Matrix<double> mmtn_d = mmt_d.Product(scalar);
	mmtn_d.Printout();
	std::cout << std::endl;

	Matrix<int> r = mmtn_d.TypeCast<int>();
	r.Printout();
	std::cout << std::endl;

	Matrix<int> t{ 3,3 };
	int tArray[] = { 85,225,236,292,819,866,499,1413,1496 };
	t.SetCells(tArray);
	t.Printout();
	std::cout << std::endl;

	Matrix<int> sum = r.Sum(t);
	sum.Printout();
	std::cout << std::endl;

	double scalarSum = 10.5;
	Matrix<double> sumScalar = mmtn_d.Sum(scalarSum);
	sumScalar.Printout();
	std::cout << std::endl;

	std::cout << "r==t ? " << (r.IsEqual(t) ? "true" : "false") << std::endl;
	std::cout << "m==copyM ? " << (m.IsEqual(copyM) ? "true" : "false") << std::endl;
}

int main() {
	Function();

	if (_CrtDumpMemoryLeaks() != NULL)
	{
		std::cout << "Nebyla provedena dealokace";
	}
	return 0;
}