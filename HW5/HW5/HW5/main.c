#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {

	int select = -1;

	while (1) {
		printf("which method?\n");
		printf("====================================================\n");
		printf("1. gauss-joradan\n");
		printf("2. LU decomposition\n");
		printf("3. Sigular Value Decomposition\n");
		printf("0. exit\n");
		printf("====================================================\n");

		scanf("%d", &select);

		switch (select)
		{
		case 0:
			return 0;
		case 1:
			gauss();
			break;
		case 2:
			ludecomposition();
			break;
		case 3:
			singularValuedcmp();
			break;
		default:
			printf("wrong input\n");
			break;
		}

	}
}