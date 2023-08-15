#include <iostream>
#include "lox-interpreter.h"
#include "expression/binary-expression.h"
#include "expression/unary-expression.h"
#include "expression/grouping-expression.h"
#include "expression/value-expression.h"

int main(int argc, char *argv[]) {
  LoxInterpreter interpreter;
  interpreter.runFile("/home/patrick/interpreter/test.lox");
  // if (argc > 2) {
  //   std::printf("Usage: jlox [script]\n");
  //   return 64;
  // } else if (argc == 2) {
  //   interpreter.runFile(argv[1]);
  // } else {
  //   interpreter.runPrompt();
  // }
}
