#include "floyd.h"
#include <windows.h>
#include <ctime>
#include <iostream>
#include <fstream>

void testTime(int** M, int n) {
	int t1, t2;
	t1 = GetTickCount();
	Floyd(M, n);
	t2 = GetTickCount();
	std::cout << "�����, ����������� �� ���������� = " << t2 - t1 << " ����� ~ " << ((double)(t2 - t1) / 1000) << " ������" << std::endl;
}

void test(int n) {

	int** M1 = new int*[n];

	for (int i = 0; i < n; i++)
		M1[i] = (int*)new int[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M1[i][j] = 0;
		}
	}

	//���������� ������� �1
	int value;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				value = rand() % 10;
				M1[i][j] = value;
				M1[j][i] = value;
			}
		}
	}

	int** M2 = new int*[n];

	for (int i = 0; i < n; i++)
		M2[i] = (int*)new int[n];

	//���������� ������� �2
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M2[i][j] = M1[i][j];
		}
	}

	std::cout << "�������� ������-��������" << std::endl;
	std::cout << "���������� ������ � �����: " << n << std::endl << std::endl;

	omp_set_num_threads(1);
	std::cout << "���������� �������: 1" << std::endl;
	testTime(M1, n);

	std::cout << "----------------------------------------------------------" << std::endl;

	omp_set_num_threads(8);
	std::cout << "���������� �������: 8" << std::endl;
	testTime(M2, n);

	std::cout << "----------------------------------------------------------" << std::endl;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (M1[i][j] != M2[i][j]) {
				std::cout << "���������� ���������� �� ���������" << std::endl;
				return;
			}
		}
	}

}

int main() {

	setlocale(LC_ALL, "Russian");
	srand(time(nullptr));

	test(10000);

	return 0;
}