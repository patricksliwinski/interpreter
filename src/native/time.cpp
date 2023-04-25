#include <chrono>
#include "native/time.h"

unsigned int Time::arity() const {
  return 0;
}

Value Time::call(Environment& env, std::vector<Value>& arguments) const {
  return (double) std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  ).count();
}