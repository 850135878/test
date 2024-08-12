#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "double_tools.h"

#define EPSILON 1e-10
#define MAX_DOUBLE 10e22
#define MIN_DOUBLE -10e22

// Checks if the addition of two numbers is out of the range of the double type.
int checkAdditionOverflow(double num1, double num2)
{
    if ((num1 > 0 && num2 > MAX_DOUBLE - num1) ||
        (num1 < 0 && num2 < -MAX_DOUBLE - num1))
    {
        return 1;
    }
    return 0;
}

// Checks if the subtraction of two numbers is out of the double type range.
int checkSubtractionOverflow(double num1, double num2)
{
    if ((num1 > 0 && num2 < -MAX_DOUBLE + num1) ||
        (num1 < 0 && num2 > MAX_DOUBLE + num1))
    {
        return 1;
    }
    return 0;
}

// Checks if the multiplication of two numbers is out of the double type range.
int checkMultiplicationOverflow(double num1, double num2)
{
    if ((num1 > 0 && (num2 > MAX_DOUBLE / num1 || num2 < MIN_DOUBLE / num1)) ||
        (num1 < 0 && (num2 < MAX_DOUBLE / num1 || num2 > MIN_DOUBLE / num1)))
    {
        return 1;
    }
    return 0;
}

// Checks if the division of two numbers is outside the double type range or if the divisor is zero.
int checkDivisionOverflow(double num1, double num2)
{
    if (fabs(num2) < EPSILON)
    {
        return -1;
    }
    if ((num1 > 0 && (num2 > MAX_DOUBLE / num1 || num2 < MIN_DOUBLE / num1)) ||
        (num1 < 0 && (num2 < MAX_DOUBLE / num1 || num2 > MIN_DOUBLE / num1)))
    {
        return 1;
    }
    return 0;
}