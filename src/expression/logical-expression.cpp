#include "expression/logical-expression.h"

LogicalExpression::LogicalExpression(std::unique_ptr<Expression> left, Token operatorToken, std::unique_ptr<Expression> right)
  : left(std::move(left)), operatorToken(operatorToken), right(std::move(right)) {}

std::string LogicalExpression::printWithParenthesis() const {
  return "(" + operatorToken.getLexeme() + " " + left->printWithParenthesis() + " " + right->printWithParenthesis() + ")";
}

Value LogicalExpression::interpret(Environment& env) const {
  Value leftValue = left->interpret(env);
  
  if (operatorToken.getType() == TokenType::OR) {
    if (isTruthy(leftValue)) return leftValue;
  } else {
    if (!isTruthy(leftValue)) return leftValue;
  }

  return right->interpret(env);
}