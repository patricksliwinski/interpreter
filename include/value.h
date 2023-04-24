#pragma once

#include <string>
#include <variant>

using Value = std::variant<std::string, double, bool, std::nullptr_t>;

struct PrintVisitor{
  std::string operator()(const std::string& str) const { return str; };
  std::string operator()(const double& dbl) const { return std::to_string(dbl); };
};

bool isTruthy(const Value& value);
std::string stringify(const Value& value);
