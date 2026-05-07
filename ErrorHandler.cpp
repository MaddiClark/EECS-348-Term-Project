//
// Created by Jaycob Campos on 4/17/26.
// Debugged and edited by Tate Meyer 5/7/26.
// Changelog: added lightweight global error tracking if tokenizing/parsing/eval
//            reports an error, the UI does not print the result. 
//            case: 2/(3-3) prints "Error: Division by zero" instead of "=0"
#include <iostream>
#include "ErrorHandler.h"

using namespace std;

void ErrorHandler::reset() {
    s_hadError = false;
}

bool ErrorHandler::hadError() {
    return s_hadError;
}

void ErrorHandler::handler(ErrorCodes error, string cause, int position, string expression) {
    s_hadError = true;
    cout << "Error: ";

    if (error == INVALID_CHARACTER) cout << "Invalid character";
    if (error == UNSUPPORTED_OPERATOR) cout << "Unsupported operator";
    if (error == MISMATCHED_PARENTHESES) cout << "Mismatched parentheses";
    if (error == MISSING_OPERAND) cout << "Missing operand";
    if (error == DIVISION_BY_ZERO) cout << "Division by zero";
    if (error == MISSING_OPERATOR) cout << "Missing operator";
    if (error == UNMATCHED_PARENTHESES) cout << "Unmatched parentheses";

    if (position == -1) {
        cout << endl;
    }else {
        cout << " '" << cause << "' at position " << position << endl;
        cout << expression << endl;
        highlightError(expression, position);
    }

}

void ErrorHandler::highlightError(string expression, int position) {
    for (int i = 0; i < position; i++) {
        cout << " ";
    }
    cout << "^" << endl;
}
