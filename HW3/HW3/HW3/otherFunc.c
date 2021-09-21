#define _CRT_SECURE_NO_WARNINGS


/* Driver for routine rtsafe */

#include <math.h>
#include <stdio.h>
#define NRANSI

#include "nr.h"
#include "nrutil.h"




#define M_PI 3.14159265358979323846
#define N 100
#define NBMAX 20
#define FUNCNUM 4


static float fx1(float x)
{
	return 10 * exp(-x) * sin(2 * M_PI * x) - 2;
}

static void funcd1(float x, float* fn, float* df)
{
	*fn = fx1(x);
	*df = -exp(-x) * (10 * sin(2 * M_PI * x) - 20 * M_PI * cos(2 * M_PI * x));
}


static float fx2(float x) 
{
	return x * x - 2 * x * exp(-x) + exp(-2 * x);

}

static void funcd2(float x, float* fn, float* df)
{
	*fn = fx2(x);
	*df = 2 * exp(-2 * x) * (x * exp(2 * x) + (x - 1) * exp(x) - 1);

}

static float fx3(float x)
{
	return cos(x + sqrt(2)) + x * (x / 2 + sqrt(2));
}

static void funcd3(float x, float* fn, float* df)
{
	*fn = fx3(x);
	*df = -sin(x + sqrt(2)) + x + sqrt(2);
}

static float fx4(float x)
{
	return exp(-x) * (3 * cos(2 * x) + 4 * sin(2 * x)) * x;
}

static void funcd4(float x, float* fn, float* df)
{
	*fn = fx4(x);
	*df = -exp(-x) * ((10 * x - 4) * sin(2 * x) + (-5 * x - 3) * cos(2 * x));
}

int otherfunc(void)
{
	int nb = NBMAX;
	float xacc, root, * xb1, * xb2;
	float (*fx[FUNCNUM])(float) = { fx1, fx2, fx3, fx4 };
	void (*funcd[FUNCNUM])(float, float*, float*) = { funcd1, funcd2, funcd3, funcd4 };

	float x1[4] = { 0.1, 0, -2.0, -1.0 };
	float x2[4] = { 1.0, 1.0, -1.0, 1.0 };

	
	for (int i = 0; i < FUNCNUM; i++) {
		xb1 = vector(1, NBMAX);
		xb2 = vector(1, NBMAX);
		zbrak(fx[i], x1[i], x2[i], N, xb1, xb2, &nb);
		printf("\nRoots of %s%d\n", "fx",i+1);

		printf("%21s %15s\n", "x", "f(x)");
		for (int j = 1; j <= nb; j++) {
			xacc = (1.0e-6) * (xb1[j] + xb2[j]) / 2.0;
			root = rtsafe(funcd[i], xb1[j], xb2[j], xacc);
			printf("root %3d %14.6f %14.6f\n", j, root, fx[i](root));
		}
		
		free_vector(xb2, 1, NBMAX);
		free_vector(xb1, 1, NBMAX);
	}
	
	
	return 0;
}

#undef NRANSI


