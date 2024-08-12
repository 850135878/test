#include "div.h"

#define DIV_IMPL(type, x, y) ((type)(x) / (type)(y))

int div_int(int x, int y)
{
    return DIV_IMPL(int, x, y);
}

long div_long(long x, long y)
{
    return DIV_IMPL(long, x, y);
}

float div_float(float x, float y)
{
    return DIV_IMPL(float, x, y);
}

double div_double(double x, double y)
{
    return DIV_IMPL(double, x, y);
}