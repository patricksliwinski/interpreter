#pragma once

#include "expression.h"

class VariableExpression : public Expression {
public:
  VariableExpression(Token name);

  const Token& getName() const { return name; };
  std::string printWithParenthesis() const override;
  Value interpret(Environment& env) const override;

private:
  Token name;
};