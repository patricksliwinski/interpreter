add_executable(interpreter)
add_executable(interpreter-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(interpreter
    PUBLIC
    ../include)

target_include_directories(interpreter-test
    PUBLIC
    ../include)

add_subdirectory(expression)
add_subdirectory(statement)
add_subdirectory(native)

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
        function.cpp
)

target_sources(interpreter-test
    PUBLIC
        test.cpp
        scanner.cpp
        token.cpp
        lox-interpreter.cpp
        parser.cpp
        literal.cpp
        value.cpp
        environment.cpp
        function.cpp
)