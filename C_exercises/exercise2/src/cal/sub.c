#include "sub.h"
#define SUB_IMPL(type, x, y) ((type)(x) - (type)(y))

int sub_int(int x, int y)
{
    return SUB_IMPL(int, x, y);
}

long sub_long(long x, long y)
{
    return SUB_IMPL(long, x, y);
}

float sub_float(float x, float y)
{
    return SUB_IMPL(float, x, y);
}

double sub_double(double x, double y)
{
    return SUB_IMPL(double, x, y);
}