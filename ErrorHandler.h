//
// Created by Jaycob Campos on 4/17/26.
// Updated by Tate Meyer on 5/5/26.
// Updated by Tate Meyer on 5/7/26.
// Changelog: added lightweight shared global error tracking for tokenizing/parsing/eval

#ifndef PARSER_ERRORHANDLER_H
#define PARSER_ERRORHANDLER_H
#include <string>
using namespace std;

enum ErrorCodes {
    INVALID_CHARACTER,
    UNSUPPORTED_OPERATOR,
    MISMATCHED_PARENTHESES,
    MISSING_OPERAND,
    DIVISION_BY_ZERO,
    MISSING_OPERATOR,
    UNMATCHED_PARENTHESES
};

class ErrorHandler {
public:
    ErrorHandler()= default;
    static void reset();
    static bool hadError();
    void handler(ErrorCodes error, string cause, int position, string expression);

private:
    static inline thread_local bool s_hadError = false;
    void highlightError(string expression, int position);
};


#endif //PARSER_ERRORHANDLER_H