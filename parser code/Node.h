//
// Created by Jaycob Campos on 4/17/26.
//

#ifndef PARSER_NODE_H
#define PARSER_NODE_H
#include "Token.h"


class Node {
    public:
    Token token;
    Node* left;
    Node* right;

    Node(Token inputToken, Node* inputLeft = nullptr, Node* inputRight = nullptr);
};


#endif //PARSER_NODE_H