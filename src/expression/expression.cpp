#include "expression/expression.h"

bool Expression::isTruthy(Value literal) const {
  if (std::holds_alternative<std::nullptr_t>(literal)) {
    return false;
  } else if (std::holds_alternative<bool>(literal)) {
    return std::get<bool>(literal);
  }
  return true;
}

void Expression::checkNumberOperator(Token op, Value rightValue) const {
  if (std::holds_alternative<double>(rightValue)) return;
  throw RuntimeError(op, "Operand must be a number");
}

void Expression::checkNumberOperator(Token op, Value leftValue, Value rightValue) const {
  if (std::holds_alternative<double>(leftValue) && std::holds_alternative<double>(rightValue)) return;
  throw RuntimeError(op, "Operand must be a number");
}
