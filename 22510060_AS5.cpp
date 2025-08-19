// *****************************************22510060 _ HPC _ ASSIGNMENT 5******************************************
// *****************************************CODE1******************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500 

int main() {
    static int A[N][N], B[N][N], C[N][N];
    int i, j, k;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++) 
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }

    double st = omp_get_wtime();

    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
             for (k = 0; k < N; k++)
             {
                 C[i][j] += A[i][k] * B[k][j];
             }
        }
    }
    double end = omp_get_wtime();
    printf("Matrix-Matrix Multiplication completed in %f seconds\n", end - st);

    return 0;
}
// *****************************************CODE2******************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int r = 500;
    int c = 500;
    int A[r][c];
    int scalar = 5;

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            A[i][j] = rand() % 10;

    double st = omp_get_wtime();

    #pragma omp parallel for private(i, j) shared(A, scalar)
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            A[i][j] *= scalar;

    double end = omp_get_wtime();
    printf("Matrix-Scalar Multiplication completed in %f seconds\n", end - st);

    return 0;
}
// *****************************************CODE3******************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main() {
    int N = 500;
    int A[N][N], x[N], y[N];

    for (int i = 0; i < N; i++) {
        x[i] = rand() % 10;
        for (int j = 0; j < N; j++)
            A[i][j] = rand() % 10;
    }

    double st = omp_get_wtime();

    #pragma omp parallel for private(i, j) shared(A, x, y)
    for (int i = 0; i < N; i++) {
        y[i] = 0;
        for (int j = 0; j < N; j++)
            y[i] += A[i][j] * x[j];
    }

    double end = omp_get_wtime();
    printf("Matrix-Vector Multiplication completed in %f seconds\n", end - st);

    return 0;
}

// *****************************************CODE4******************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int N =  1000000;
    int arr[N], pre[N];
    for (int i = 0; i < N; i++)
        arr[i] = 1; 

    double st = omp_get_wtime();

    pre[0] = arr[0];
    #pragma omp parallel for
    for (int i = 1; i < N; i++)
        pre[i] = pre[i - 1] + arr[i]; 

    double end = omp_get_wtime();
    printf("Prefix sum completed in %f seconds\n", end - st);

    return 0;
}
