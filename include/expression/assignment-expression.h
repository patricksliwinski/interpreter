#pragma once

#include "expression.h"

class AssignmentExpression : public Expression {
public:
  AssignmentExpression(Token name, std::unique_ptr<Expression> value);
  std::string printWithParenthesis() const override;

  const Token& getName() const { return name; };
  const Expression& getValue() const { return *value; };
  Value interpret(Environment& env) const override;

private:
  Token name;
  std::unique_ptr<Expression> value;
};