//
// Created by Jaycob Campos on 4/17/26.
// Last edited by: Maddi Clark 5/5/26

#include "Parser.h"
#include <vector>

Node* Parser::createTree() {
    std::vector<Token> operatorStack[];
    std::vector<Token> operandStack[];

    for (int i = 0; i <= tokens.size; i++){ //sorts tokens into a list of operators and operands
        if tokens[i].TokenType == NUMBER {
            operandStack.push_back(tokens[i]);
        }
        else {
            operatorStack.push_back(tokens[i]);
        }
    }

    
}

int Parser::lowestPrecedenceOperator(int start, int end) {

}

Node* Parser::buildSubTree(int start, int end) {

}