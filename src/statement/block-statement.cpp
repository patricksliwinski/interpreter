#include "statement/block-statement.h"

BlockStatement::BlockStatement(std::vector<std::unique_ptr<Statement>> statements)
  : statements(std::move(statements)) {}

// Create a new environment and pass it to the statements when you call interpret on them.
void BlockStatement::interpret(Environment& env) const {
  Environment blockEnv(&env);
  for (const auto& statement : statements) {
    statement->interpret(blockEnv);
  }
}