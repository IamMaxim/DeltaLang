#include "Parser.h"

int main() {
    std::ifstream ifs("code");
    Parser parser(ifs);
    parser.parse();
    return 0;
}