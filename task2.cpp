#include <windows.h>
#include <ctime>
#include "matrix.h"

Matrix<int> testMultTime(Matrix<int> A, Matrix<int> B) {
	int t1, t2;
	t1 = GetTickCount();
	Matrix<int> C = A * B;
	t2 = GetTickCount();
	std::cout << "�����, ����������� �� ���������� = " << t2 - t1 << " ����� ~ "<< ((double)(t2 - t1) / 1000) << " ������" << std::endl;
	return C;
}

void testMultMatrix(int n) {

	Matrix<int> A = Matrix<int>(n, n);
	Matrix<int> B = Matrix<int>(n, n);
	A.randIntMatrix(100);
	B.randIntMatrix(100); 

	std::cout << "__________________________________________________________" << std::endl << std::endl;
	std::cout << "��������� ������" << std::endl;
	std::cout << "����������� ������: " << n << "x" << n << std::endl << std::endl;

	omp_set_num_threads(1);
	std::cout << "���������� �������: 1" << std::endl;
	Matrix<int> C = testMultTime(A, B);

	std::cout << "----------------------------------------------------------" << std::endl;

	omp_set_num_threads(8);
	std::cout << "���������� �������: 8" << std::endl;
	Matrix<int> D = testMultTime(A, B);

	std::cout << "----------------------------------------------------------" << std::endl;

	if (C == D)
		std::cout << "���������� ��������� ���������" << std::endl;
	else 
		std::cout << "���������� ��������� �� ���������" << std::endl;
}

int main() {
	
	setlocale(LC_ALL, "Russian");
	srand(time(nullptr));
	
	testMultMatrix(1000);

	return 0;
}