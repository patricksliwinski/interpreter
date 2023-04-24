#pragma once

#include "statement.h"

class WhileStatement : public Statement {
public:
  WhileStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body);

  const Expression& getCondition() const { return *condition; };
  const Statement& getBody() const { return *body; };
  void interpret(Environment& env) const override;

private:
  std::unique_ptr<Expression> condition;
  std::unique_ptr<Statement> body;
};