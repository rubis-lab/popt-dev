// g++ -fopenmp -o main main.cpp


#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char *arvg[]){
    int n = 4;
    for(int i = 1; i < 4; i++){
        printf("Running %d threads...\n", n);
        omp_set_dynamic(0);
        omp_set_num_threads(n);
        #pragma omp parallel
        {
            printf("Hello, World! %d\n", omp_get_thread_num());
        }
        n += i;
    }
    return 0;
}