#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>

int main(void) {
	int select = -1;

	while (1) {
		printf("which method?\n");
		printf("====================================================\n");
		printf("1. bisection\n");
		printf("2. linear Interpolation\n");
		printf("3. newton-rapson\n");
		printf("4. newton With Bracketing\n");
		printf("5. secant\n");
		printf("6. muller\n");
		printf("7. otherfunc\n");
		printf("0. exit\n");
		printf("====================================================\n");

		scanf("%d", &select);

		switch (select)
		{
		case 0:
			return 0;
		case 1:
			bisection();
			break;
		case 2:
			linearinterpolation();
			break;
		case 3:
			newtonrapson();
			break;
		case 4:
			newtonWB();
			break;
		case 5:
			secant();
			break;
		case 6:
			mullermethod();
			break;
		case 7:
			otherfunc();
			break;
		default:
			printf("wrong input\n");
			break;
		}
	}
}