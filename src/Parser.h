#pragma once

#include <fstream>
#include <vector>
#include <iostream>
#include <map>

struct ParserContext {
    uint64_t line = 0, column = 0;
    std::string *s = new std::string;

    void throwException(const char *text) {
        throw "[" + std::to_string(line) + ", " + std::to_string(column) + "] " + text;
    };
};

class Type {};

class Node {

};

class FunctionDeclaration : Node {

};

class FunctionCall : Node {

};

class Operator {};

class Keyword {};

class Variable {};

class Parser {
private:
    std::ifstream *inputFile;
//    std::map<std::string, Operator*> operators;
    std::map<std::string, Type*> types;
    std::map<std::string, Keyword*> keywords;
    std::map<std::string, Variable*> variables;

    //skip spaces and return index of first non-space
    void skipSpaces(ParserContext &ctx);
    char nextNonSpace(ParserContext &ctx);
    bool isIdentifierChar(char c);
    bool isDigit(char c);
    uint getLevel(ParserContext &ctx);
    std::string readIdentifier(ParserContext &ctx);
public:
    Parser(std::ifstream &inputFile);
    Node *parse();
//    std::vector<std::string> split(std::string &s);
};
