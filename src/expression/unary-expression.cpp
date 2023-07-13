#include "expression/unary-expression.h"

UnaryExpression::UnaryExpression(Token operatorToken, std::unique_ptr<Expression> right)
  : operatorToken(operatorToken), right(std::move(right)) {}

std::string UnaryExpression::printWithParenthesis() const {
  return "(" + operatorToken.getLexeme() + " " + right->printWithParenthesis() + ")";
}

Value UnaryExpression::interpret(Environment& env) const {
  Value rightValue = right->interpret(env);
  switch (operatorToken.getType()) {
    case TokenType::MINUS:
      checkNumberOperator(operatorToken, rightValue);
      return -std::get<double>(rightValue);
    case TokenType::BANG:
      return !isTruthy(rightValue);
  }
  return NullValue {};
}