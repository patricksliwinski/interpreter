#pragma once

#include <unordered_map>
#include <any>
#include <string>

#include "value.h"

class LoxInterpreter;

class Environment {
public:
  
  Environment() = default;
  Environment(Environment* enclosing);

  void define(const std::string& name, const Value& value) { values[name] = value; }

  Value get(const std::string& name);

  void assign(const std::string& name, const Value& value);

  Environment* getEnclosing() { return enclosing; }

  // Fix this to avoid raw pointers
  //LoxInterpreter* getInterpreter() { return interpreter; }
  //void setInterpreter(LoxInterpreter* interpreter) { this->interpreter = interpreter; }

private:
  std::unordered_map<std::string, Value> values;
  Environment* enclosing;
  //LoxInterpreter& interpreter;
};