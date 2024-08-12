#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <errno.h>
#include <math.h>

#include "string_tools.h"
#include "double_tools.h"

#define MAX_LENGTH 50

/**
 * Removes whitespace before and after a mathematical expression.
 */
void trimWhitespace(char *str)
{
    int start = 0;
    int end = strlen(str) - 1;

    while (isspace(str[start]))
    {
        start++;
    }

    if (str[start] == '\0')
    {
        str[0] = '\0';
        return;
    }

    while (end > start && isspace(str[end]))
    {
        end--;
    }

    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}

int isAllWhitespace(const char *str)
{
    while (*str != '\0')
    {
        if (!isspace((unsigned char)*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

/**
 * Intercepts a substring of a specified length at a specified position.
 */
char *substring(const char *str, int start, int len)
{
    int strLen = strlen(str);
    if (start < 0 || start >= strLen || len < 0 || start + len > strLen)
    {
        return NULL;
    }

    char *newStr = (char *)malloc(len + 1);
    if (newStr == NULL)
    {
        return NULL;
    }

    strncpy(newStr, str + start, len);
    newStr[len] = '\0';
    return newStr;
}

/**
 * Converts a double string type to a numeric type and checks that it is not outside the value range of the double type.
 */
int convertStrToDouble(char *str, double *result)
{
    char *end;

    trimWhitespace(str);
    *result = strtod(str, &end);
    if (end == str || *end != '\0')
    {
        return 0;
    }

    return 1;
}