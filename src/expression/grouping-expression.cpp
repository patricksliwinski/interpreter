#include "expression/grouping-expression.h"

GroupingExpression::GroupingExpression(std::unique_ptr<Expression> expression)
  : expression(std::move(expression)) {}

std::string GroupingExpression::printWithParenthesis() const {
  return "( group " + expression->printWithParenthesis() + ")";
}

Value GroupingExpression::interpret(Environment& env) const {
  return expression->interpret(env);
}
