#pragma once

#include "callable.h"
#include "statement/function-statement.h"

class Function : public Callable {
  public:
    Function(const FunctionStatement *declaration);
    unsigned int arity() const;
    Value call(Environment& env, std::vector<Value>& arguments) const;

  private:
    const FunctionStatement* declaration;
};