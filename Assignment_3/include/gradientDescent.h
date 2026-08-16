#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

double evaluatePolynomial(int degree, double coefficients[], double x);

double gradientDescent(
    int degree,
    double coefficients[],
    double initialX,
    double learningRate,
    double tolerance,
    int maxIterations,
    int *iterations
);

#endif