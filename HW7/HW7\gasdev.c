
#include <math.h>

float gasdev(long* idum, float mean, float stdev)
{
	float ran1(long* idum);
	static int iset = 0;
	static float gset;
	float fac, rsq, v1, v2;

	if (*idum < 0) iset = 0;
	if (iset == 0) {
		do {
			v1 = 2 * ran1(idum) - 1;
			v2 = 2 * ran1(idum) - 1;
			rsq = v1 * v1 + v2 * v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac = sqrt(-2.0 * log(rsq) / rsq);

		gset = v1 * fac;
		gset = (stdev * gset) + mean;
		return gset;
	}
	else {
		iset = 0;
		return gset;
	}
}
