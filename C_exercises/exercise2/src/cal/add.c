#include <stdio.h>
#include "add.h"

#define ADD_IMPL(type, x, y) ((type)(x) + (type)(y))

int add_int(int x, int y)
{
    return ADD_IMPL(int, x, y);
}

long add_long(long x, long y)
{
    return ADD_IMPL(long, x, y);
}

float add_float(float x, float y)
{
    return ADD_IMPL(float, x, y);
}

double add_double(double x, double y)
{
    return ADD_IMPL(double, x, y);
}
