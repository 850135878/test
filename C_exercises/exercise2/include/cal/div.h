/***
 * @Author: git config user.name && git config user.email
 * @Date: 2024-08-02 16:27:30
 * @LastEditors: git config user.name && git config user.email
 * @LastEditTime: 2024-08-05 17:49:04
 * @FilePath: /vs_workspace/5.c_language/homework/exercise2/include/cal/div.h
 * @Description:
 * @
 * @Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#ifndef DIV_H
#define DIV_H

#define DIV(a, b) _Generic((a) - (b), \
    int: div_int,                     \
    long: div_long,                   \
    float: div_float,                 \
    double: div_double)(a, b)

int div_int(int x, int y);
long div_long(long x, long y);
float div_float(float x, float y);
double div_double(double x, double y);

#endif