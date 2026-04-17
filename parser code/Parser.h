//
// Created by Jaycob Campos on 4/17/26.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H
#include "Token.h"
#include "Node.h"
#include <vector>

class Parser {
public:
    vector<Token> tokens;

    Node* createTree();


private:
    int lowestPrecedenceOperator(int start, int end);
    Node* buildSubTree(int start, int end);

};


#endif //PARSER_PARSER_H