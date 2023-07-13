#pragma once

#include <vector>
#include "statement.h"

class BlockStatement : public Statement {
public:
  BlockStatement(std::vector<std::unique_ptr<Statement>> statements);

  // TODO: best way to pass vector of unique_ptr?
  std::vector<std::unique_ptr<Statement>> getStatements() { return std::move(statements); };
  void interpret(Environment& env) const override;

private:
  std::vector<std::unique_ptr<Statement>> statements;
};