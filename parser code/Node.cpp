//
// Created by Jaycob Campos on 4/17/26.
//

#include "Node.h"

Node::Node(Token inputToken, Node* inputLeft, Node* inputRight) {
    token = inputToken;
    left = inputLeft;
    right = inputRight;
}