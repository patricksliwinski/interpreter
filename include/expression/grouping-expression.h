#pragma once

#include "expression.h"

class GroupingExpression : public Expression {
public:
  GroupingExpression(std::unique_ptr<Expression> expression);

  const Expression& getExpression() const { return *expression; };
  std::string printWithParenthesis() const override;
  Value interpret(Environment& env) const override;

private:
  std::unique_ptr<Expression> expression;
};