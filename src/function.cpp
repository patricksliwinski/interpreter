#include "function.h"

Function::Function(const FunctionStatement *declaration)
  : declaration(declaration) {}

unsigned int Function::arity() const {
  return 1;
}

Value Function::call(Environment& env, std::vector<Value>& arguments) const {
  return 1.0;
}