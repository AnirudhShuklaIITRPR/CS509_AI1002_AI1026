#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "C:\\Users\\Dell\\Downloads\\CS509\\BUDDY\\Assignment_3\\include\\gradientDescent.h"

double evaluatePolynomial(int degree, double coefficients[], double x){
    double result = 0.0;
    double power = 1.0;

    for (int i = 0; i <= degree; i++){
        result += coefficients[i] * power;
        power *= x;
    }

    return result;
}


double evaluateDerivative(int degree, double coefficients[], double x){
    double result = 0.0;
    double power = 1.0;

    for (int i = 1; i <= degree; i++){
        result += i * coefficients[i] * power;
        power *= x;
    }

    return result;
}


double gradientDescent(int degree, double coefficients[], double initialX, double learningRate,
    double tolerance, int maxIterations, int *iterations){
    double x = initialX;

    *iterations = 0;

    for (int i = 0; i < maxIterations; i++){
        double gradient = evaluateDerivative(degree, coefficients, x);
        if (fabs(gradient) <= tolerance){
            *iterations = i;
            return x;
        }

        double newX = x - learningRate * gradient;
        *iterations = i + 1;
        if (fabs(newX - x) <= tolerance){
            x = newX;
            return x;
        }

        x = newX;
    }

    return x;
}