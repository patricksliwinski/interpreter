target_include_directories(interpreter
    PUBLIC
    ../include)

target_sources(interpreter
  PUBLIC
  statement/print-statement.cpp
  statement/expression-statement.cpp
  statement/var-statement.cpp
  statement/block-statement.cpp
  statement/if-statement.cpp
  statement/while-statement.cpp
  statement/function-statement.cpp
)

target_include_directories(interpreter-test
    PUBLIC
    ../include)

target_sources(interpreter-test
  PUBLIC
  statement/print-statement.cpp
  statement/expression-statement.cpp
  statement/var-statement.cpp
  statement/block-statement.cpp
  statement/if-statement.cpp
  statement/while-statement.cpp
  statement/function-statement.cpp
)