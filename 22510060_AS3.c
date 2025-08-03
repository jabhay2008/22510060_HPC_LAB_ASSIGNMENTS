
// *****************************************22510060 _ HPC _ ASSIGNMENT 3******************************************
// *****************************************CODE1******************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int compareAsc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int compareDesc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}
int main() {
    int n = 5;
    int A[] = {1, 3, -5, 7, 9};
    int B[] = {2, -6, 4, -2, 1};

    // Sort A in ascending order
    qsort(A, n, sizeof(int), compareAsc);

    // Sort B in descending order
    qsort(B, n, sizeof(int), compareDesc);
    int minScalarProduct = 0;
    #pragma omp parallel for reduction(+:minScalarProduct)
    for (int i = 0; i < n; i++) {
        minScalarProduct += A[i] * B[i];
    }

    printf("Minimum Scalar Product = %d\n", minScalarProduct);

    return 0;
}


// *****************************************CODE2******************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX 2000

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

// Function to initialize matrices
void initialize_matrix(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }
    }
}
// Function to add matrices using OpenMP
void add_matrix(int size, int threads) {
    omp_set_num_threads(threads);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int thread_counts[] = {1, 2, 4, 8};
    int num_threads = sizeof(thread_counts) / sizeof(thread_counts[0]);

    printf("MatrixSize,Threads,Time(s)\n");

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];

        for (int t = 0; t < num_threads; t++) {
            int threads = thread_counts[t];

            initialize_matrix(size);

            double start = omp_get_wtime();
            add_matrix(size, threads);
            double end = omp_get_wtime();

            printf("%d,%d,%f\n", size, threads, end - start);
        }
    }

    return 0;
}


// *****************************************CODE3******************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200
#define SCALAR 5

void initialize_vector(int *A) {
    for (int i = 0; i < SIZE; i++) {
        A[i] = rand() % 100;
    }
}

void scalar_addition_static(int *A, int chunk, int threads) {
    omp_set_num_threads(threads);
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < SIZE; i++) {
        A[i] += SCALAR;
    }

    double end = omp_get_wtime();
    printf("STATIC | Threads: %d | Chunk: %d | Time: %f sec\n", threads, chunk, end - start);
}

void scalar_addition_dynamic(int *A, int chunk, int threads) {
    omp_set_num_threads(threads);
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < SIZE; i++) {
        A[i] += SCALAR;
    }

    double end = omp_get_wtime();
    printf("DYNAMIC | Threads: %d | Chunk: %d | Time: %f sec\n", threads, chunk, end - start);
}

// Demonstration of nowait clause
void test_nowait_clause() {
    int A[SIZE], B[SIZE];
    initialize_vector(A);
    initialize_vector(B);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < SIZE; i++)
                A[i] += SCALAR;
        }

        #pragma omp section
        {
            for (int i = 0; i < SIZE; i++)
                B[i] += SCALAR;
        }

        #pragma omp section 
        {
            printf("NOWAIT section - does not wait for other sections.\n");
        }
    }

    printf("Nowait clause example completed.\n");
}

int main() {
    int A[SIZE];

    int thread_counts[] = {2, 4, 8};
    int chunk_sizes[] = {1, 5, 10, 20, 50};

    for (int t = 0; t < 3; t++) {
        for (int c = 0; c < 5; c++) {
            initialize_vector(A);
            scalar_addition_static(A, chunk_sizes[c], thread_counts[t]);

            initialize_vector(A);
            scalar_addition_dynamic(A, chunk_sizes[c], thread_counts[t]);
        }
    }

    test_nowait_clause();

    return 0;
}

