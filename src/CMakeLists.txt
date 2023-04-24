add_executable(interpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(interpreter
    PUBLIC
    ../include)

add_subdirectory(expression)
add_subdirectory(statement)

target_sources(interpreter
    PUBLIC
        main.cpp
        scanner.cpp
        token.cpp
        lox-interpreter.cpp
        parser.cpp
        literal.cpp
        value.cpp
        environment.cpp
)