#include "scanner.h"
#include "lox-interpreter.h"
#include "expression/expression.h"
#include "parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

bool LoxInterpreter::hadError = false;

void LoxInterpreter::runFile(std::string filename) {
  std::ifstream stream(filename);
  std::stringstream buffer;
  buffer << stream.rdbuf();
  run(buffer.str());
}

void LoxInterpreter::runPrompt() {
  for(;;) {
    printf("> ");
    std::string line;
    getline(std::cin, line);
    if (line.empty()) {
      break;
    }
    run(line);
    hadError = false;
  }
}

void LoxInterpreter::run(std::string source) {
  Scanner scanner {source};
  std::vector<Token> tokens {scanner.scanTokens()};
  Parser parser {tokens};

  
  std::vector<std::unique_ptr<Statement>> expressions {parser.parse()};

  // Stop if there was a syntax error.
  if (hadError) return;

  interpret(expressions);

  //std::cout << expression->printWithParenthesis() << std::endl;
}

void LoxInterpreter::interpret(std::vector<std::unique_ptr<Statement>>& statements) {
  try {
    for (const auto& statement : statements) {
      statement->interpret(environment);
    }
  } catch (RuntimeError error) {
    LoxInterpreter::runtimeError(error);
  }
}

void LoxInterpreter::error(int line, std::string message) {
  report(line, "", message);  
}

void LoxInterpreter::error(Token token, std::string message) {
  if (token.getType() == TokenType::EOF_TOKEN) {
    report(token.getLine(), " at end", message);
  } else {
    report(token.getLine(), " at '" + token.getLexeme() + "'", message);
  }
}

void LoxInterpreter::report(int line, std::string where, std::string message) {
  printf("[line %d] Error %s: %s", line, where.c_str(), message.c_str());
  hadError = true;
}

void LoxInterpreter::runtimeError(RuntimeError error){
  std::cout << error.getMessage() << "\n[line " << error.getLine() << "]" << std::endl;
  //hadRuntimeError = true;
}

Parser::ParseError Parser::error(Token token, const std::string& message) const {
  LoxInterpreter::error(token, message);
  return ParseError();
}