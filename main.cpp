#include <iostream>
#include "Headers.h"

void evaluate(string equation) {
    Parser parser;
    Evaluator evaluator;

    vector<Token> tokens = Tokenizer().createTokens(equation);
    if (tokens.empty()) {
        return;
    }

    parser.tokens = tokens;

    parser.expression = equation;
    evaluator.expression = equation;
    Node* parent = parser.createTree();

    if (parent != nullptr) {
        double result = evaluator.evaluate(parent);
        cout << equation + "    =   " << result << endl;
        delete parent;
    }
}

int main() {
    string openingScreen =
        "========================================\n"
        "  Arithmetic Expression Evaluator\n"
        "========================================\n"
        "Commands:\n"
        "  <expression>  Evaluate an arithmetic expression\n"
        "  help          Show supported operators\n"
        "  quit          Exit the program\n";

    string helpText = R"(Supported operators:
                        +    addition
                        -    subtraction (also unary)
                        *    multiplication
                        /    division
                        %    modulo
                        **   exponentiation
                        ( )  grouping)";

    string input;
    cout << openingScreen << endl;

    do {
        cout << "> ";
        getline(cin, input);

        if (input == "help") {
            cout << helpText << endl;
            continue;
        }

        if (input != "quit") {
            evaluate(input);
        }


    }while (input != "quit");

    cout << "ending program..."<< endl;

    return 0;
}
