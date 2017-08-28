#include "libs/productions.h"
#include "stack.c"
#include "../lexer/libs/tokens.h"
extern int yylex();

int lookahead;

int config_parser(int initial_prod){
    configure_stack();
    stack_up(36);
    stack_up(initial_prod);
    lookahead = yylex();
}

int parse_token(){
    while(1){
        int current_stack = stack_top(stack_data);
        int current_input = lookahead; 
        if(current_stack >= 400){
            switch(current_stack){
                case PROGR:
                    if(current_input >= 260 && current_input <= 265){
                        stack_down();
                        stack_up(REC);
                        stack_up(EOL);
                        stack_up(CMD);
                    }else{
                        return -1;
                    }
                    break;
                case REC:
                    if(current_input >= 260 && current_input <= 265){
                        stack_down();
                        stack_up(PROGR);
                    }else if(current_input == END || current_input == 36){
                        stack_down();
                    }else{
                        return -1;
                    }
                    break;
                case CMD:
                    switch(current_input){
                        case IF:
                            stack_down();
                            stack_up(CMD);
                            stack_up(THEN);
                            stack_up(EXPR);
                            stack_up(IF);
                            break;
                        case WHILE:
                            stack_down();
                            stack_up(CMD);
                            stack_up(EXPR);
                            stack_up(WHILE);
                            break;
                        case BEGN:
                            stack_down();
                            stack_up(END);
                            stack_up(PROGR);
                            stack_up(BEGN);
                            break;
                        case WRITE || READ || VAR:
                            stack_down();
                            stack_up(SCMD);
                            break;
                        default:
                            return -1;
                    }
                case SCMD:
                    switch(current_input){
                        case WRITE:
                            stack_down();
                            stack_up(VAR);
                            stack_up(WRITE);
                            break;
                        case READ:
                            stack_down();
                            stack_up(VAR);
                            stack_up(READ);
                            break;
                        case VAR:
                            stack_down();
                            stack_up(EXPR);
                            stack_up(EQ);
                            stack_up(VAR);
                            break;
                        default:
                            return -1;
                    }
                case EXPR:
                    switch(current_input){
                        case NUM:
                            stack_down();
                            stack_up(REC2);
                            stack_up(NUM);
                            break;
                        default:
                            return -1;
                    }
                case REC2:
                    switch(current_input){
                        case PLUS:
                            stack_down();
                            stack_up(EXPR);
                            stack_up(PLUS);
                            break;
                        case MINUS:
                            stack_down();
                            stack_up(EXPR);
                            stack_up(MINUS);
                            break;
                        default:
                            return -1;
                    }
            }
        }else if(current_stack >= 260 && current_input < 400){
            if(current_input == current_stack){
                stack_down();
                lookahead = yylex();
                return 0;
            }else{
                return -1;
            }
        }else{
            if(current_input == current_stack){
                stack_down();
                return 1;
            }
        }
    }
}

int run_parser(int initial_prod){
    config_parser(initial_prod);
    int valid = parse_token();
    while(valid == 0){
        valid = parse_token();
    }
    return valid;
}