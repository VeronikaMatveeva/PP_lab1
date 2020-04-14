#include <windows.h>
#include <ctime>
#include "matrix.h"

Matrix<int> testMultTime(Matrix<int> A, Matrix<int> B) {
	int t1, t2;
	t1 = GetTickCount();
	Matrix<int> C = A * B;
	t2 = GetTickCount();
	std::cout << "Время, затраченное на вычисления = " << t2 - t1 << " тиков ~ "<< ((double)(t2 - t1) / 1000) << " секунд" << std::endl;
	return C;
}

void testMultMatrix(int n) {

	Matrix<int> A = Matrix<int>(n, n);
	Matrix<int> B = Matrix<int>(n, n);
	A.randIntMatrix(100);
	B.randIntMatrix(100); 

	std::cout << "__________________________________________________________" << std::endl << std::endl;
	std::cout << "УМНОЖЕНИЕ МАТРИЦ" << std::endl;
	std::cout << "Размерность матриц: " << n << "x" << n << std::endl << std::endl;

	omp_set_num_threads(1);
	std::cout << "Количество потоков: 1" << std::endl;
	Matrix<int> C = testMultTime(A, B);

	std::cout << "----------------------------------------------------------" << std::endl;

	omp_set_num_threads(8);
	std::cout << "Количество потоков: 8" << std::endl;
	Matrix<int> D = testMultTime(A, B);

	std::cout << "----------------------------------------------------------" << std::endl;

	if (C == D)
		std::cout << "Результаты умножения совпадают" << std::endl;
	else 
		std::cout << "Результаты умножения НЕ совпадают" << std::endl;
}

int main() {
	
	setlocale(LC_ALL, "Russian");
	srand(time(nullptr));
	
	testMultMatrix(1000);

	return 0;
}