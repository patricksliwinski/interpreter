#include "statement/expression-statement.h"

ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression> expression)
  : expression(std::move(expression)) {}

void ExpressionStatement::interpret(Environment& env) const {
  expression->interpret(env);
}