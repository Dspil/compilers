.PHONY: clean distclean

CC=gcc
CFLAGS=-Wall

default: minibasic

minibasic: parser.o lexer.o ast.o
	$(CC) $(CFLAGS) -o minibasic $^ -lfl

parser.h parser.c: parser.y
	bison -dv parser.y -o parser.c

lexer.c: lexer.l
	flex -s -o lexer.c lexer.l

lexer.o: lexer.c parser.h

parser.o: parser.c

ast.o: ast.c

lexer.o: lexer.c parser.h

clean:
	$(RM) *.o *~* parser.h *#* parser.output parser.c lexer.c

distclean: clean
	$(RM) minibasic
