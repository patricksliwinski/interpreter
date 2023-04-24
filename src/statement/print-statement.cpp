#include <iostream>
#include "statement/print-statement.h"

PrintStatement::PrintStatement(std::unique_ptr<Expression> expression)
  : expression(std::move(expression)) {}

void PrintStatement::interpret(Environment& env) const {
  std::cout << stringify(expression->interpret(env)) << std::endl;
}