set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Compiler.cpp Compiler.h Parser.cpp Parser.h)
add_executable(DeltaLang ${SOURCE_FILES})