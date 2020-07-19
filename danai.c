p = newFunction("abs")
openScope();
newParameter("n", typeInteger, PASS_BY_VALUE, p);
endFunctionHeader(p, typeInteger);
closeScope();

p = newFunction("fabs")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("sqrt")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("sin")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("cos")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("tan")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("arctan")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("exp")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("ln")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("pi")
openScope();
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("trunc")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeInteger);
closeScope();

p = newFunction("round")
openScope();
newParameter("r", typeReal, PASS_BY_VALUE, p);
endFunctionHeader(p, typeInteger);
closeScope();

p = newFunction("ord")
openScope();
newParameter("c", typeChar, PASS_BY_VALUE, p);
endFunctionHeader(p, typeInteger);
closeScope();

p = newFunction("chr")
openScope();
newParameter("n", typeInteger, PASS_BY_VALUE, p);
endFunctionHeader(p, typeChar);
closeScope();

p = newFunction("readInteger")
openScope();
endFunctionHeader(p, typeInteger);
closeScope();

p = newFunction("readBoolean")
openScope();
endFunctionHeader(p, typeBoolean);
closeScope();

p = newFunction("readChar")
openScope();
endFunctionHeader(p, typeChar);
closeScope();

p = newFunction("readReal")
openScope();
endFunctionHeader(p, typeReal);
closeScope();

p = newFunction("readString")
openScope();
newParameter("size", typeInteger, PASS_BY_VALUE, p);
newParameter("s", typeIArray(typeChar), PASS_BY_REFERENCE, p);
closeScope();
