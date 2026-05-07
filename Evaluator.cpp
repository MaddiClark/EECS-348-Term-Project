//
// Created by Jaycob Campos on 4/17/26.
// Updated by Nikki Sotoodi on 5/6/26.
// Debugged by Avery Richardson on 5/6/26
// ChangeLog: Added Line 33-36, Added a NULL check block to ensure a crash does not occur
//

#include "Evaluator.h"
#include "ErrorHandler.h"
#include <cmath>


double Evaluator::evaluate(Node *root) {

    ErrorHandler obj;

    if (root == nullptr) {

        obj.handler(MISSING_OPERAND, "", -1, expression);
        return 0;

    }

    if (root->token.type == NUMBER) {

        return root->token.number;

    }


    if (root->token.type == OPERATOR) {

        if (root->left == nullptr || root->right == nullptr) {
            obj.handler(MISSING_OPERAND, root->token.operatorValue, -1, expression);
            return 0;
        }

        double left = evaluate(root->left);

        double right = evaluate(root->right);

        return applyOperator(root->token.operatorValue, left, right);

    }


    obj.handler(MISSING_OPERAND, "", -1, expression);
    return 0;

}

double Evaluator::applyOperator(string operatorValue, double left, double right) {

    ErrorHandler obj;

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

            obj.handler(DIVISION_BY_ZERO, operatorValue, -1, expression);
            return 0;

        }

        return left / right;

    }

    else if (operatorValue == "%") {

        if (right == 0) {

            obj.handler(DIVISION_BY_ZERO, operatorValue, -1, expression);
            return 0;

        }

        return (int)left % (int)right;

    }

    else if (operatorValue == "**") {

        return pow(left, right);

    }


    obj.handler(UNSUPPORTED_OPERATOR, operatorValue, -1, expression);
    return 0;

}