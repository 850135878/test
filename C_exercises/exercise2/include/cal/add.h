#ifndef ADD_H
#define ADD_H

/**
 * _Generic 根据表达式的类型选择不同的代码路径
 */
#define ADD(a, b) _Generic((a) + (b), \
    int: add_int,                     \
    long: add_long,                   \
    float: add_float,                 \
    double: add_double)(a, b)

int add_int(int x, int y);
long add_long(long x, long y);
float add_float(float x, float y);
double add_double(double x, double y);

#endif