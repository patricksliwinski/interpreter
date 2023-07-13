#pragma once

#include "statement.h"

class FunctionStatement : public Statement {
public:
  FunctionStatement(Token name, std::vector<Token> params, std::vector<std::unique_ptr<Statement>> body);

  const Token& getName() const { return name; };
  void interpret(Environment& env) const override;

private:
  Token name;
  std::vector<Token> params;
  std::vector<std::unique_ptr<Statement>> body;
};