#define _CRT_SECURE_NO_WARNINGS

#include "nr.h"
#include <stdio.h>
#include <time.h>

#define SIZE 10000
#define INTERVAL 100
#define MAX 2
#define MIN -3
#define MEAN 0.5
#define S 1.5
#define NPTS 10000
#define ISCAL 500
#define LLEN 50

int main()
{
    int i, j, klim;
    long seed;
    float dd;
    double rn, d, block;      
    seed = -time(NULL);
    int num[INTERVAL] = { 0 };
    int num2[10] = { 0 };

    d = MAX - MIN;
    block = d/INTERVAL;


    printf("Uniform distribution in [%d,%d]\n", MIN, MAX);
    for (i = 0;i < SIZE;i++)
    {
        rn = ran1(&seed)*d+MIN;
        for (j = 0; j < INTERVAL; j++) {
            if ((MIN + j * block <= rn) && (rn < MIN + (j + 1) * block)) {
                num[j]++;
                break;
            }
        }
    }
    printf("%10s %10s %9s\n", "x", "p(x)", "graph:");
    for (i = 0; i < INTERVAL; i++) {
        dd = (float)num[i] / NPTS;
        printf("(%5.2f ~ %5.2f) %.4f : ", MIN + i * block, MIN + (i + 1) * block,dd);
        klim = (int)(ISCAL * dd);
        if (klim > LLEN)  klim = LLEN;
        for (j = 0; j < klim; j++)
            printf("*");
        printf("\n");
    }

    printf("\n\nGaussian Distribution with mean = %.2f, standard deviation = %.2f\n", MEAN, S);
    printf("%10s %10s %9s\n", "x", "p(x)", "graph:");
    for (i = 0;i < SIZE;i++)
    {
        rn = gasdev(&seed, MEAN, S, MAX, MIN);
        for (j = 0; j < 10; j++) {
            if ((MIN + j * S/3 <= rn) && (rn < MIN + (j + 1) * S/3)) {
                num2[j]++;
                break;
            }
        }
    }
    for (i = 0; i < 10; i++) {
        dd = (float)num2[i] / NPTS;
        printf("(%5.2f ~ %5.2f) %.4f : ", MIN + i * S/3, MIN + (i + 1) * S/3, dd);
        klim = (int)(ISCAL * dd);
        if (klim > LLEN)  klim = LLEN;
        for (j = 0; j < klim; j++)
            printf("*");
        printf("\n");
    }


    return 0;
}