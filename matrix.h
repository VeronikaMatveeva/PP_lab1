#pragma once
#include <omp.h>
#include <iostream>

template <typename T>
class Matrix
{
private:

	T** A; // матрица (указатель на двумерный массив)
	int n; // количество столбцов
	int m; // количество строк

public:

	// конструкторы 
	
	Matrix()
	{
		n = m = 0;
		A = nullptr;
	}

	Matrix(int _m, int _n)
	{
		m = _m;
		n = _n;

		A = (T**) new T*[m];

		for (int i = 0; i < m; i++)
			A[i] = (T*)new T[n];

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				A[i][j] = 0;
	}

	Matrix(const Matrix& B)
	{
		
		m = B.m;
		n = B.n;

		A = (T**) new T*[m];
		for (int i = 0; i < m; i++)
			A[i] = (T*) new T[n];

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				A[i][j] = B.GetMij(i,j);
	}

	// методы

	T GetMij(int i, int j) const
	{
		if ((m > 0) && (n > 0))
			return A[i][j];
		else
			return 0;
	}

	void SetMij(int i, int j, T value)
	{
		if ((i < 0) || (i >= m))
			return;
		if ((j < 0) || (j >= n))
			return;
		A[i][j] = value;
	}

	void Print(const char* MatrixName)
	{
		std::cout << "Matrix " << MatrixName << ":"<< std::endl;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
				std::cout << A[i][j] << "\t";
			std::cout << std::endl;
		}
	}

	//заполнение матрицы случайными целыми  числами по модулю
	void randIntMatrix(int mod) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				this->SetMij(i, j, rand() % mod);
			}
		}
	}

	// операторы

	Matrix operator=(const Matrix& B)
	{
		if (n > 0)
		{
			for (int i = 0; i < m; i++)
				delete[] A[i];
		}

		if (m > 0)
		{
			delete[] A;
		}

		m = B.m;
		n = B.n;

		A = (T**) new T*[m];
		for (int i = 0; i < m; i++)
			A[i] = (T*) new T[n];

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				A[i][j] = B.GetMij(i, j);
		return *this;
	}

	bool operator== (const Matrix &B)
	{
		if (n == B.n && m == B.m) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					if (this->GetMij(i, j) != B.GetMij(i, j)) {
						return false;
					}
				}
			}
			return true;
		}
		else{
			return false;
		}
	}


	// УМНОЖЕНИЕ
	Matrix operator*(const Matrix& B) 
	{
		if (m != B.n) {
			return Matrix();
		}
		
		Matrix<T> result = Matrix<T>(n, B.m);

		int i, j, k;
#pragma omp parallel private(i, j, k)
		{
			// умножение по формуле
			#pragma omp for
			for (i = 0; i < n; i++) {	
				for (j = 0; j < B.m; j++) {
					for (k = 0; k < m; k++) {
						T value = result.GetMij(i, j);
						value += this->GetMij(i, k) * B.GetMij(k, j);
						result.SetMij(i, j, value);
					}
				}
			}
		}

		return result;
	}

	// деструктор

	~Matrix()
	{
		if (n > 0)
		{
			for (int i = 0; i < m; i++)
				delete[] A[i];
		}

		if (m > 0)
			delete[] A;
	}
};