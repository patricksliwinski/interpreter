#pragma once

#include "expression.h"

class BinaryExpression : public Expression {
public:
  BinaryExpression(std::unique_ptr<Expression> left, Token operatorToken, std::unique_ptr<Expression> right);
  std::string printWithParenthesis() const override;

  const Expression& getLeft() const { return *left; };
  const Token& getOperatorToken() const { return operatorToken; };
  const Expression& getRight() const { return *right; };
  Value interpret(Environment& env) const override;

private:
  std::unique_ptr<Expression> left;
  Token operatorToken;
  std::unique_ptr<Expression> right;
};
