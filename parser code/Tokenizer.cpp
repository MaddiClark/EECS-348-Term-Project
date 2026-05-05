//
// Created by Jaycob Campos on 4/17/26.
// Updated by Tate Meyer on 5/5/26.
//
#include "Tokenizer.h"
#include "ErrorHandler.h"

#include <cctype>
#include <string>

vector<Token> Tokenizer::createTokens(string input) {
    inputString = std::move(input);
    position = 0;
    vector<Token> tokens;
    ErrorHandler errorHandler;

    const int length = static_cast<int>(inputString.size());
    while (position < length) {
        skipSpaces();
        if (position >= length) {
            break;
        }

        const unsigned char uc = static_cast<unsigned char>(inputString[position]);

        // Allows "0.5" and ".5"; "." alone is rejected (fraction needs at least one digit).
        if (std::isdigit(uc)) {
            tokens.push_back(readingNumbers());
        } else if (inputString[position] == '.') {
            if (position + 1 < length &&
                std::isdigit(static_cast<unsigned char>(inputString[position + 1]))) {
                tokens.push_back(readingNumbers());
            } else {
                errorHandler.handler(INVALID_CHARACTER, ".", position, inputString);
                return {};
            }
        } else if (inputString[position] == '(' || inputString[position] == ')') {
            const string paren(1, inputString[position]);
            position++;
            tokens.emplace_back(TokenType::PARENTHESIS, 0.0, paren, 0);
        } else if (inputString[position] == '+' || inputString[position] == '-' ||
                   inputString[position] == '*' || inputString[position] == '/') {
            tokens.push_back(readingOperators());
        } else {
            // Everything else is a lexical error for this grammar.
            errorHandler.handler(INVALID_CHARACTER, string(1, inputString[position]), position, inputString);
            return {};
        }
    }
    return tokens;
}

void Tokenizer::skipSpaces() {
    const int n = static_cast<int>(inputString.size());
    while (position < n &&
           std::isspace(static_cast<unsigned char>(inputString[position])) != 0) {
        position++;
    }
}

Token Tokenizer::readingNumbers() {
    const int n = static_cast<int>(inputString.size());
    const int start = position;

    if (position >= n) {
        return Token(TokenType::NUMBER, 0.0, "", 0);
    }

    if (inputString[position] == '.') {
        position++;
        bool sawFractionDigit = false;
        while (position < n &&
               std::isdigit(static_cast<unsigned char>(inputString[position])) != 0) {
            sawFractionDigit = true;
            position++;
        }
        if (!sawFractionDigit) {
            return Token(TokenType::NUMBER, 0.0, "", 0);
        }
    } else {
        while (position < n &&
               std::isdigit(static_cast<unsigned char>(inputString[position])) != 0) {
            position++;
        }
        if (position < n && inputString[position] == '.') {
            position++;
            while (position < n &&
                   std::isdigit(static_cast<unsigned char>(inputString[position])) != 0) {
                position++;
            }
        }
    }

    const string lexeme = inputString.substr(static_cast<string::size_type>(start),
                                            static_cast<string::size_type>(position - start));
    try {
        const double value = std::stod(lexeme);
        return Token(TokenType::NUMBER, value, "", 0);
    } catch (...) {
        // If stod fails, let createTokens report the error on next iteration when it sees the same char.
        return Token(TokenType::NUMBER, 0.0, "", 0);
    }
}

Token Tokenizer::readingOperators() {
    const int n = static_cast<int>(inputString.size());
    if (position >= n) {
        return Token(TokenType::OPERATOR, 0.0, "", 0);
    }

    const char c = inputString[position++];
    string op(1, c);
    int prec = 0;
    if (c == '+' || c == '-') {
        prec = 1;
    } else if (c == '*' || c == '/') {
        prec = 2;
    }
    return Token(TokenType::OPERATOR, 0.0, op, prec);
}

bool Tokenizer::isWhiteSpace() {
    if (position < 0 || position >= static_cast<int>(inputString.size())) {
        return false;
    }
    return std::isspace(static_cast<unsigned char>(inputString[position])) != 0;
}

bool Tokenizer::isValidCharacter() {
    if (position < 0 || position >= static_cast<int>(inputString.size())) {
        return false;
    }
    const unsigned char uc = static_cast<unsigned char>(inputString[position]);
    const char c = inputString[position];
    if (std::isspace(uc) != 0) {
        return true;
    }
    if (std::isdigit(uc) != 0) {
        return true;
    }
    if (c == '.') {
        return true;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return true;
    }
    if (c == '(' || c == ')') {
        return true;
    }
    return false;
}
