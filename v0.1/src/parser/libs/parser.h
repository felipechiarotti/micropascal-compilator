#ifndef PARSER_H_
#define PARSER_H_

#include "../../libs/tokens-productions.h"
#include "stack.h"

struct Parser;
int config_parser(struct Parser, int);
int run_parser(struct Parser, int);
int parse_token(struct Parser);
extern int yylex();

#endif