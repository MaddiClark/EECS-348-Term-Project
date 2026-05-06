//

// Created by Jaycob Campos on 4/17/26.

// Updated by Nikki Sotoodi on 5/6/26.

//

 

#include "Evaluator.h"

#include <stdexcept>

 

double Evaluator::evaluate(Node *root) {

    if (root == nullptr) {

        throw runtime_error("Invalid expression");

    }

 

    if (root->token.type == NUMBER) {

        return root->token.number;

    }

 

    if (root->token.type == OPERATOR) {

        double left = evaluate(root->left);

        double right = evaluate(root->right);

 

        return applyOperator(root->token.operatorValue, left, right);

    }

 

    throw runtime_error("Invalid expression");

}

 

double Evaluator::applyOperator(string operatorValue, double left, double right) {

    if (operatorValue == "+") {

        return left + right;

    }

    else if (operatorValue == "-") {

        return left - right;

    }

    else if (operatorValue == "*") {

        return left * right;

    }

    else if (operatorValue == "/") {

        if (right == 0) {

            throw runtime_error("Division by zero");

        }

        return left / right;

    }

 

    throw runtime_error("Unknown operator");

}
