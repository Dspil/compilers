.PHONY: clean

CC=gcc
CFLAGS=-Wall

lexer.c: lexer.l
	flex -s -o lexer.c lexer.l

clean:
	$(RM) lexer.c *.o *~*
