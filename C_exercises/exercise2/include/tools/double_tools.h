#ifndef DOUBLE_TOOLS_H
#define DOUBLE_TOOLS_H

#define MAX_DOUBLE_NUM "10000000000000000000000"
#define MIN_DOUBLE_NUM "-10000000000000000000000"
// Checks if the addition of two numbers is out of the range of the double type.
int checkAdditionOverflow(double num1, double num2);

// Checks if the subtraction of two numbers is out of the double type range.
int checkSubtractionOverflow(double num1, double num2);

// Checks if the multiplication of two numbers is out of the double type range.
int checkMultiplicationOverflow(double num1, double num2);

// Checks if the division of two numbers is outside the double type range or if the divisor is zero.
int checkDivisionOverflow(double num1, double num2);

#endif