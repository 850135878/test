#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

/* Initialising the stack. */
Stack *initStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (!s)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    s->data = (char **)malloc(sizeof(char *) * INITIAL_CAPACITY);
    if (!s->data)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    s->top = -1;
    s->capacity = INITIAL_CAPACITY;

    return s;
}

/* Freeing dynamically allocated memory on the stack. */
void freeStack(Stack *s)
{
    if (s == NULL)
        return;

    for (int i = 0; i < s->capacity; i++)
    {
        free(s->data[i]);
    }
    free(s->data);
    s->data = NULL;
    s->capacity = 0;
    s->top = -1;
    free(s);
}

/* Check if the stack is empty. */
int isEmpty(const Stack *s)
{
    return s->top == -1;
}

/* Check if the stack is full. */
int isFull(const Stack *s)
{
    return s->top == s->capacity - 1;
}

/* Stack expansion. */
void resizeStack(Stack *s)
{
    s->capacity *= EXPANSION_FACTOR;
    s->data = (char **)realloc(s->data, s->capacity * sizeof(char *));
    if (!s->data)
    {
        fprintf(stderr, "Memory reallocation failed!\n");
        exit(1);
    }
}

/* Push the val on the stack. */
void push(Stack *s, const char *val)
{
    if (isFull(s))
    {
        /* If the stack is full, it is automatically expanded */
        resizeStack(s);
    }
    s->data[++(s->top)] = (char *)malloc((strlen(val) + 1) * sizeof(char));
    if (!s->data[s->top])
    {
        fprintf(stderr, "Value's memory reallocation failed!\n");
        exit(1);
    }
    strcpy(s->data[s->top], val);
}

/* Push val off the stack. */
char *pop(Stack *s)
{
    if (isEmpty(s))
    {
        return NULL;
    }
    char *val = s->data[s->top];
    s->data[s->top--] = NULL;
    return val;
}

/* Get the top element of the stack. */
char *top(const Stack *s)
{
    if (isEmpty(s))
    {
        return NULL;
    }
    return s->data[s->top];
}