.PHONY: clean distclean default

export SHELL := /bin/bash

ifeq ($(shell uname -s),Darwin)
export PATH := /usr/local/opt/llvm/bin:$(PATH)
endif

CXX=clang++
CXXFLAGS=-Wall -g -O3


default: pcl

parser.hpp parser.cpp: parser.y
	bison -dv -o parser.cpp parser.y

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

parser.o: parser.cpp parser.hpp ast.hpp

lexer.o: lexer.cpp parser.hpp

ast.o: ast.cpp ast.hpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

pcl: lexer.o parser.o ast.o
	$(CXX) $(CXXFLAGS) -o pcl $^ -lfl

clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output a.* *.o *~

distclean: clean
	$(RM) pcl
