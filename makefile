compilator: src/main.c src/lexer/lex.yy.c
	cc -o compilator src/main.c src/lexer/lex.yy.c 

lexer: 
	flex -i -o src/lexer/lex.yy.c src/lexer/lexer.l	

clean:
	rm -f compilator
	rm -f src/lexer/lex.yy.c
