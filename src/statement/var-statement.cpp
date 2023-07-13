#include <iostream>
#include "statement/var-statement.h"

VarStatement::VarStatement(Token name, std::unique_ptr<Expression> initializer)
  : name(name), initializer(std::move(initializer)) {}

void VarStatement::interpret(Environment& env) const {
  if (initializer != nullptr) {
    auto value = initializer->interpret(env);
    env.define(name.getLexeme(), value);
  } else {
    env.define(name.getLexeme(), NullValue{});
  }
}