%{
#include "libs/tokens.h"
int nline = 1;
%}
%%
[iI][fF]							return IF;
[tT][hH][eE][nN]					return THEN;
";"									return EOL;
[wW][hH][iI][lL][eE]				return WHILE;
[bB][eE][gG][iI][nN]        		return BEGN;
[eE][nN][dD]						return END;
[wW][rR][iI][tT][eE]				return WRITE;
[a-zA-Z][a-zA-Z0-9]*				return VAR;
[rR][eE][aA][dD]					return READ;
"="									return EQ;
[-]?[0-9]+([.][0-9]+)?				return NUM;
"+"									return PLUS;
"-"									return MINUS;
[ \t]								;
[\n]								nline++;
.									printf("caracter inesperado na linha %d\n",nline);
<<EOF>> 							return 36;
%%

int yywrap(void)
{
	return 1;
}