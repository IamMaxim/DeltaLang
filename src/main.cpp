#include "Parser.h"

int main() {
    std::ifstream ifs("code");
    Parser parser(ifs);
    try {
        parser.parse();
    } catch (std::string s) {
        std::cout << s << '\n';
    }
    return 0;
}