.PHONY: clean distclean

export SHELL := /bin/bash

ifeq ($(shell uname -s),Darwin)
export PATH := /usr/local/opt/llvm/bin:$(PATH)
endif

CXX=g++
CXXFLAGS=-Wall `llvm-config --cxxflags`
LDFLAGS=`llvm-config --ldflags --system-libs --libs all`

CC=gcc
CFLAGS=-Wall

default: pclcomp builtins.so pcl

pcl: pcltemp
	 chmod +x pcl

pcltemp: pcl.py
	cp pcl.py pcl

builtins.so: builtins.ll
	clang builtins.ll -c -o builtins.so

pclcomp: ast.o make_params.o code_gen.o parser.o lexer.o symbol.o error.o general.o
	$(CXX) $(CXXFLAGS) -o pclcomp $^ $(LDFLAGS)

general.o: general.c general.h error.h
	$(CXX) $(CXXFLAGS) general.c -c -o general.o
error.o: error.c general.h error.h
	$(CXX) $(CXXFLAGS) error.c -c -o error.o
symbol.o: symbol.c general.h error.h ast_symbol.h
	$(CXX) $(CXXFLAGS) symbol.c -c -o symbol.o

parser.hpp parser.cpp: parser.y
	bison -dv parser.y -o parser.cpp

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

lexer.o: lexer.cpp parser.hpp
	$(CXX) $(CXXFLAGS) lexer.cpp -c -o lexer.o

parser.o: parser.cpp
	$(CXX) $(CXXFLAGS) parser.cpp -c -o parser.o

ast.o: ast.c
	$(CXX) $(CXXFLAGS) -c ast.c -o ast.o

make_params.o: make_params.cpp
	$(CXX) $(CXXFLAGS) -c make_params.cpp -o make_params.o

code_gen.o: code_gen.cpp code_gen.hpp ast_symbol.h
	$(CXX) $(CXXFLAGS) -c code_gen.cpp -o code_gen.o

clean:
	$(RM) *.o *~* parser.hpp *#* parser.output parser.cpp lexer.cpp parser.c lexer.c parser.h a.ll a.s a.out builtins.so

distclean: clean
	$(RM) pclcomp pcl
