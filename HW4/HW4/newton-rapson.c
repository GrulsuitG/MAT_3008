#define _CRT_SECURE_NO_WARNINGS

/* Driver for routine rtnewt */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define N 100
#define NBMAX 20
#define X1 0.0
#define X2 400.0

static float fx(float x)
{
	return exp(-0.005 * x) * cos(sqrt(2000 - (0.01 * x * x)) * 0.05) - 0.01;
}


static void funcd(float x, float* fn, float* df)
{
	*fn = fx(x);
	*df = (exp(-(x / 200)) * (sqrt(200000 - (x * x)) * cos(sqrt(200000 - (x * x)) / 200) - x * sin(sqrt(200000 - (x * x)) / 200))) / (200 * sqrt(200000 - (x * x)));
}

int newtonrapson(void)
{
	int i, nb = NBMAX;
	float xacc, root, * xb1, * xb2;

	xb1 = vector(1, NBMAX);
	xb2 = vector(1, NBMAX);
	zbrak(fx, X1, X2, N, xb1, xb2, &nb);
	printf("\nnewton-rapson:\n");
	/*for (i = 1; i <= nb; i++) {
		xacc = (1.0e-4);
		printf("accuracy 10^-4\n");
		root = rtnewt(funcd, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n", i, root, fx(root));
	}*/
	for (i = 1; i <= nb; i++) {
		xacc = (1.0e-6) * (xb1[i] + xb2[i]) / 2.0;
		printf("accuracy 10^-6\n");
		root = rtnewt(funcd, xb1[i], xb2[i], xacc);
		printf("root %3d %14.6f %14.6f\n", i, root, fx(root));
	}
	free_vector(xb2, 1, NBMAX);
	free_vector(xb1, 1, NBMAX);
	return 0;
}
#undef NRANSI

