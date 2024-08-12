#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "add.h"
#include "sub.h"
#include "div.h"
#include "mul.h"
#include "stack.h"
#include "string_tools.h"
#include "double_tools.h"

#define MATH_STRING_LEN 1024
#define EPSILON 1e-9
#define HIGHEST_DEGREE 30

typedef enum
{
    LOW = 1,
    MEDIUM,
    HIGH
} Priority;

/**
 * Gets the priority of the specified operator.
 */
Priority getPriority(const char *op)
{
    if (!strcmp(op, "+") || !strcmp(op, "-"))
    {
        return LOW;
    }
    if (!strcmp(op, "*") || !strcmp(op, "/"))
    {
        return MEDIUM;
    }
    if (!strcmp(op, "(") || !strcmp(op, ")"))
    {
        return HIGH;
    }
    return 0;
}

/**
 * Verify that the string of a mathematical expression is legal
 */
int isValidExpression(const char *str)
{
    const char *p;
    int decimalFound = 0;
    int numberFound = 0;
    char prevChar;

    if (!strlen(str) || (str[strlen(str) - 1] == '+' || str[strlen(str) - 1] == '-' || str[strlen(str) - 1] == '*' || str[strlen(str) - 1] == '/' || str[strlen(str) - 1] == '('))
    {
        return 0;
    }

    prevChar = '\0';
    p = str;
    while (*p)
    {
        // Checking characters can only be '0'-'9', '+', '-', '*', '/'. '=', '(', ')', ' ','.'
        if (!(isdigit(*p) || *p == '(' || *p == ')' ||
              *p == '+' || *p == '-' ||
              *p == '*' || *p == '/' ||
              *p == ' ' || *p == '.' || *p == '='))
        {
            return 0;
        }

        // Checking that no other characters can appear after the equal sign
        if (*p == '=' && *(p + 1) != '\0')
        {
            return 0;
        }

        // Checking for two decimal places in a numeric string
        if (*p == '.')
        {
            if (decimalFound || prevChar == '\0' || !(prevChar >= '0' && prevChar <= '9'))
            {
                return 0;
            }

            if ((*(p + 1) != '\0') && (*(p + 1) == '(' || *(p + 1) == ')'))
            {
                return 0;
            }
            decimalFound = 1;
        }
        else if (*p >= '0' && *p <= '9')
        {
            if (!numberFound && *p == '0' && (prevChar < '0' || prevChar > '9') && (*(p + 1) >= '0' && *(p + 1) <= '9'))
            {
                return 0;
            }
            numberFound = 1;
        }
        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/')
        {
            decimalFound = 0;
            numberFound = 0;
        }

        // Checking for the presence of sequential operators
        if ((*(p + 1) != '\0') && (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '=' || *p == '.') && (*(p + 1) == '+' || *(p + 1) == '-' || *(p + 1) == '*' || *(p + 1) == '/' || *(p + 1) == '=' || *(p + 1) == ')'))
        {
            return 0;
        }

        prevChar = *p;
        p++;
    }

    return 1;
}

/**
 * Perform arithmetic operations on two numbers and check for out of bounds
 */
void calculation(double num1, double num2, char op, double *result, int *overflow)
{
    switch (op)
    {
    case '+':
        if (checkAdditionOverflow(num1, num2))
        {
            *overflow = 1;
            return;
        }
        *result = ADD(num1, num2);
        break;
    case '-':
        if (checkSubtractionOverflow(num1, num2))
        {
            *overflow = 1;
            return;
        }
        *result = SUB(num1, num2);
        break;
    case '*':
        if (checkMultiplicationOverflow(num1, num2))
        {
            *overflow = 1;
            return;
        }
        *result = MUL(num1, num2);
        break;
    case '/':
        *overflow = checkDivisionOverflow(num1, num2);
        if (*overflow == 1 || *overflow == -1)
        {
            return;
        }
        *result = DIV(num1, num2);
        break;
    default:
        fprintf(stderr, "Error: Invalid operator '%c'.\n", op);
        return;
    }
    *overflow = 0;
}

/**
 * Popping two numbers from the value stack and calculating them against the operator stack
 * - Returns 0 to indicate that the operation has failed
 */
int popAndOperate(Stack *num_stack, Stack *op_stack)
{
    char *num1Str, *num2Str;
    char resStr[HIGHEST_DEGREE];
    double num1, num2, result;
    char *topOp;
    int isOverflowFlag = 0;

    num1Str = pop(num_stack);
    if (!num1Str)
    {
        return 0;
    }

    num2Str = pop(num_stack);
    if (!num2Str)
    {
        return 0;
    }

    topOp = pop(op_stack);

    if (!convertStrToDouble(num1Str, &num1) || !convertStrToDouble(num2Str, &num2))
    {
        fprintf(stderr, "Error: num_str convert to double error! \n");
        return 0;
    }

    calculation(num2, num1, topOp[0], &result, &isOverflowFlag);
    if (isOverflowFlag == -1)
    {
        fprintf(stderr, "Error: division by zero.\n");
        return 0;
    }
    else if (isOverflowFlag == 1)
    {
        fprintf(stderr, "Error: Calculation overflow detected.\n");
        return 0;
    }

    snprintf(resStr, sizeof(resStr), "%f", result);
    push(num_stack, resStr);
    return 1;
}

// Returns 0 to indicate that the operation has failed
int processOperator(Stack *num_stack, Stack *op_stack, char *op)
{
    char *topOp;
    Priority opPri;
    Priority topPri;

    if (!strcmp(op, "="))
    {
        while (!isEmpty(op_stack))
        {
            if (!popAndOperate(num_stack, op_stack))
            {
                return 0;
            }
        }
        if (num_stack->top != 0)
        {
            fprintf(stderr, "Maths formula formatting errors!\n");
            return 0;
        }
    }

    opPri = getPriority(op);
    topOp = top(op_stack);

    if (!strcmp(op, ")"))
    {
        // Pop elements from the value stack and the operator stack in turn to compute until the '(' manipulator is encountered
        while (topOp && strcmp(topOp, "("))
        {
            popAndOperate(num_stack, op_stack);
            topOp = top(op_stack);
        }

        if (!topOp)
        {
            fprintf(stderr, "Maths formula formatting error: left and right brackets don't match!\n");
            return 0;
        }
        else
        {
            pop(op_stack);
            return 1;
        }
    }

    while (!isEmpty(op_stack))
    {
        topOp = top(op_stack);
        topPri = getPriority(topOp);
        // Current priority is greater than or less than top-of-stack priority, out of the stack for numerical calculation.
        if (topPri >= opPri && strcmp(topOp, "("))
        {
            if (!popAndOperate(num_stack, op_stack))
            {
                return 0;
            }
        }
        else
        {
            break;
        }
    }
    push(op_stack, op);
    return 1;
}

void calMathExpression(const char *str, double *result, int *success)
{
    const char *p;
    char *num_str;
    int i, j; // i and j represent the index of the starting position of a possible numeric string and its length, respectively.
    int negativeIndex = -1;
    Stack *num_stack = initStack();
    Stack *op_stack = initStack();

    p = str;
    i = j = 0;
    while (*p)
    {
        if ((*p >= '0' && *p <= '9') || (*p == ' ' || *p == '.'))
        {
            // The case of the default multiplication sign after the right bracket.
            if ((*p >= '0' && *p <= '9') && i && !j && str[i - 1] == ')')
            {
                push(op_stack, "*");
            }
            j++;
            p++;
            continue;
        }
        else
        {
            // Encounter the operator and press the number string into the num_stack
            if (j)
            {
                if (negativeIndex != -1)
                {
                    num_str = substring(str, negativeIndex, j + i - negativeIndex); // negative number string
                    negativeIndex = -1;
                }
                else
                {
                    num_str = substring(str, i, j);
                    // Check if the substrings are all spaces
                    if (isAllWhitespace(num_str))
                    {
                        i += j;
                        j = 0;
                        continue;
                    }
                }

                if (!num_str)
                {
                    fprintf(stderr, "Intercept String Error!\n");
                    *success = 0;
                    return;
                }

                push(num_stack, num_str);
                free(num_str);

                if (*p == '(') // The case of the default multiplication sign before the left bracket.
                {
                    push(op_stack, "*");
                }

                i += j;
                j = 0;
            }

            switch (*p)
            {
            case '+':
                if (!processOperator(num_stack, op_stack, "+"))
                {
                    *success = 0;
                    return;
                }
                break;
            case '-':
                // Consideration of negative scenarios.
                if (!i || str[i - 1] == '(')
                {
                    negativeIndex = i;
                }
                else
                {
                    if (!processOperator(num_stack, op_stack, "-"))
                    {
                        *success = 0;
                        return;
                    }
                }
                break;
            case '*':
                if (!processOperator(num_stack, op_stack, "*"))
                {
                    *success = 0;
                    return;
                }
                break;
            case '/':
                if (!processOperator(num_stack, op_stack, "/"))
                {
                    *success = 0;
                    return;
                }
                break;
            case '(':
                // If the left bracket is preceded by a right bracket, the multiplication "*" sign is omitted.
                if (i > 0 && !j && str[i - 1] == ')')
                {
                    push(op_stack, "*");
                }
                push(op_stack, "(");
                break;
            case ')':
                if (!processOperator(num_stack, op_stack, ")"))
                {
                    *success = 0;
                    return;
                }
                break;
            case '=':
            default:
                if (!processOperator(num_stack, op_stack, "="))
                {
                    *success = 0;
                    return;
                }

                if (num_stack->top != 0)
                {
                    freeStack(num_stack);
                    freeStack(op_stack);
                    fprintf(stderr, "Maths formula formatting errors!\n");
                    *success = 0;
                    return;
                }

                if (!convertStrToDouble(top(num_stack), result))
                {
                    fprintf(stderr, "Maths formula formatting errors!\n");
                    *success = 0;
                    return;
                }
                *success = 1;
                freeStack(num_stack);
                freeStack(op_stack);
                return;
            }
        }
        i++;
        p++;
    }
}

char *appendEqualIfNeeded(char *formula)
{
    char *newFormula = NULL;
    int len = strlen(formula);
    if (formula[len - 1] == '=')
    {
        return formula;
    }

    newFormula = (char *)malloc(len + 2);
    if (!newFormula)
    {
        return NULL;
    }
    strcpy(newFormula, formula);
    newFormula[len] = '=';
    newFormula[len + 1] = '\0';
    return newFormula;
}

void showMenu()
{
    char formula[MATH_STRING_LEN];
    double res;
    int successFlag = 0;
    while (1)
    {
        printf("================请输入数学公式===================\n");
        if (fgets(formula, sizeof(formula), stdin) == NULL)
        {
            printf("Could not read the text or reached the end of the file.\n");
            exit(1);
        }

        trimWhitespace(formula);
        //  Check whether the formula string is legal
        if (!isValidExpression(formula))
        {
            fprintf(stderr, "Illegal characters in the input maths formula string. please re-enter it. \n");
            continue;
        }

        // Supplement the formula string with '=' as appropriate
        char *newFormula = appendEqualIfNeeded(formula);
        if (!newFormula)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(1);
        }

        // Calculate strings of mathematical expressions
        calMathExpression(newFormula, &res, &successFlag);
        if (!successFlag)
        {
            fprintf(stderr, "Input Formula error! Please re-enter it. \n");
            continue;
        }

        if (fabs(res - (int)res) < EPSILON)
        {
            printf("计算结果: %s%d\n", newFormula, (int)res);
        }
        else
        {
            printf("计算结果: %s%.5f\n", newFormula, res);
        }
    }
}

int main()
{
    showMenu();
}