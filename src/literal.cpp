#include "value.h"

std::string stringify(const Value& literal) {
  return std::visit(PrintVisitor {}, literal);
}