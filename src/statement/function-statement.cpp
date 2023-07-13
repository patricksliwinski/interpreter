#include "statement/function-statement.h"
#include "function.h"

FunctionStatement::FunctionStatement(Token name, std::vector<Token> params, std::vector<std::unique_ptr<Statement>> body)
  : name(name), params(params), body(std::move(body)) {}

void FunctionStatement::interpret(Environment& env) const {
  CallableValue callableValue{std::make_shared<Function>(this)};
  env.define(name.getLexeme(), callableValue);
}