// *****************************************22510060 _ HPC _ ASSIGNMENT 1******************************************
// *****************************************CODE1******************************************************************


#include<iostream>
#include <omp.h>
using namespace std ;

int main(void)
{
    #pragma omp parallel
    {
        cout<<"HELLO WORLD"<<endl;
    }

}

// *****************************************CODE2******************************************************************


#include<iostream>
#include<omp.h>
using namespace std;

int main()
{
    int thread = 0 ;
    cout<<"Enter the number of threads : ";
    cin>>thread;

    // printing Hello World sequential.
    cout<<endl<<"Hello world sequential"<<endl<<endl;
    for(int i = 0 ; i<thread;i++)
    {
        cout<<"Id : "<<i<<"   Hello World"<<endl;
    }

    // set the number of threads for OpenMP
     cout<<endl<<"Hello world parallel"<<endl<<endl;
    omp_set_num_threads(thread);
    #pragma omp parallel
    {
        int id  = omp_get_thread_num();
        // cout<<"Id : "<<id<<"  Hello world  "<<endl;
        cout<<"hello world"<<endl;
    }
}

// *****************************************CODE3******************************************************************


#include<iostream>
#include<omp.h>
using namespace std ;
int main()
{

    int cores = 0 ; float clock_speed = 0; int fps = 0;

    double Flops= 0;
    cout<<"Enter the number of cores : ";
    cin>>cores;
    cout<<"Enter the clock speed in GHz : ";
    cin>>clock_speed;
    cout<<"Enter the FPS : ";
    cin>>fps;
    Flops = cores * clock_speed * fps ;// 1 GHz = 10^9 Hz
    cout<<"The FLOPS of the system is : "<<Flops<<" GFLOPS"<<endl;

}