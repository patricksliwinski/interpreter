#include "statement/while-statement.h"

WhileStatement::WhileStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Statement> body)
  : condition(std::move(condition)), body(std::move(body)) {}

void WhileStatement::interpret(Environment& env) const {
  while (isTruthy(condition->interpret(env))) {
    body->interpret(env);
  }
}