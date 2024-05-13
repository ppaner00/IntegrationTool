#include <iostream>
#include <functional> 

double trapezoidalRule(std::function<double(double)> func, double a, double b, int n);

int main() {
    
    auto func = [](double x) -> double { return x * x; }; // f(x) = x^2

    double a = 0; // Lower bound
    double b = 1; // Upper bound

    // Number of trapezoids
    int n = 100;

    double result = trapezoidalRule(func, a, b, n);

    std::cout << "The integral of x^2 from " << a << " to " << b << " is approximately " << result << std::endl;

    return 0;
}

double trapezoidalRule(std::function<double(double)> func, double a, double b, int n) {
    double h = (b - a) / n; 
    double sum = 0.5 * (func(a) + func(b)); 

    for (int i = 1; i < n; i++) {
        sum += func(a + i * h); 
    }

    return sum * h; 
}

