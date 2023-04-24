#include "statement/if-statement.h"
#include "value.h"

IfStatement::IfStatement(std::unique_ptr<Expression> condition, 
  std::unique_ptr<Statement> thenBranch, 
  std::unique_ptr<Statement> elseBranch)
  : condition(std::move(condition)), 
  thenBranch(std::move(thenBranch)), 
  elseBranch(std::move(elseBranch)) {}

void IfStatement::interpret(Environment& env) const {
  if (isTruthy(condition->interpret(env))) {
    thenBranch->interpret(env);
  } else {
    elseBranch->interpret(env);
  }
}