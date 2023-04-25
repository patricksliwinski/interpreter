#include "callable.h"

class Time : public Callable {
  public:
    unsigned int arity() const;
    Value call(Environment& env, std::vector<Value>& arguments) const;
};