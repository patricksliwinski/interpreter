#pragma once

#include "environment.h"
#include "value.h"

class Callable {
  public:
    virtual ~Callable() = default;
    virtual unsigned int arity() const = 0;
    virtual Value call(Environment& env, std::vector<Value>& arguments) const = 0;
};