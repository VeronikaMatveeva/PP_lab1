#pragma once
#include <omp.h>

//אכדמנטעל װכמיהא-׃מנרוככא
void Floyd(int** M, int n)
{
	int i, j, k;
#pragma omp parallel private(i, j, k)
	
	for (k = 0; k < n; k++) {
		#pragma omp for
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if ((M[i][k] + M[k][j]) < M[i][j]) {
					M[i][j] = M[i][k] + M[k][j];
				}
			}
		}
	}
}