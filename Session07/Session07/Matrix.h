#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

template<typename T>

struct Matrix {
private:
	T*** _matrix;
	int _rows;
	int _columns;
public:
	Matrix(int rows, int columns);
	Matrix(const Matrix<T>& m);
	~Matrix();
	void Set(int row, int column, T value);
	void SetCells(T* array);
	T& Get(int row, int column);
	T& Get(int row, int column) const;

	template<typename R>
	Matrix<R> TypeCast() const;
	Matrix Transposition() const;
	Matrix Product(const Matrix& m) const;
	Matrix Product(T scalar) const;
	Matrix Sum(const Matrix& m) const;
	Matrix Sum(T scalar) const;

	bool IsEqual(const Matrix& m) const;
	void Printout() const;
};

template<typename T>
Matrix<T>::Matrix(int rows, int columns) {
	_rows = rows;
	_columns = columns;
	_matrix = new T ** [rows];

	for (size_t i = 0; i < rows; i++)
	{
		_matrix[i] = new T * [columns];

		for (size_t j = 0; j < columns; j++)
		{
			_matrix[i][j] = new T;
		}
	}
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m) {
	_rows = m._rows;
	_columns = m._columns;
	_matrix = new T ** [_rows];

	for (size_t i = 0; i < _rows; i++)
	{
		_matrix[i] = new T * [_columns];

		for (size_t j = 0; j < _columns; j++)
		{
			_matrix[i][j] = new T;
			*_matrix[i][j] = *m._matrix[i][j];
		}
	}
}

template<typename T>
Matrix<T>::~Matrix() {
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			delete _matrix[i][j];
		}
		
		delete[] _matrix[i];
	}

	delete _matrix;
}

template<typename T>
void Matrix<T>::Set(int row, int column, T value) {	
	if ((row >= 0 && row <= _rows) && (column >= 0 && column <= _columns))
	{
		*_matrix[row][column] = value;
	}
	else {
		throw std::invalid_argument("Wrong index");
	}
}

template<typename T>
void Matrix<T>::SetCells(T* array) {
	int index = 0;

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			*_matrix[i][j] = array[index];
			index++;
		}
	}
}

template<typename T>
T& Matrix<T>::Get(int row, int column) {
	if ((row >= 0 && row <= _rows) && (column >= 0 && column <= _columns))
	{
		return *_matrix[row][column];
	}
	else {
		throw std::invalid_argument("Wrong index");
	}
}

template<typename T>
T& Matrix<T>::Get(int row, int column) const {
	if ((row >= 0 && row <= _rows) && (column >= 0 && column <= _columns))
	{
		return *_matrix[row][column];
	}
	else {
		throw std::invalid_argument("Wrong index");
	}
}

template<typename T>
template<typename R>
Matrix<R> Matrix<T>::TypeCast() const {
	Matrix<R> newMatrix = Matrix<R>(_rows, _columns);

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			newMatrix.Set(i, j, *_matrix[i][j]);
		}
	}

	return newMatrix;
}

template<typename T>
Matrix<T> Matrix<T>::Transposition() const {
	Matrix<T> transposition = Matrix<T>(_columns, _rows);

	for (size_t i = 0; i < _columns; i++)
	{
		for (size_t j = 0; j < _rows; j++)
		{
			*transposition._matrix[i][j] = *_matrix[j][i];
		}
	}

	return transposition;
}

template<typename T>
Matrix<T> Matrix<T>::Product(const Matrix& m) const {
	if (_columns != m._rows)
	{
		throw std::invalid_argument("Condition for product was not met.");
	}

	T sum = 0;
	Matrix<T> product = Matrix<T>(_rows, m._columns);

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < m._columns; j++)
		{
			for (size_t k = 0; k < _columns; k++)
			{
				sum += *_matrix[i][k] * *m._matrix[k][j];
			}	

			*product._matrix[i][j] = sum;
			sum = 0;
		}
	}

	return product;
}

template<typename T>
Matrix<T> Matrix<T>::Product(T scalar) const {
	Matrix<T> product = Matrix<T>(_rows, _columns);

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			*product._matrix[i][j] = *_matrix[i][j] * scalar;
		}
	}

	return product;
}

template<typename T>
Matrix<T> Matrix<T>::Sum(const Matrix& m) const {
	if (_rows != m._rows || _columns != m._columns)
	{
		throw std::invalid_argument("Matrix has invalid size.");
	}

	Matrix<T> sum = Matrix<T>(_rows, _columns);

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			*sum._matrix[i][j] = *_matrix[i][j] + *m._matrix[i][j];
		}
	}

	return sum;
}

template<typename T>
Matrix<T> Matrix<T>::Sum(T scalar) const {
	Matrix<T> sum = Matrix<T>(_rows, _columns);

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			*sum._matrix[i][j] = *_matrix[i][j] + scalar;
		}
	}

	return sum;
}

template<typename T>
bool Matrix<T>::IsEqual(const Matrix& m) const {
	if (_rows != m._rows && _columns != m._columns)
	{
		return false;
	}

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			if (_matrix[i][j] != m._matrix[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

template<typename T>
void Matrix<T>::Printout() const {

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			std::cout << *_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

#endif // !MATRIX_H
