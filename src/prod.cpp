// product_log.cpp
#include "product_log.h"
#include <omp.h>
#include <iostream>
using namespace std;
// Function to initialize the array
void initialize_array(int* a, int size, int value) {
    for (int i = 0; i < size; i++) {
        a[i] = value;
    }
}

// Function to compute the sum of logarithms in parallel
double compute_log_sum(int* a, int size, int num_threads) {
    double log_sum = 0.0;

    #pragma omp parallel for default(shared) reduction(+:log_sum) num_threads(num_threads)
    for (int i = 0; i < size; i++) {
        log_sum += log(a[i]);
    }

    return log_sum;
}

// Function to compute the product using the sum of logarithms
double compute_product(double log_sum) {
    return exp(log_sum);
}



#define ARR_SIZE 100

int main(int argc, char *argv[]) {
    int a[ARR_SIZE];
    int num_threads = 4; // Set the number of threads

    // Initialize array
    initialize_array(a, ARR_SIZE, 2);

    // Compute the log sum in parallel
    double log_sum = compute_log_sum(a, ARR_SIZE, num_threads);

    // Compute the product using the log sum
    double prod = compute_product(log_sum);

    // Print the result
    cout << "Product=" << prod << endl;

    return 0;
}
