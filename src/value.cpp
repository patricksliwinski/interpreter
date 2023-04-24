#include "value.h"

bool isTruthy(const Value& value) {
  if (std::holds_alternative<std::nullptr_t>(value)) {
    return false;
  } else if (std::holds_alternative<bool>(value)) {
    return std::get<bool>(value);
  }
  return true;
}