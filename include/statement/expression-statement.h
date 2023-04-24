#pragma once

#include "statement.h"

class ExpressionStatement : public Statement {
public:
  ExpressionStatement(std::unique_ptr<Expression> expression);

  const Expression& getExpression() const { return *expression; };
  void interpret(Environment& env) const override;

private:
  std::unique_ptr<Expression> expression;
};