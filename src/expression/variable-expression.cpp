#include "expression/variable-expression.h"

VariableExpression::VariableExpression(Token name)
  : name(name) {}

std::string VariableExpression::printWithParenthesis() const {
  return "(" + name.getLexeme() + ")";
}

Value VariableExpression::interpret(Environment& env) const {
  return env.get(name.getLexeme());
}