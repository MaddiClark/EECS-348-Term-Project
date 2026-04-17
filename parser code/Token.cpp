//
// Created by Jaycob Campos on 4/17/26.
//
#include "Token.h"

Token::Token() {
    type = NUMBER;
    number = 0;
    operatorValue = "";
    precedence = 0;
}

Token::Token(TokenType inputType, double inputNumber, string inputOperator, int inputPrecedence) {
    type = inputType;
    number = inputNumber;
    operatorValue = inputOperator;
    precedence = inputPrecedence;
}

