/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    t_and = 258,
    t_array = 259,
    t_begin = 260,
    t_boolean = 261,
    t_char = 262,
    t_dispose = 263,
    t_div = 264,
    t_do = 265,
    t_else = 266,
    t_end = 267,
    t_false = 268,
    t_forward = 269,
    t_function = 270,
    t_goto = 271,
    t_if = 272,
    t_integer = 273,
    t_label = 274,
    t_mod = 275,
    t_new = 276,
    t_nil = 277,
    t_not = 278,
    t_of = 279,
    t_or = 280,
    t_procedure = 281,
    t_program = 282,
    t_real = 283,
    t_result = 284,
    t_return = 285,
    t_then = 286,
    t_true = 287,
    t_var = 288,
    t_while = 289,
    t_id = 290,
    t_real_const = 291,
    t_int_const = 292,
    t_char_const = 293,
    t_string_const = 294,
    t_neq = 295,
    t_geq = 296,
    t_leq = 297,
    t_assign = 298,
    unary = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 11 "parser.y" /* yacc.c:1909  */

  ast * a;
  char c;
  int n;
  char* s;
  long double r;
  kind k;
  

#line 109 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
