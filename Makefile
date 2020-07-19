.PHONY: clean distclean

CC=gcc
CFLAGS=-Wall

default: minibasic

%.o : %.c
	$(CC) $(CFLAGS) -c $<

minibasic: parser.o lexer.o ast.o symbol.o error.o general.o
	$(CC) $(CFLAGS) -o minibasic $^ -lfl

general.o: general.c general.h error.h
error.o: error.c general.c error.h
symbol.o: error.c general.c error.h
symbtest.o: symbtest.c symbol.h error.h

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
