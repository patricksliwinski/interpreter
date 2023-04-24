#pragma once

#include "statement.h"

class VarStatement : public Statement {
public:
  VarStatement(Token name, std::unique_ptr<Expression> initializer);

  const Token& getName() const { return name; };
  const Expression& getInitializer() const { return *initializer; };
  void interpret(Environment& env) const override;

private:
  Token name;
  std::unique_ptr<Expression> initializer;
};