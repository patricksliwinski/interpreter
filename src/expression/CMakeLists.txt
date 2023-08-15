target_include_directories(interpreter
    PUBLIC
    ../include)

target_sources(interpreter
  PUBLIC
  expression/expression.cpp
  expression/binary-expression.cpp
  expression/unary-expression.cpp
  expression/grouping-expression.cpp
  expression/literal-expression.cpp
  expression/variable-expression.cpp
  expression/assignment-expression.cpp
  expression/logical-expression.cpp
  expression/call-expression.cpp
)