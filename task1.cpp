#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <omp.h>

int main()
{
	int seed = (int)time(0);
#pragma omp parallel
	{
		int rank = omp_get_thread_num();
		srand(31*seed + rank*999983);
		int num = rand();
		std::ofstream file(std::to_string(rank) + ".txt");
		file << num;
		file.close();

#pragma omp critical
		{
			std::cout << num << std::endl;
		}
	}
}