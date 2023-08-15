target_include_directories(interpreter
    PUBLIC
    ../include)

target_sources(interpreter
  PUBLIC
  native/time.cpp
)

target_include_directories(interpreter-test
    PUBLIC
    ../include)

target_sources(interpreter-test
  PUBLIC
  native/time.cpp
)