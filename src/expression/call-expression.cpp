#include "expression/call-expression.h"
#include "callable.h"

CallExpression::CallExpression(std::unique_ptr<Expression> callee, Token paren, std::vector<std::unique_ptr<Expression>> arguments)
  : callee(std::move(callee)), paren(paren), arguments(std::move(arguments)) {}

std::string CallExpression::printWithParenthesis() const {
  std::string argumentsString;
  for (const auto& argument : arguments) {
    argumentsString += " " + argument->printWithParenthesis();
  }
  return "( call " + callee->printWithParenthesis() + argumentsString + ")";
}

Value CallExpression::interpret(Environment& env) const {
  Value calleeValue = callee->interpret(env);
  if (!isCallable(calleeValue)) {
    throw RuntimeError(paren, "Can only call functions and classes.");
  }

  std::vector<Value> argumentsValues;
  for (const auto& argument : arguments) {
    argumentsValues.push_back(argument->interpret(env));
  }

  auto calleeCallable = asCallable(calleeValue).callable;
  if (argumentsValues.size() != calleeCallable->arity()) {
    throw RuntimeError(paren, "Expected " + std::to_string(calleeCallable->arity()) + " arguments but got " + std::to_string(argumentsValues.size()) + ".");
  }

  return calleeCallable->call(env, argumentsValues);
}