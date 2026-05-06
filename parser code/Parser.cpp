//
// Created by Jaycob Campos on 4/17/26.
// Last edited by: Maddi Clark 5/5/26.
// Is it optimized? God no lol

#include "Parser.h"
#include <vector>

Node* Parser::createTree() {
    if (tokens.empty()) return nullptr;

    int balance = 0;

    //checks for parenthesis errors
    for (int i = 0; i < tokens.size(); i++) {
        Token& t = tokens [i];
        if (t.type == PARENTHESIS) {
            if (t.value == '(') balance++;
            else if (t.value == ')') balance--;

            if (balance < 0) { //checking for any extra parenthesis
                ErrorHandler.handler(MISMATCHED_PARENTHESES, "extra )", i, expression);
                return nullptr;
            }
        }
    }

    if (balance != 0) { //checking for any missing parenthesis
        ErrorHandler.handler(UNMATCHED_PARENTHESES, "(", -1, expression);
        return nullptr;
    }
    //end of checking parenthesis errors

    return buildSubTree(0, tokens.size() - 1);
}

int Parser::lowestPrecedenceOperator(int start, int end) {
    int minPrecedence = 1; 
    int index = -1;
    int parenDepth = 0;

    for (int i = start; i <= end; i++) {
        Token& t = tokens[i]; //creates a copy of the token for use

        if (t.type == PARENTHESIS){
            if (t.value == '(') parenDepth++;
            else if (t.value == ')') parenDepth--;
        }

        else if (t.type == OPERATOR && parenDepth == 0) {
            bool isExponent = (t.value == "**");

            if (t.precedence <= minPrecedence) {
                minPrecedence = t.precedence;
                index = i;
            }

            else if (t.precedence == minPrecedence) {
                if (!isExponent) {
                    index = i;
                }
            }
        }
    }
    return index;
}

Node* Parser::buildSubTree(int start, int end) {
    if (start > end) { //preventing overflow
        ErrorHandler.handler(MISSING_OPERAND, "", start, expression);
        return nullptr; 
    }

    //single number case
    if (start == end && tokens[start].type == NUMBER){
        if (tokens[start].type != NUMBER){
            ErrorHandler.handler(MISSING_OPERAND, "", start, expression);
            return nullptr;
        }
        return new Node(tokens[start]);
    }

    //parentheses case, safely strips parenthesis and creates a new subtree with the contents
    if (tokens[start].type == PARENTHESIS && tokens[start].value == '(') {
        int depth = 0;
        bool wraps = true;

        for (int i = start; i <= end; i++) {
            if (tokens[i].value == '(') depth++;
            else if (tokens[i].value == ')') depth--;

            if (depth == 0 && i < end) {
                wraps = false;
                break;
            }
        }
        if (wraps) {
            return buildSubTree(start + 1, end - 1);
        }
    }

    if (tokens[start].type == OPERATOR && tokens[start].value == "-") {
        if (start == 0 || tokens[start-1].type == OPERATOR || (tokens[start-1].type == PARENTHESIS && tokens[start-1].value == '(')) {
            Node* zeroNode = new Node(Token(NUMBER, 0)); //treats condition as 0-expression

            Node* right = buildSubTree(start+1, end);
            if (!right) return nullptr;

            Node* node = new Node(tokens[start]);
            node -> left = zeroNode;
            node -> right = right;
            return node;
        }
    }

    if (tokens[start].type == OPERATOR && tokens[start].value == '+') {
        if (start == 0 || tokens[start-1].type == OPERATOR || (tokens[start-1].type == PARENTHESIS && tokens[start-1].value == '(')) {
            return buildSubTree(start + 1, end);
        }
    }

    int operatorIndex = lowestPrecedenceOperator(start, end);

    if (operatorIndex == -1) { //checks for a missing operator
        ErrorHandler.handler(MISSING_OPERATOR, "", start, expression);
        return nullptr;
    }

    Node* node = new Node(tokens[operatorIndex]);

    Node* left = buildSubTree(start, operatorIndex - 1);
    if (!left) return nullptr; //checks if in correct subtree

    Node* right = buildSubTree(operatorIndex + 1, end);
    if (!right) return nullptr; //checks if in correct subtree

    return node;
}