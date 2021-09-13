#include <stdio.h>

void get_eps_f(float *negeps, float *eps) {
	float temp = 1;

	while ((1 + temp) != 1) {
		*eps = temp;
		temp /= 2;
	}

	temp = 1;
	while ((1 - temp) != 1) {
		*negeps = temp;
		temp /= 2;
	}
}

void get_eps_d(double* negeps, double* eps) {
	double temp = 1;

	while ((1 + temp) != 1) {
		*eps = temp;
		temp /= 2;
	}

	temp = 1;
	while ((1 - temp) != 1) {
		*negeps = temp;
		temp /= 2;
	}
}

int main() {

	float f_eps, f_neps;
	double d_eps, d_neps;
	get_eps_f(&f_neps, &f_eps);
	get_eps_d(&d_neps, &d_eps);
	printf("Machine Accuracy in float\n");
	printf("eps = %12.6g\n", f_eps);
	printf("negeps = %12.6g\n", f_neps);
	printf("\n======================================================\n\n");
	printf("Machine Accuracy in double\n");
	printf("eps = %12.6g\n", d_eps);
	printf("negeps = %12.6g\n", d_neps);
	return 0;

}