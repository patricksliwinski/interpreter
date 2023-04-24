#pragma once

#include <variant>
#include <string>
#include "token-type.h"
#include "value.h"

class Token {
public:
  Token(TokenType type, std::string lexeme, Value literal, int line);
  std::string toString();

  const std::string& getLexeme() const { return lexeme; };
  const Value& getValue() const { return literal; };
  int getLine() const { return line; };
  TokenType getType() const { return type; };

  private:
    TokenType type;
    std::string lexeme;
    Value literal;
    int line;
};
