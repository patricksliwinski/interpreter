#pragma once

#include "expression.h"

class UnaryExpression : public Expression {
public:
  UnaryExpression(Token operatorToken, std::unique_ptr<Expression> right);

  const Token& getOperatorToken() const { return operatorToken; };
  const Expression& getRight() const { return *right; };
  std::string printWithParenthesis() const override;
  Value interpret(Environment& env) const override;

private:
  Token operatorToken;
  std::unique_ptr<Expression> right;
};