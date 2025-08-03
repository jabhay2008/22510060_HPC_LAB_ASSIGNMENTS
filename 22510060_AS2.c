
// *****************************************22510060 _ HPC _ ASSIGNMENT 2******************************************
// *****************************************CODE1******************************************************************
#include <stdio.h>
#include <omp.h>

int main()
{
    int length = 0;
    int scaler = 0.0;
    printf("Enter the length of Vector : ");
    scanf("%d", &length);

    printf("Enter the scaler : ");
    scanf("%d", &scaler);

    double arr[length];
    double ar[length];

    printf("Enter the digits of the vector :");
    for (int i = 0; i < length; i++)
    {
        scanf("%lf", &arr[i]);
    }

#pragma omp parallel
    {
        for (int j = 0; j < length; j++)
        {
            ar[j] = arr[j] + scaler;
        }
    }

    for (int j = 0; j < length; j++)
    {

        printf("%lf \n", ar[j]);
    }
}


// *****************************************CODE2******************************************************************


#include <stdio.h>
#include<omp.h>

int main() 
{
    long long num_steps = 1000000000; 
    double step, x, pi, sum = 0.0;
    long long i;
    step = 1.0 / (double)num_steps;
#pragma omp parallel 
{
    for (i = 0; i < num_steps; i++) 
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

}
    
    pi = step * sum;

    printf("Calculated Pi = %.15f\n", pi);

    return 0;
}
