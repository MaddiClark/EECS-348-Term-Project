//
// Created by Jaycob Campos on 4/17/26.
//

#ifndef PARSER_ERRORHANDLER_H
#define PARSER_ERRORHANDLER_H
#include <string>
using namespace std;

enum ErrorCodes {
    INVALID_CHARACTER,
    UNSUPPORTED_OPERATOR,
    MISMATCHED_PARENTHESES,
    MISSING_OPERAND,
    DIVISION_BY_ZERO
};

class ErrorHandler {
public:
    void handler(ErrorCodes error, string cause, int position, string expression);

private:
    void highlightError(string expression, int position);
};


#endif //PARSER_ERRORHANDLER_H