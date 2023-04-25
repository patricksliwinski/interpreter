#pragma once

#include <vector>

#include "expression.h"

class CallExpression : public Expression {
public:
  CallExpression(std::unique_ptr<Expression> callee, Token paren, std::vector<std::unique_ptr<Expression>> arguments);
  std::string printWithParenthesis() const override;

  const Expression& getLeft() const { return *callee; };
  const Token& getOperatorToken() const { return paren; };
  Value interpret(Environment& env) const override;

private:
  std::unique_ptr<Expression> callee;
  Token paren;
  std::vector<std::unique_ptr<Expression>> arguments;
};