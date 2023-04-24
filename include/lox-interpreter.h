#pragma once

#include <string>
#include <vector>
#include <memory>
#include "token.h"
#include "expression/expression.h"
#include "statement/statement.h"
#include "environment.h"

class LoxInterpreter {
public:

  /**
   * @brief Runs a lox file through the interpreter
   * 
   * @param filename the file to run
   */
	void runFile(std::string filename);

  /**
   * @brief Starts the lox interpreter with a user prompt
   * 
   */
	void runPrompt();

  /**
   * @brief Runs a string of lox code through the interpreter
   * 
   * @param source 
   */
	void run(std::string source);

  /**
   * @brief Reports an error to the user
   * 
   * @param line The line number where the error occurred
   * @param message Custom error message
   */

  void interpret(std::vector<std::unique_ptr<Statement>>& statements);

	static void error(int line, std::string message);
  static void error(Token token, std::string message);
  static void runtimeError(RuntimeError error);

private:
	static bool hadError;
  static bool hadRuntimeError;
  Environment environment;
	static void report(int line, std::string where, std::string message);
};
