#include "libs/stack.h"
struct Stack{
    int data[100];
    int size;
};

void stack_up(struct Stack stack, int value){
    stack.data[stack.size] = value;
    stack.size++;
}

int stack_down(struct Stack stack){
    int valor = stack.data[stack.size];
    stack.data[stack.size] = 0;
    return valor;
}

int stack_top(struct Stack stack){
    return stack.data[stack.size];
}