#pragma once

#include <memory>

#include "../expression/expression.h"
#include "../environment.h"

class Statement {
public:
  virtual ~Statement() = default;
  virtual void interpret(Environment& env) const = 0;
};