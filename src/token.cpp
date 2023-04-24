#include "token.h"

Token::Token(TokenType type, std::string lexeme, Value literal, int line)
  : type(type), lexeme(lexeme), literal(literal), line(line) {}

std::string Token::toString() {
  return std::string("Token(") + std::to_string(type) + ", " + lexeme + ", " +
    std::to_string(line) + ")";
}