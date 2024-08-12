#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

void trimWhitespace(char *str);
int isAllWhitespace(const char *str);
char *substring(const char *str, int start, int len);
int convertStrToDouble(char *str, double *result);

#endif