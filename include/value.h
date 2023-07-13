#pragma once

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <any>

class Callable;

struct CallableValue {
  std::shared_ptr<Callable> callable;
};

struct NullValue {

};

using Value = std::variant<std::string, double, bool, NullValue, CallableValue>;

struct PrintVisitor{
  std::string operator()(const std::string& str) const { return str; };
  std::string operator()(const double& dbl) const { return std::to_string(dbl); };
  std::string operator()(const bool& boolean) const { return boolean ? "true" : "false"; };
  std::string operator()(const NullValue& null) const { return "nil"; };
  std::string operator()(const CallableValue& callable) const { return ""; };
};

bool isTruthy(const Value& value);
bool isCallable(const Value& value);
CallableValue asCallable(const Value& value);
std::string stringify(const Value& value);
