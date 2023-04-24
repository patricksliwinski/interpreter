#include "expression/assignment-expression.h"

AssignmentExpression::AssignmentExpression(Token name, std::unique_ptr<Expression> value)
  : name(name), value(std::move(value)) {}

std::string AssignmentExpression::printWithParenthesis() const {
  return "( assign " + name.getLexeme() + " " + value->printWithParenthesis() + ")";
}

Value AssignmentExpression::interpret(Environment& env) const {
  auto value = this->value->interpret(env);
  env.assign(name.getLexeme(), value);
  return value;
}