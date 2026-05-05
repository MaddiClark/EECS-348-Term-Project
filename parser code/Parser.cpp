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

}