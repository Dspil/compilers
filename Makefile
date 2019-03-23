.PHONY: clean distclean

CC=gcc
CFLAGS=-Wall

parser: parser.c lexer.c
	$(CC) -o parser parser.c lexer.c

parser.c: parser.y
	bison -dv parser.y -o parser.c

lexer.c: lexer.l
	flex -s -o lexer.c lexer.l

clean:
	$(RM) *.c *.o *~* parser.h *#* parser.output

distclean: clean
	$(RM) parser
