//
// Created by Jaycob Campos on 4/17/26.
//
#include <iostream>
#include "ErrorHandler.h"

using namespace std;

void ErrorHandler::handler(ErrorCodes error, string cause, int position, string expression) {
    cout << "Error: ";

    if (error == INVALID_CHARACTER) cout << "Invalid character";
    if (error == UNSUPPORTED_OPERATOR) cout << "Unsupported operator";
    if (error == MISMATCHED_PARENTHESES) cout << "Mismatched parentheses";
    if (error == MISSING_OPERAND) cout << "Missing operand";
    if (error == DIVISION_BY_ZERO) cout << "Division by zero";
    if (error == MISSING_OPERATOR) cout << "Missing operator";
    if (error == UNMATCHED_PARENTHESES) cout << "Unmatched parentheses";

    if (position == -1) {
        cout << expression << endl;
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
