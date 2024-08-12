/***
 * @Author: git config user.name && git config user.email
 * @Date: 2024-08-02 16:27:13
 * @LastEditors: git config user.name && git config user.email
 * @LastEditTime: 2024-08-05 17:50:58
 * @FilePath: /vs_workspace/5.c_language/homework/exercise2/include/cal/mul.h
 * @Description:
 * @
 * @Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#ifndef MUL_H
#define MUL_H

/**
 * _Generic 根据表达式的类型选择不同的代码路径
 */
#define MUL(a, b) _Generic((a) + (b), \
    int: mul_int,                     \
    long: mul_long,                   \
    float: mul_float,                 \
    double: mul_double)(a, b)

int mul_int(int x, int y);
long mul_long(long x, long y);
float mul_float(float x, float y);
double mul_double(double x, double y);

#endif
