#include <iostream>
#include <stdlib.h>
#include <math.h>

const unsigned int ITERATIONS = 100000;

double riemann (double a, double b, unsigned int n, double x);
double lambert (double i, double x);

int main(int argc, char* args[]) {
    std::cout << "Approximation: " << riemann(0, M_PI, ITERATIONS, atof(args[1])) * -2.0 / M_PI << std::endl;
    return 0;
}

double riemann (double a, double b, unsigned int n, double x) {
    const double step = (b-a)/(double)n;
    double sum = 0;
    for (double i = a; i < b; i += step) {
        sum += step * lambert(i, x);
    }
    return sum;
}

double lambert (double t, double x) {
    double numerator = x * exp(cos(t));
    numerator *= sin(5*t/2 - sin(t));
    numerator += sin(3*t/2);
    numerator *= sin(1*t/2);

    double denominator = 2 * x * exp(cos(t));
    denominator *= cos(t-sin(t));
    denominator += pow(x, 2) * exp(2 * cos(t));
    denominator += 1;

    return numerator/denominator;
}
