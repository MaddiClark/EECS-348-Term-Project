//
// Created by Jaycob Campos on 4/17/26.
//

#ifndef PARSER_TOKEN_H
#define PARSER_TOKEN_H


#include <string>
using namespace std;

enum TokenType {
    NUMBER,
    OPERATOR,
    PARENTHESIS
};

class Token {
public:
    TokenType type;
    double number;
    string operatorValue;
    int precedence;

    Token();
    Token(TokenType inputType, double inputNumber, string inputOperator, int inputPrecedence);
};

#endif //PARSER_TOKEN_H

