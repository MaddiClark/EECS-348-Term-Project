//
// Created by Jaycob Campos on 4/17/26.
//

#ifndef PARSER_TOKENIZER_H
#define PARSER_TOKENIZER_H
#include <string>
#include "Token.h"
#include <vector>

using namespace std;

class Tokenizer {
public:
    vector<Token> createTokens(string input);

private:
    string inputString;
    int position = 0;

    Token readingNumbers();
    Token readingOperators();
    bool isWhiteSpace();
    bool isValidCharacter();
};

#endif //PARSER_TOKENIZER_H