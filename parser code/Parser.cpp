//
// Created by Jaycob Campos on 4/17/26.
// Last edited by: Maddi Clark 5/5/26.
// Is it optimized? God no lol

#include "Parser.h"
#include <vector>

Node* Parser::createTree() {
    if (tokens.empty()) return nullptr;
    return buildSubTree(0, tokens.size() - 1);
}

int Parser::lowestPrecedenceOperator(int start, int end) {
    int minPrecedence = 1; 
    int index = -1;
    int parenDepth = 0;

    for (int i = start; i <= end; i++) {
        Token t = tokens[i]; //creates a copy of the token for use

        if (t.type == PARENTHESIS){
            if (t.value == "(") parenDepth++;
            else if (t.value == ")") parenDepth--;
        }

        else if (t.type == OPERATOR && parenDepth == 0) {
            if (t.precedence <= minPrecedence) {
                minPrecedence = t.precedence;
                index = i;
            }
        }
    }
    
}

Node* Parser::buildSubTree(int start, int end) {
    if (start > end) return nullptr; //preventing overflow

    //single number case
    if (start == end && tokens[start].type == NUMBER){
        return new Node(tokens[start]);
    }

    //parentheses case
    if (tokens[start].type == PARENTHESIS && tokens[start].value == "(" && tokens[end] == ')') {
        return buildSubTree(start + 1, end - 1);
    }

    int operatorIndex = lowestPrecedenceOperator(start, end);

    if (operatorIndex == -1) return nullptr; //error for invalid expression

    Node* node = new Node(tokens[operatorIndex]);
    node -> left = buildSubTree(start, operatorIndex - 1);
    node -> right = buildSubTree(operatorIndex + 1, end);

    return node;
}