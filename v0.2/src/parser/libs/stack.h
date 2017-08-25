#ifndef STACK_H_
#define STACK_H_

struct Stack;
void stack_up(struct Stack, int);
int stack_down(struct Stack);
int stack_top(struct Stack);

#endif