#include <cmath>

#include "header.h"

float count_RPN(const std::string &str) {
    std::string loc_str = str + ' ';
    std::stack<float> buff;
    std::string tmp_el_num, tmp_el_operation;
    for (int i = 0; i < loc_str.size(); i++) {
        if (loc_str[i] != ' ') {
            if ((loc_str[i] >= '0' and loc_str[i] <= '9') or loc_str[i] == '.') {
                tmp_el_num += loc_str[i];
            } else {
                tmp_el_operation += loc_str[i];
            }
        } else {
            if (!tmp_el_num.empty()) {
                buff.push(stof(tmp_el_num, nullptr));
                tmp_el_num = "";
            } else if (!tmp_el_operation.empty()) {
                if (tmp_el_operation == "-") {
                    float a = buff.top();
                    buff.pop();
                    float b = buff.top();
                    buff.pop();
                    buff.push(b - a);
                } else if (tmp_el_operation == "+") {
                    float a = buff.top();
                    buff.pop();
                    float b = buff.top();
                    buff.pop();
                    buff.push(a + b);
                } else if (tmp_el_operation == "*") {
                    float a = buff.top();
                    buff.pop();
                    float b = buff.top();
                    buff.pop();
                    buff.push(a * b);
                } else if (tmp_el_operation == "/") {
                    float a = buff.top();
                    buff.pop();
                    float b = buff.top();
                    buff.pop();
                    buff.push(b / a);
                } else if (tmp_el_operation == "sin") {
                    float a = buff.top();
                    buff.pop();
                    buff.push(std::sin(a));
                } else if (tmp_el_operation == "cos") {
                    float a = buff.top();
                    buff.pop();
                    buff.push(std::cos(a));
                } else if (tmp_el_operation == "tg") {
                    float a = buff.top();
                    buff.pop();
                    buff.push(std::tan(a));
                } else if (tmp_el_operation == "ctg") {
                    float a = buff.top();
                    buff.pop();
                    buff.push(1 / std::tan(a));
                } else if (tmp_el_operation == "exp") {
                    float a = buff.top();
                    buff.pop();
                    buff.push(std::exp(a));
                } else {
                    std::cerr << "Error: Invalid expression" << std::endl;
                    exit(1);
                }
                tmp_el_operation = "";
            }
        }
    }
    return buff.top();
}
