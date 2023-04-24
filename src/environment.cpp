#include "environment.h"
#include "expression/expression.h"


Environment::Environment(Environment* enclosing) : enclosing(enclosing) {

}

Value Environment::get(const std::string& name) {
  if (values.find(name) != values.end()) {
    return values[name];
  }
  if (enclosing != nullptr) {
    return enclosing->get(name);
  }
  throw RuntimeError("Undefined variable '" + name + "'.");
}

void Environment::assign(const std::string& name, const Value& value) {
  if (values.find(name) == values.end()) {
    if (enclosing != nullptr) {
      enclosing->assign(name, value);
      return;
    }
    throw RuntimeError("Undefined variable '" + name + "'.");
  }
  values[name] = value;
}