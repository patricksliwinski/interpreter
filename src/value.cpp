#include "value.h"
#include "callable.h"

bool isTruthy(const Value& value) {
  if (std::holds_alternative<NullValue>(value)) {
    return false;
  } else if (std::holds_alternative<bool>(value)) {
    return std::get<bool>(value);
  }
  return true;
}

bool isCallable(const Value& value) {
  return std::holds_alternative<CallableValue>(value);
  return true;
}

CallableValue asCallable(const Value& value) {
  return std::get<CallableValue>(value);
}