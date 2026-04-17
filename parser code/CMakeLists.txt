cmake_minimum_required(VERSION 4.1)
project(parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(parser "main.cpp"
        "Token.cpp"
        "Token.h"
        "Node.cpp"
        "Node.h"
        "Tokenizer.cpp"
        "Tokenizer.h"
        "Parser.cpp"
        "Parser.h"
        "Evaluator.cpp"
        "Evaluator.h"
        "ErrorHandler.cpp"
        "ErrorHandler.h"
        "Headers.h"
)
