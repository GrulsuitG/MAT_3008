#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#define NRANSI
#include "nr.h"



#define MEAN 0
#define S 1.0
#define NP 11

int main()
{
    int i, j, nrot;
    long seed;
  
    float* d, ** v, ** e;
    static float c[NP][NP] = { 0 };

    seed = -time(NULL);
    //make a random matrix
    for(i =0; i<NP; i++)
    {
        for (j = 0; j <= i; j++) {
            c[i][j] =  gasdev(&seed, MEAN, S);
        }
    }
    //make a symmetric matrix
    for (i = 0; i < NP; i++)
    {
        for (j = i + 1; j < NP; j++)
        {
            c[i][j] = c[j][i];
        }
    }

    d = vector(1, NP);
    v = matrix(1, NP, 1, NP);
    e = convert_matrix(&c[0][0], 1, NP, 1, NP);
    
    jacobi(e, NP, d, v, &nrot);
    eigsrt(d, v, NP);

    for (i = 1;i <= NP;i++) {
        printf("eigenvalue %3d = %12.6f\n", i, d[i]);
        printf("eigenvector:\n");
        for (j = 1;j <= NP;j++) {
            printf("%12.6f", v[j][i]);
            if ((j % 6) == 0) printf("\n");
        }
        printf("\n");
    }
    free_convert_matrix(e, 1, NP, 1, NP);
    free_matrix(v, 1, NP, 1, NP);
    free_vector(d, 1, NP);
    
 
    return 0;
}

#undef   NRANSI