#include "mul.h"

#define MUL_IMPL(type, x, y) ((type)(x) * (type)(y))

int mul_int(int x, int y)
{
    return MUL_IMPL(int, x, y);
}
long mul_long(long x, long y)
{
    return MUL_IMPL(long, x, y);
}
float mul_float(float x, float y)
{
    return MUL_IMPL(float, x, y);
}

double mul_double(double x, double y)
{
    return MUL_IMPL(double, x, y);
}