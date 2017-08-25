#include "libs/parser.h"

struct Parser{
    int lookahead;
    struct Stack stack;
};

int config_parser(struct Parser parser, int initial_prod){
    stack_up(parser.stack, 36);
    stack_up(parser.stack, initial_prod);
    parser.lookahead = yylex();
}

int run_parser(struct Parser parser, int initial_prod){
    config_parser(parser, initial_prod);
    int valid = parse_token(parser);
    while(valid == 0){
        valid = parse_token(parser);
    }
    return valid;
}

int parse_token(struct Parser parser){
    while(1){
        int current_stack = stack_top(parser.stack);
        int current_input = parser.lookahead; 
        if(current_stack >= 400){
            switch(current_stack){
                case PROGR:
                    if(current_input >= 260 && current_input <= 265){
                        stack_down(parser.stack);
                        stack_up(parser.stack, REC);
                        stack_up(parser.stack, EOL);
                        stack_up(parser.stack, CMD);
                    }else{
                        return -1;
                    }
                    break;
                case REC:
                    if(current_input >= 260 && current_input <= 265){
                        stack_down(parser.stack);
                        stack_up(parser.stack, PROGR);
                    }else if(current_input == END || current_input == 36){
                        stack_down(parser.stack);
                    }else{
                        return -1;
                    }
                    break;
                case CMD:
                    switch(current_input){
                        case IF:
                            stack_down(parser.stack);
                            stack_up(parser.stack, CMD);
                            stack_up(parser.stack, THEN);
                            stack_up(parser.stack, EXPR);
                            stack_up(parser.stack, IF);
                            break;
                        case WHILE:
                            stack_down(parser.stack);
                            stack_up(parser.stack, CMD);
                            stack_up(parser.stack, EXPR);
                            stack_up(parser.stack, WHILE);
                            break;
                        case BEGN:
                            stack_down(parser.stack);
                            stack_up(parser.stack, END);
                            stack_up(parser.stack, PROGR);
                            stack_up(parser.stack, BEGN);
                            break;
                        case WRITE || READ || VAR:
                            stack_down(parser.stack);
                            stack_up(parser.stack, SCMD);
                            break;
                        default:
                            return -1;
                    }
                case SCMD:
                    switch(current_input){
                        case WRITE:
                            stack_down(parser.stack);
                            stack_up(parser.stack, VAR);
                            stack_up(parser.stack, WRITE);
                            break;
                        case READ:
                            stack_down(parser.stack);
                            stack_up(parser.stack, VAR);
                            stack_up(parser.stack, READ);
                            break;
                        case VAR:
                            stack_down(parser.stack);
                            stack_up(parser.stack, EXPR);
                            stack_up(parser.stack, EQ);
                            stack_up(parser.stack, VAR);
                            break;
                        default:
                            return -1;
                    }
                case EXPR:
                    switch(current_input){
                        case NUM:
                            stack_down(parser.stack);
                            stack_up(parser.stack, REC2);
                            stack_up(parser.stack, NUM);
                            break;
                        default:
                            return -1;
                    }
                case REC2:
                    switch(current_input){
                        case PLUS:
                            stack_down(parser.stack);
                            stack_up(parser.stack, EXPR);
                            stack_up(parser.stack, PLUS);
                            break;
                        case MINUS:
                            stack_down(parser.stack);
                            stack_up(parser.stack, EXPR);
                            stack_up(parser.stack, MINUS);
                            break;
                        default:
                            return -1;
                    }
            }
        }else if(current_stack >= 260 && current_input < 400){
            if(current_input == current_stack){
                stack_down(parser.stack);
                parser.lookahead = yylex();
                return 0;
            }else{
                return -1;
            }
        }else{
            if(current_input == 0 && current_stack == 36){
                stack_down(parser.stack);
                return 1;
            }
        }
    }
}