target_include_directories(interpreter
    PUBLIC
    ../include)

target_sources(interpreter
  PUBLIC
  native/time.cpp
)