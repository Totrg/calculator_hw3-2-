#include "header.h"

int main() {
    std::cout
            << "Input format:\n    --Pi is P\n    --decimal separator is dot\n    --functions require brackets [ex: function(arg)]\nEnter problem:\n";
    while (true) {
        std::string str;
        std::cin >> str;
        //std::cout << infix_to_RPN(str) << std::endl;
        std::cout << count_RPN(infix_to_RPN(str)) << std::endl;
        std::cout << "\nEnter problem:\n";
    }
    return 0;
}
