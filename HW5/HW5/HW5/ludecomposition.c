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

int ludecomposition(void)
{
	int i, j, row, col, m, n, dum, * indx, * jndx;
	float d, ** a, ** ai, **aa, * x, *c, *y;
	float b[NP];
	char filename[FILENUM][MAXSTR];
	long idum = (-13);
	FILE* fp;

	indx = ivector(1, NP);
	c = vector(1, NP);
	x = vector(1, NP);
	a = matrix(1, NP, 1, NP);
	ai = matrix(1, NP, 1, NP);
	aa = matrix(1, NP, 1, NP);
	x = matrix(1, NP, 1, NP);
	
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
				fscanf(fp, "%f ", &a[row][col]);

		for (row = 1;row <= n;row++)
			fscanf(fp, "%f ", &x[row]);
		/* Print out a-matrix for comparison with product of
		   lower and upper decomposition matrices */
		printf("original matrix:\n");
		for (row = 1; row <= n; row++) {
			for (col = 1;col <= n;col++) printf("%12.6f", a[row][col]);
			printf("\n");
		}

		for (row = 1; row <= n; row++) {
			b[row] = x[row];
		}

		/* Perform the decomposition */
		ludcmp(a, n, indx, &d);
		
		for (col = 1; col <= n; col++) {
			for (row = 1; row <= m; row++) c[row] = 0.0;
			c[col] = 1.0;
			lubksb(a, n, indx, c);
			for (row = 1; row <= n; row++) ai[row][col] = c[row];
		}

		printf("inverse of A:\n");
		for (row = 1; row <= n; row++) {
			for (col = 1;col <= n;col++) printf("%12.6f", ai[row][col]);
			printf("\n");
		}
		
		lubksb(a, n, indx, b);

		printf("solution: \n");
		for (row = 1; row <= n; row++)
			printf("%12.6f ", b[row]);

		printf("\ndeterminant: ");
		for (j = 1; j <= n; j++) d *= a[j][j];
		printf("%12.6f\n", d);
		/*
		for (j = 1;i <= n;j++) b[j] *= (1.0 + 0.2 * ran3(&idum));
		printf("\nSolution vector with noise added:\n");
		for (j = 1;j <= n;j++) printf("%12.6f", b[j]);
		printf("\n");
		mprove(a, aa, n, indx, x, b);
		printf("\nSolution vector recovered by mprove:\n");
		for (j = 1;j <= n;j++) printf("%12.6f", b[j]);
		*/
		printf("\n***********************************\n");
		//printf("press return for next problem:\n");
		//(void)getchar();




		fclose(fp);

	}
	free_vector(x, 1, NP);
	free_matrix(a, 1, NP, 1, NP);
	free_matrix(ai, 1, NP, 1, NP);
	free_ivector(indx, 1, NP);
	return 0;
}
#undef NRANSI
