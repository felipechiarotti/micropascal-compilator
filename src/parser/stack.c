int stack_data[100];
int stack_size;


void configure_stack(){
    stack_size = 0;
}
void stack_up(int value){
    stack_data[stack_size] = value;
    stack_size++;
}

int stack_down(){
    int valor = stack_data[stack_size];
    stack_data[stack_size] = 0;
    stack_size--;
    return valor;
}

int stack_top(){
    return stack_data[stack_size-1];
}

void show_stack(){
    for( int i = stack_size-1; i >= 0; i--){
        printf("***%d\n", stack_data[i]);
    }
}