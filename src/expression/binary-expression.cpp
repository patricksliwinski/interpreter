#include "expression/binary-expression.h"

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> left, Token operatorToken, std::unique_ptr<Expression> right)
  : left(std::move(left)), operatorToken(operatorToken), right(std::move(right)) {}

std::string BinaryExpression::printWithParenthesis() const {
  return "(" + operatorToken.getLexeme() + " " + left->printWithParenthesis() + " " + right->printWithParenthesis() + ")";
}

Value BinaryExpression::interpret(Environment& env) const {
  Value leftValue = left->interpret(env);
  Value rightValue = right->interpret(env);
  switch (operatorToken.getType()) {
    case TokenType::GREATER:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) > std::get<double>(rightValue);
    case TokenType::GREATER_EQUAL:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) >= std::get<double>(rightValue);
    case TokenType::LESS:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) < std::get<double>(rightValue);
    case TokenType::LESS_EQUAL:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) <= std::get<double>(rightValue);
    case TokenType::BANG_EQUAL:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) != std::get<double>(rightValue);
    case TokenType::EQUAL_EQUAL:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) == std::get<double>(rightValue);
    case TokenType::MINUS:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) - std::get<double>(rightValue);
    case TokenType::SLASH:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) / std::get<double>(rightValue);
    case TokenType::STAR:
      checkNumberOperator(operatorToken, leftValue, rightValue);
      return std::get<double>(leftValue) * std::get<double>(rightValue);
    case TokenType::PLUS:
      if (std::holds_alternative<double>(leftValue) && std::holds_alternative<double>(rightValue)) {
        return std::get<double>(leftValue) + std::get<double>(rightValue);
      }
      if (std::holds_alternative<std::string>(leftValue) && std::holds_alternative<std::string>(rightValue)) {
        return std::get<std::string>(leftValue) + std::get<std::string>(rightValue);
      }
      throw RuntimeError("Operands must be numbers or strings");
  }
  return NullValue();
}