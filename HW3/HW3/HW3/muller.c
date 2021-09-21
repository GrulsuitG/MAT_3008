#define _CRT_SECURE_NO_WARNINGS

/* Driver for routine rtsec */

#include <stdio.h>
#include <math.h>
#define NRANSI
#include "nr.h"
#include "nrutil.h"

#define N 100
#define NBMAX 20
#define X1 1.0
#define X2 10.0
#define MAXIT 100

static float fx(float x)
{
	//return pow(x, 3) + 2 * x * x + 10 * x - 20;
	return bessj0(x);
}

float muller(float (*f)(float), float p0, float p1, float p2) {
	float result, f0, f1, f2;
	float a, b, c, x, y, m ,n;
	float h1, h2, d1, d2;
	for (int i = 0;; i++) {
		f0 = f(p0);
		f1 = f(p1);
		f2 = f(p2);
		h1 = p0 - p2;
		h2 = p1 - p2;
		d1 = f0 - f2;
		d2 = f1 - f2;
		c = f2;
		b = (h1 * h1 * d2 - h2 * h2 * d1) / ((h1 * h2) * (h1 - h2));
		a = (h2 * d1 - h1 * d2) / ((h1 * h2) * (h1 - h2));
		x = ((-2 * c) / (b + sqrt(b * b - 4 * a * c)));
		y = ((-2 * c) / (b - sqrt(b * b - 4 * a * c)));

		if (x >= y)
			result = p2 + x;
		else
			result = p2 + y;

		m = result * 1000;
		n = p2 * 1000;
		m = floor(m);
		n = floor(n);
		if (m == n) {
			return result;
		}
		p0 = p1;
		p1 = p2;
		p2 = result;
		if (i > MAXIT) {
			nrerror("Maximum number of iterations exceeded in muller");
			return 0;
		}
	}
}

int mullermethod(void) {
	
	int i, nb = NBMAX;
	float xacc, root, * xb1, * xb2;

	xb1 = vector(1, NBMAX);
	xb2 = vector(1, NBMAX);
	zbrak(fx, X1, X2, N, xb1, xb2, &nb);
	printf("\nRoots of bessj0:\n");
	printf("%21s %15s\n", "x", "f(x)");
	for (i = 1; i <= nb; i++) {
		root = muller(fx, xb1[i], (xb1[i]+xb2[i]), xb2[i]);
		printf("root %3d %14.6f %14.6f\n", i, root, fx(root));
	}
	free_vector(xb2, 1, NBMAX);
	free_vector(xb1, 1, NBMAX);
	return 0;
}

#undef NRANSI

