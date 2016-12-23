#include <sstream>
#include "Parser.h"

Node *Parser::parse() {
    using namespace std;
    ParserContext ctx;
    uint level = 0, prevLevel = 0;

    //go to file start
    inputFile->seekg(0, ios::beg);
    inputFile->clear();
    while (inputFile->good()) {
        string str;
        getline(*inputFile, str);
        ctx.s = &str;
        printf("scanned line: %s\n", (*ctx.s).c_str());
        level = getLevel(ctx);
        printf("level is: %i\n", level);

        string id = readIdentifier(ctx);
        skipSpaces(ctx);
        if (!(*ctx.s)[ctx.column+1])
            ctx.throwException("Expected variable name");

        Type *type;
        Variable *var;
        Keyword *keyword;

        if ((type = types[id])) {
            string name = readIdentifier(ctx);
            if ((*ctx.s).length() > ctx.column) {
                printf("varname: %s\n", name.c_str());
                if (nextNonSpace(ctx) == '=') {
                    printf("reading var value\n");
                    skipSpaces(ctx);
                    string value = readIdentifier(ctx);
                    printf("value is: %s\n", value.c_str());
                    if (value == "")
                        ctx.throwException("Expected value");
                }
            }
        } else if ((var = variables[id])) {

        } else if ((keyword = keywords[id])) {

        }

        prevLevel = level;
        ctx.line++;
    }
}

Parser::Parser(std::ifstream &inputFile) {
    this->inputFile = &inputFile;

    types["int32"] = new Type;
}

bool Parser::isIdentifierChar(char c) {
    return c >= 'a' && c <= 'z' ||
           c >= 'A' && c <= 'Z' ||
           isDigit(c) || c == '_';
}

bool Parser::isDigit(char c) {
    return c >= '0' && c <= '9';
}

//returns level starting from current char (all previous chars are counted)
uint Parser::getLevel(ParserContext &ctx) {
    uint64_t level = ctx.column;
    char c;
    while (true) {
        c = (*ctx.s)[level];
        if (c == '\t')
            level++;
        else break;
    }
    ctx.column = level;
    return (uint) level;
}

std::string Parser::readIdentifier(ParserContext &ctx) {
    std::stringstream ss;
    char c;
    uint64_t i = ctx.column;
    while (i < (*ctx.s).length()) {
        c = (*ctx.s)[i];
        if (c == ' ' || c == '\n')
            break;

        if (!isIdentifierChar(c))
            ctx.throwException(("Unexpected character while parsing identifier: '" + std::to_string(c) + "'").c_str());

        ss << c;
        i++;
    }
    ctx.column = i;
    printf("Read identifier %s\n", ss.str().c_str());
    return ss.str();
}

char Parser::nextNonSpace(ParserContext &ctx) {
    char c;
    uint64_t i = ctx.column;
    while ((c = (*ctx.s)[i++])) {
        ctx.column++;
        if (c != ' ')
            return c;
    }
    return '\0';
}

void Parser::skipSpaces(ParserContext &ctx) {
    uint64_t i = ctx.column;
    char c;
    while ((c = (*ctx.s)[i++])) {
        if (c == ' ')
            ctx.column++;
        else return;
    }
}
