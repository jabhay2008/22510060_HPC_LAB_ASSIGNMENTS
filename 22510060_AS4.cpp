// *****************************************22510060 _ HPC _ ASSIGNMENT 4******************************************
// *****************************************CODE1******************************************************************
#include <iostream>
#include <omp.h>
using namespace std;

long long fib(int n) {
    if (n < 2) return n;
    long long x, y;
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);
    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    cin >> n;

    double start = omp_get_wtime();
    long long result;

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }

    double end = omp_get_wtime();

    cout << "Fibonacci(" << n << ") = " << result << "\n";
    cout << "Time taken: " << (end - start) << " sec\n";

    return 0;
}


// *****************************************CODE2******************************************************************

#include <iostream>
#include <queue>
#include <omp.h>
using namespace std;

const int buff_SIZE = 5;  
const int PRODUCE_COUNT = 10; 

queue<int> buff;  
int prod_item = 0;
int cons_item = 0;

int main() {
    omp_set_num_threads(2); 
    double start = omp_get_wtime();

    #pragma omp parallel sections shared(buff, prod_item, cons_item)
    {
        #pragma omp section
        {
            while (prod_item < PRODUCE_COUNT) {
                #pragma omp critical
                {
                    if (buff.size() < buff_SIZE) {
                        int item = prod_item + 1;
                        buff.push(item);
                        prod_item++;
                        cout << "Producer produced: " << item << "\n";
                    }
                }
                #pragma omp flush
            }
        }

        #pragma omp section
        {
            while (cons_item < PRODUCE_COUNT) {
                #pragma omp critical
                {
                    if (!buff.empty()) {
                        int item = buff.front();
                        buff.pop();
                        cons_item++;
                        cout << "Consumer consumed: " << item << endl;
                    }
                }
                #pragma omp flush
            }
        }
    }

    double end = omp_get_wtime();
    cout << "Total time: " << (end - start) << " sec\n";
    return 0;
}
