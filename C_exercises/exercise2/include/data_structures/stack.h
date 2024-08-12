
#ifndef STACK_H
#define STACK_H

#define INITIAL_CAPACITY 10
#define EXPANSION_FACTOR 2

typedef struct
{
    char **data;  /* dynamic array */
    int top;      /* top-of-stack index */
    int capacity; /* stack capacity */
} Stack;

Stack *initStack();
void freeStack(Stack *s);
int isEmpty(const Stack *s);
int isFull(const Stack *s);
void push(Stack *s, const char *val);
char *pop(Stack *s);
char *top(const Stack *s);

#endif
