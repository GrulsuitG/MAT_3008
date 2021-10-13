#define _CRT_SECURE_NO_WARNINGS

/* Driver for routine ludcmp */

#include <stdio.h>
#include <stdlib.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define MAXSTR 20
#define FILENUM 3
#define NP 20

int singularValuedcmp(void)
{
	int i, row, col, m, n, k, l;
	float* w, * b, ** u, ** ai, ** v, *x,wi;
	FILE* fp;
	char filename[FILENUM][MAXSTR];

	w = vector(1, NP);
	b = vector(1, NP);
	x = vector(1, NP);
	u = matrix(1, NP, 1, NP);
	ai = matrix(1, NP, 1, NP);
	v = matrix(1, NP, 1, NP);
	
	for (i = 1; i <= FILENUM; i++) {
		sprintf(filename[i - 1], "lineq%d.dat", i);
	}

	for (i = 0; i < FILENUM; i++) {
		printf("%s\n", filename[i]);
		if ((fp = fopen(filename[i], "r")) == NULL)
			nrerror("Data file not found\n");


		fscanf(fp, "%d %d ", &n, &m);

		for (row = 1;row <= n;row++)
			for (col = 1;col <= n;col++)
				fscanf(fp, "%f ", &u[row][col]);

		for (row = 1;row <= n;row++)
			fscanf(fp, "%f ", &b[row]);

		printf("Original matrix:\n");
		for (row = 1;row <= n;row++) {
			for (col = 1;col <= m; col++)
				printf("%12.6f", u[row][col]);
			printf("\n");
		}

		svdcmp(u, m, n, w, v);

		printf("inverso of A:\n");      
		for (row = 1; row <= n; row++) {
			for (col = 1; col <= m; col++) {
				ai[row][col] = 0.0;
				for (k = 1; k <= n; k++) {
					wi = ((w[k] < 0.000001) ? 0.0 : (1 / w[k]));
					ai[row][col] += v[row][k] * wi * u[col][k];
				}
			}
			for (col = 1; col <= m; col++)
				printf("%12.6f ", ai[row][col]);
			printf("\n");
		}
		for (row = 1; row <= n; row++) {
			x[row] = 0.0;
			for (col = 1; col <= m; col++)
				x[row] += ai[row][col] * b[col];
		}
		printf("solution:\n");
		for (row = 1; row <= n; row++)
			printf("%12.6f", x[row]);




		fclose(fp);
		printf("\n***********************************\n");
	}
	free_matrix(v, 1, NP, 1, NP);
	free_matrix(u, 1, NP, 1, NP);
	free_vector(w, 1, NP);
	free_vector(b, 1, NP);
	return 0;
}
#undef NRANSI
