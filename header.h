#ifndef CALCULATOR_HEADER_HPP_
#define CALCULATOR_HEADER_HPP_

#include <iostream>
#include <stack>
#include <string>
#include <cmath>

std::string infix_to_RPN(const std::string& str);
float count_RPN(const std::string& str);

#endif //CALCULATOR_HEADER_HPP_
