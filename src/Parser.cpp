//
// Created by Jaycob Campos on 4/17/26.
// Last edited by: Maddi Clark 5/5/26.
// Is it optimized? God no lol

#include "Parser.h"
#include "ErrorHandler.h"
#include <climits>
#include <vector>

Node* Parser::createTree() {
    ErrorHandler errorHandler;
    if (tokens.empty()) return nullptr;

    int balance = 0;

    //checks for parenthesis errors
    for (int i = 0; i < tokens.size(); i++) {
        Token& t = tokens [i];
        if (t.type == PARENTHESIS) {
            if (t.operatorValue == "(") balance++;
            else if (t.operatorValue == ")") balance--;

            if (balance < 0) { //checking for any extra parenthesis
                errorHandler.handler(MISMATCHED_PARENTHESES, "extra )", i, expression);
                return nullptr;
            }
        }
    }

    if (balance != 0) { //checking for any missing parenthesis
        errorHandler.handler(UNMATCHED_PARENTHESES, "(", -1, expression);
        return nullptr;
    }
    //end of checking parenthesis errors

    return buildSubTree(0, tokens.size() - 1);
}

int Parser::lowestPrecedenceOperator(int start, int end) {
    int minPrecedence = INT_MAX;
    int index = -1;
    int parenDepth = 0;

    for (int i = start; i <= end; i++) {
        Token& t = tokens[i];

        if (t.type == PARENTHESIS){
            if (t.operatorValue == "(") parenDepth++;
            else if (t.operatorValue == ")") parenDepth--;
        }

        else if (t.type == OPERATOR && parenDepth == 0) {
            bool isExponent = (t.operatorValue == "**");

            if (t.precedence < minPrecedence) {
                minPrecedence = t.precedence;
                index = i;
            } else if (t.precedence == minPrecedence && !isExponent) {
                // pick rightmost for left-to-right associativity; skip ** (right-associative)
                index = i;
            }
        }
    }

    return index;
}

Node* Parser::buildSubTree(int start, int end) {
    if (start > end) { //preventing overflow
        errorHandler.handler(MISSING_OPERAND, "", start, expression);
        return nullptr;
    }

    //single number case
    if (start == end && tokens[start].type == NUMBER){
        if (tokens[start].type != NUMBER){
            errorHandler.handler(MISSING_OPERAND, "", start, expression);
            return nullptr;
        }
        return new Node(tokens[start]);
    }

    //parentheses case, safely strips parenthesis and creates a new subtree with the contents
    if (tokens[start].type == PARENTHESIS && tokens[start].operatorValue == "(") {
        int depth = 0;
        bool wraps = true;

        for (int i = start; i <= end; i++) {
            if (tokens[i].operatorValue == "(") depth++;
            else if (tokens[i].operatorValue == ")") depth--;

            if (depth == 0 && i < end) {
                wraps = false;
                break;
            }
        }
        if (wraps) {
            return buildSubTree(start + 1, end - 1);
        }
    }

    int operatorIndex = lowestPrecedenceOperator(start, end);

    if (operatorIndex == -1) { //checks for a missing operator
        errorHandler.handler(MISSING_OPERATOR, "", start, expression);
        return nullptr;
    }

    // unary minus: only when the split point IS the '-' at the start of the range
    if (operatorIndex == start && tokens[start].operatorValue == "-") {
        if (start == 0 || tokens[start-1].type == OPERATOR || (tokens[start-1].type == PARENTHESIS && tokens[start-1].operatorValue == "(")) {
            Node* zeroNode = new Node(Token()); //treats condition as 0-expression

            Node* right = buildSubTree(start+1, end);
            if (!right) { delete zeroNode; return nullptr; }

            Node* node = new Node(tokens[start]);
            node->left = zeroNode;
            node->right = right;
            return node;
        }
    }

    // unary plus: same gating as unary minus, but no zero node needed since +x = x
    if (operatorIndex == start && tokens[start].operatorValue == "+") {
        if (start == 0 || tokens[start-1].type == OPERATOR || (tokens[start-1].type == PARENTHESIS && tokens[start-1].operatorValue == "(")) {
            return buildSubTree(start+1, end);
        }
    }

    Node* node = new Node(tokens[operatorIndex]);

    Node* left = buildSubTree(start, operatorIndex - 1);
    if (!left) { delete node; return nullptr; }

    Node* right = buildSubTree(operatorIndex + 1, end);
    if (!right) { delete node; return nullptr; }

    node->left = left;
    node->right = right;
    return node;
}