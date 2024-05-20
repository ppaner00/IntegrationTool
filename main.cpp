#include <iostream>
#include <functional>
#include <cmath>
#include <string>

double trapezoidalRule(std::function<double(double)> func, double a, double b, int n);
double selectFunction(const std::string& funcName, double x);
void runIntegrationTool();

int main() {
    runIntegrationTool();
    return 0;
}

void runIntegrationTool() {
    std::string funcName;
    double a, b;
    int n;

    // User input for the function
    std::cout << "Select the function to integrate (options: x^2, sin(x), cos(x)): ";
    std::cin >> funcName;

    // User input for the interval
    std::cout << "Enter the lower bound of the interval: ";
    std::cin >> a;
    std::cout << "Enter the upper bound of the interval: ";
    std::cin >> b;

    // User input for the number of trapezoids
    std::cout << "Enter the number of trapezoids (precision): ";
    std::cin >> n;

    std::function<double(double)> func = [funcName](double x) { return selectFunction(funcName, x); };

    double result = trapezoidalRule(func, a, b, n);

    std::cout << "The integral of " << funcName << " from " << a << " to " << b << " is approximately " << result << std::endl;
}

// Function to select and evaluate the user-defined function
double selectFunction(const std::string& funcName, double x) {
    if (funcName == "x^2") {
        return x * x;
    } else if (funcName == "sin(x)") {
        return std::sin(x);
    } else if (funcName == "cos(x)") {
        return std::cos(x);
    } else {
        std::cerr << "Unknown function!" << std::endl;
        return 0.0;
    }
}

// Trapezoidal Rule function
double trapezoidalRule(std::function<double(double)> func, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));

    for (int i = 1; i < n; i++) {
        sum += func(a + i * h);
    }

    return sum * h;
}
