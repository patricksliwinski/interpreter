#pragma once

#include <memory>
#include <stdexcept>
#include <optional>

#include "../token.h"
#include "../environment.h"

class Expression {
public:
  virtual ~Expression() = default;
  virtual std::string printWithParenthesis() const = 0;
  virtual Value interpret(Environment& env) const = 0;
  bool isTruthy(Value value) const;
  void checkNumberOperator(Token op, Value rightValue) const;
  void checkNumberOperator(Token op, Value leftValue, Value rightValue) const;
};

class RuntimeError : public std::runtime_error {
public:
  RuntimeError() : std::runtime_error("") {};
  RuntimeError(std::string message) : std::runtime_error(message), message(message) {};
  RuntimeError(Token token, std::string message) : std::runtime_error(message), message(message), token(token) {};

  std::string getMessage() { return message; };

   int getLine() { 
    if (token.has_value()) {
      return token.value().getLine();
    }
    return 0;
  }

private:
  std::string message;
  std::optional<Token> token;
};