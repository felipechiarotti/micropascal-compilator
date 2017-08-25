#include <stdio.h>
#include "parser/parser.c"

extern void yyset_in(FILE*);
int main(int argc, char **argv){
	if(argc == 2){
		FILE *file;
		if(!(file = fopen(argv[1], "r"))){
			perror("Erro: ");
            return (-1);
		}else{
			struct Parser parser;
			int result = run_parser(parser, PROGR);
			if(result){
				printf("%s compilado com sucesso!",argv[1]);
			}else{
				printf("Não foi possível compilar o arquivo %s",argv[1]);
			}
		}
		fclose(file);
	}else{
		printf("[!]Utilize o compilador da seguinte forma: \"%s nome-do-arquivo\"\n",argv[0]);
	}
	return 0;
}