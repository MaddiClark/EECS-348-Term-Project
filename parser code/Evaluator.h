//
// Created by Jaycob Campos on 4/17/26.
//

#ifndef PARSER_EVALUATOR_H
#define PARSER_EVALUATOR_H
#include "Node.h"

class Evaluator {
public:
    double evaluate(Node *root);

private:
    double applyOperator(string operatorValue, double left, double right);
};


#endif //PARSER_EVALUATOR_H