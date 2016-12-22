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
        std::string orig, s;

        getline(*inputFile, orig);
        level = getLevel(ctx, orig);
        s = orig.substr(ctx.column);
        printf("level is: %i\n", level);

        string id = readIdentifier(ctx, s);
        s = orig.substr(ctx.column);
        printf("string: <%s>\n", s.c_str());
        nextNonSpace(ctx, s);
        s = orig.substr(ctx.column-1);
        printf("string: <%s>\n", s.c_str());

        Type *type;
        Variable *var;
        Keyword *keyword;

        if ((type = types[id])) {
            string name = readIdentifier(ctx, s);
            if (s.length() > ctx.column) {
                s = orig.substr(ctx.column);
                printf("string: <%s>\n", s.c_str());
                printf("varname: %s\n", name.c_str());
                if (nextNonSpace(ctx, s) == '=') {
                    printf("reading var value");
                    s = orig.substr(ctx.column - 1);
                    printf("string: <%s>\n", s.c_str());
                    nextNonSpace(ctx, s);
                    s = orig.substr(ctx.column);
                    printf("string: <%s>\n", s.c_str());
                    string value = readIdentifier(ctx, s);
                    s = orig.substr(ctx.column);
                    printf("string: <%s>\n", s.c_str());
                    printf("value is: %s\n", value.c_str());
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

//returns level of current string
uint Parser::getLevel(ParserContext &ctx, std::string &s) {
    uint level = 0;
    char c;
    while (true) {
        c = s[level];
        if (c == '\t')
            level++;
        else break;
    }

    ctx.column += level;
    return (uint) level;
}

std::string Parser::readIdentifier(ParserContext &ctx, std::string s) {
    std::stringstream ss;
    char c;
    uint32_t i = 0;
    while (i < s.length()) {
        c = s[i];
        if (c == ' ' || c == '\n')
            break;

        if (!isIdentifierChar(c))
            ctx.throwException(("Unexpected character while parsing identifier: '" + std::to_string(c) + "'").c_str());

        ss << c;
        i++;
    }
    ctx.column += i;
    printf("Read identifier %s\n", ss.str().c_str());
    return ss.str();
}

char Parser::nextNonSpace(ParserContext &ctx, std::string &s) {
    char c;
    int i = 0;
    while ((c = s[i++])) {
        ctx.column++;
        if (c != ' ')
            return c;
    }
    return ' ';
}

/*
uint Parser::skipSpaces(std::string s, uint startIndex) {
    uint i = startIndex;
    char c;
    while ((c = s[i++])) {
        if (c != ' ')
            return i;
    }
    return 0;
}
*/
