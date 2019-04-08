#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#include <chrono>

typedef std::ratio<1, 1000000000000> pico;
typedef std::chrono::duration<long long, pico> picoseconds;

// Number of times to iterate Newton's Method
const unsigned int ITERATIONS = 10;

double lambert_newton(double n);
double newton (double x, double n);
double lambert(double x, double n);
double lambert_newton_full(double n);

int main(int argc, char* args[]) {
    double x = 1;
    if (argc > 1) x = atof(args[1]);
    std::cout << "Approximation: " << lambert_newton(x) << std::endl; // Run Newton's method and print it out
    std::cout << "Approximation: " << lambert_newton_full(x) << std::endl;

    return 0;
}

// Approximate the Lambert Omega function using Newton's Method
double lambert_newton(double n) {
    // Start timing
    //std::cout << "Starting" << std::endl;
    //auto start = std::chrono::high_resolution_clock::now();

    // Initialize 0 as the starting guess and iterate Newton's Method ITERATIONS number of times
    double value = 0;
    for (unsigned int i = 0; i < ITERATIONS; i++) {
        value = newton(value, n);
    }

    // Finish timing and print out time
//    auto stop = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<picoseconds>(stop - start).count();
//    std::cout << "Duration: " << duration << "ns" << std::endl;

    return value;
}


double lambert_newton_full(double n) {
    // Start timing
    std::cout << "Starting" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    double output = 0;
    double numerator ;
    double denominator ;

    // Initialize 0 as the starting guess and iterate Newton's Method ITERATIONS number of times
    double value = 0;
    for (unsigned int i = 0; i < ITERATIONS; i++)
    {
        std::cout << "Value: " << value << std::endl;
        numerator = value;
        numerator -= n / exp(value);
        denominator = value + 1;
        output =  numerator / denominator;

        value -= output;
    }

    // Finish timing and print out time
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<picoseconds>(stop - start).count();
    std::cout << "Duration: " << duration << "ps" << std::endl;

    return value;
}

// Takes a guess and a value to solve for (n) and performs one Newton's Method iteration on it
/* double newton_full (double x, double n)
{
    double output = 0;
    double numerator = value;
    numerator -= n / exp(x);

    double denominator = x + 1;

    output =  numerator / denominator;


    return x - output;
}
*/

double newton (double x, double n) {
    return x - lambert(x, n);
}

// Returns the value of xe^x devided by its derivative
double lambert(double x, double n) {
    double numerator = x;
    numerator -= n / exp(x);

    double denominator = x + 1;

    return numerator / denominator;
}
