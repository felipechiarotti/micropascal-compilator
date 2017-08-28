#include <stdio.h>
#include "parser/parser.c"

int main(int argc, char **argv){
		int result = run_parser(PROGR);
		if(result){
			printf("Compilado com sucesso!\n");
		}else{
			printf("Não foi possível compilar o arquivo\n");
		}
	return 0;
}