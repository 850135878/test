
#ifndef SUB_H
#define SUB_H

/**
 * _Generic 根据表达式的类型选择不同的代码路径
 */
#define SUB(a, b) _Generic((a) + (b), \
    int: sub_int,                     \
    long: sub_long,                   \
    float: sub_float,                 \
    double: sub_double)(a, b)

int sub_int(int x, int y);
long sub_long(long x, long y);
float sub_float(float x, float y);
double sub_double(double x, double y);

#endif