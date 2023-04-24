#include "expression/value-expression.h"

ValueExpression::ValueExpression(Value value)
  : value(value) {}

std::string ValueExpression::printWithParenthesis() const {
  return std::visit(PrintVisitor {}, value);
}

Value ValueExpression::interpret(Environment& env) const {
  return value;
}