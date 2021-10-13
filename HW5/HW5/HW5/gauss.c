#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define MAXSTR 20
#define FILENUM 3
#define NP 20

int gauss(void){
	int i, n, m, row, col;
	float** a, ** ai, ** b, * x, ** t;
	
	FILE* fp;
	char filename[FILENUM][MAXSTR];
	
	a = matrix(1, NP, 1, NP);
	ai = matrix(1, NP, 1, NP);
	b = matrix(1, NP, 1, NP);
	x = vector(1, NP);


	for (i = 1; i <= FILENUM; i++) {
		sprintf(filename[i - 1], "lineq%d.dat", i);
	}

	for (i = 0; i < FILENUM; i++) {
		
		if ((fp = fopen(filename[i], "r")) == NULL)
			nrerror("file is not exist\n");
		
		fscanf(fp, "%d %d ", &n, &m);
		for (row = 1; row <= n; row++)
			for (col = 1; col <= m; col++)
				fscanf(fp, "%f ", &a[row][col]);
		
	

		printf("Matrix A\n");
		for (row = 1; row <= n; row++) {
			for (col = 1; col <= m; col++)
				printf("%12.6f", a[row][col]);
			printf("\n");
		}
		
		col = 1;
		for (row = 1; row <= n; row++)
			fscanf(fp, "%f ", &b[row][col]);

		printf("\n");
		
		for (row = 1; row <= n; row++) {
			for (col = 1; col <= m; col++) {
				ai[row][col] = a[row][col];
			}
		}

		gaussj(ai, n, b, m);

		printf("inverse of A\n");
		for (row = 1; row <= n; row++) {
			for (col = 1; col <= m; col++)
				printf("%12.6f", ai[row][col]);
			printf("\n");
		}

		printf("solution x: \n");
		for (row = 1; row <= n; row++) {
			printf("%12.6f", b[row][1]);
		}
		
		printf("\n");
		

	}
	
}