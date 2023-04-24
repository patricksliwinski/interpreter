#pragma once

#include "statement.h"

class IfStatement : public Statement {
public:
  IfStatement(std::unique_ptr<Expression> condition, 
    std::unique_ptr<Statement> thenBranch, 
    std::unique_ptr<Statement> elseBranch);

  const Expression& getCondition() const { return *condition; };
  const Statement& getThenBranch() const { return *thenBranch; };
  const Statement& getElseBranch() const { return *elseBranch; };
  void interpret(Environment& env) const override;

private:
  std::unique_ptr<Expression> condition;
  std::unique_ptr<Statement> thenBranch;
  std::unique_ptr<Statement> elseBranch;
};