#pragma once

#include "expression.h"
#include "../value.h"

class ValueExpression : public Expression {
public:
  ValueExpression(Value value);

  const Value& getValue() const { return value; };
  std::string printWithParenthesis() const override;
  Value interpret(Environment& env) const override;

private:
  Value value;
};