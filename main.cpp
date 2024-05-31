#include <iostream>
#include <functional>
#include <cmath>
#include <string>
#include "exprtk.hpp" // External library

double trapezoidalRule(std::function<double(double)> func, double a, double b, int n);
double selectFunction(const std::string& funcName, double x);
void runIntegrationTool();
double parseConstant(const std::string& str);

int main() {
    runIntegrationTool();
    return 0;
}

void runIntegrationTool() {
    std::string funcName;
    std::string a_str, b_str;
    double a, b;
    int n;

    // User input for the function
    std::cout << "Select the function to integrate: ";
    std::cin >> funcName;

    // User input for the interval
    std::cout << "Enter the lower bound: ";
    std::cin >> a_str;
    std::cout << "Enter the upper bound: ";
    std::cin >> b_str;

    a = parseConstant(a_str);
    b = parseConstant(b_str);

    // User input for the number of trapezoids
    std::cout << "Enter the number of trapezoids: ";
    std::cin >> n;

    std::function<double(double)> func;

    if (funcName == "x^2" || funcName == "sin(x)" || funcName == "cos(x)") {
        func = [funcName](double x) { return selectFunction(funcName, x); };
    } else {
        exprtk::symbol_table<double> symbol_table;
        double variable = 0.0;
        symbol_table.add_variable("x", variable);
        exprtk::expression<double> expression;
        expression.register_symbol_table(symbol_table);
        exprtk::parser<double> parser;

        if (!parser.compile(funcName, expression)) {
            std::cerr << "Error: Invalid function expression!" << std::endl;
            return;
        }

        func = [expression, &variable](double x) mutable {
            variable = x;
            return expression.value();
        };
    }

    double result = trapezoidalRule(func, a, b, n);

    std::cout << "The integral of " << funcName << " from " << a_str << " to " << b_str << " is approximately " << result << std::endl;
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

// Parsing constants such as PI
double parseConstant(const std::string& str) {
    if (str == "pi") {
        return M_PI;
    } else {
        try {
            return std::stod(str);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: invalid input for interval bounds" << std::endl;
            exit(1);
        }
    }
}

// Trapezoidal Rule
double trapezoidalRule(std::function<double(double)> func, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));

    for (int i = 1; i < n; i++) {
        sum += func(a + i * h);
    }

    return sum * h;
}
