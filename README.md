# PCL

Compiler developed mostly in [C](https://en.wikipedia.org/wiki/C_(programming_language)) for the [compilers](https://courses.softlab.ntua.gr/compilers/) course at National Technical University of Athens (year 2019).

## Authors

   * Danai Efstathiou ([danaiefst](https://github.com/danaiefst))
   * Dionysios Spiliopoulos ([Dspil](https://github.com/Dspil))

## The PCL programming language

PCL is an imperative programming language resembling the [Pascal](https://en.wikipedia.org/wiki/Pascal_(programming_language)) programming language. It's full documentation can be found in [pcl2019.pdf](https://github.com/Dspil/compilers/blob/master/pcl2019.pdf).

## Technologies

This tools used for the development of this compiler are:

   * [C](https://en.wikipedia.org/wiki/C_(programming_language)) and [C++](https://en.wikipedia.org/wiki/C%2B%2B) languages
   * [flex](https://github.com/westes/flex/)
   * [bison](https://www.gnu.org/software/bison/)
   * [llvm](https://llvm.org/)

## Dependencies

This project was built with the following tools:
   * g++ version 7.5.0
   * clang version 11.0.0
   * llvm version 11.0.0
   * python version 3.6.9
   * flex version 2.6.4
   * bison version 3.0.4

## Installation

Installation can be achieved by cloning this repository and running `make` on the main directory.

## Usage

After running `make` one can use the python script `pcl` to invoke the compiler as follows:

```bash
./pcl <options>
```

<options> can be just a filename with some extension, in which case an llvm IR file is created along with an assembly one, with the extensions 'imm' and 'asm' respectively.

For a full listing of the available options run:

```bash
./pcl -h
```

## Design

The compiler consists of 5 parts executed consequently:
  * <b Lexing/>, which is implemented in file lexer.l using flex.
  * Parsing, which is implemented in file parser.y using bison, while also creating an Abstract Syntax Tree (ast).
  * Type Checking, which is implemented in file ast.c in function type_check.
  * Function Parameters Fixing. This part was necessary due to the use of LLVM IR, which does not support nested scopes, nor allows direct access to the stack frames. In this part each function that uses a variable defined in an outer scope gets this variable passed as a parameter by reference. For this reason, the function make_params in file make_params.cpp is called to alter the ast. As this language supports mutual recursion, make_params is a fix point computation.
  * LLVM IR production, which is implemented in file code_gen.cpp. In this file, optimizations to the IR code are also included.
  
## Bonus parts

The following bonus parts are implemented:
  * Reals
  * Optimizations of IR code
  * Register allocation and final code optimizations
