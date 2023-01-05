#include "header.h"

int priority(const std::string &str) {
    if (str == "(") return 0;
    else if (str == "-" or str == "+") return 1;
    else if (str == "*" or str == "/") return 2;
    else if (str == "sin" or str == "cos" or str == "tg" or str == "ctg" or str == "exp") return 3;
    else {
        std::cerr << "Error: Invalid expression [priority(" << str << ")]" << std::endl;
        exit(1);
    }
}

std::string infix_to_RPN(const std::string &str) {
    std::string rez;
    std::stack<std::string> buff;
    bool prev_char_is_num = false, prev_el_is_num = false;
    bool search_flag = false;
    bool sin_search = false,
            cos_search = false,
            tg_search = false,
            ctg_search = false,
            exp_search = false;
    std::string tmp;
    float x;
    bool is_x_defined = false;
    std::string prev_el;
    bool firstel = true;
    for (auto el: str) {
        if (sin_search) {
            if (tmp == "sin") {
                buff.push(tmp);
                sin_search = false;
                search_flag = false;
                tmp = "";
            } else if (tmp.size() == 3) {
                std::cerr << "Error: Invalid expression [unknown function name]" << std::endl;
                exit(1);
            } else tmp += el;
        } else if (cos_search) {
            if (tmp == "cos") {
                buff.push(tmp);
                cos_search = false;
                ctg_search = false;
                search_flag = false;
                tmp = "";
            } else if (tmp.size() == 3) {
                cos_search = false;
            } else tmp += el;
        } else if (tg_search) {
            if (tmp == "tg") {
                buff.push(tmp);
                tg_search = false;
                search_flag = false;
                tmp = "";
            } else if (tmp.size() == 2) {
                std::cerr << "Error: Invalid expression [unknown function name]" << std::endl;
                exit(1);
            } else tmp += el;
        } else if (ctg_search) {
            if (tmp == "ctg") {
                buff.push(tmp);
                ctg_search = false;
                cos_search = false;
                search_flag = false;
                tmp = "";
            } else if (tmp.size() == 3) {
                std::cerr << "Error: Invalid expression [unknown function name]" << std::endl;
                exit(1);
            } else tmp += el;
        } else if (exp_search) {
            if (tmp == "exp") {
                buff.push(tmp);
                exp_search = false;
                search_flag = false;
                tmp = "";
            } else if (tmp.size() == 3) {
                std::cerr << "Error: Invalid expression [unknown function name]" << std::endl;
                exit(1);
            } else tmp += el;
        }
        if (el == ' ' and !search_flag)
            continue;
        else if (el < '0' or el > '9' and !search_flag) {
            if (prev_char_is_num and el != '.') {
                prev_char_is_num = false;
                prev_el_is_num = true;
                tmp += " ";
                rez += tmp;
                tmp = "";
            }
            if ((el >= 'a' and el <= 'z') or el == 'P') {
                switch (el) {
                    case 's':
                        sin_search = true;
                        search_flag = true;
                        tmp += el;
                        break;
                    case 'c':
                        cos_search = true;
                        ctg_search = true;
                        search_flag = true;
                        tmp += el;
                        break;
                    case 't':
                        tg_search = true;
                        search_flag = true;
                        tmp += el;
                        break;
                    case 'e':
                        exp_search = true;
                        search_flag = true;
                        tmp += el;
                        break;
                    case 'P':
                        rez += "P ";
                        prev_el_is_num = true;
                        break;
                    case 'x':
                        if (!is_x_defined) {
                            std::cout << "Enter x: ";
                            std::cin >> x;
                            std::cout << std::endl;
                            rez += std::to_string(x) + " ";
                            prev_el_is_num = true;
                            is_x_defined = true;
                        } else {
                            rez += std::to_string(x) + " ";
                            prev_el_is_num = true;
                        }
                        break;
                    default:
                        std::cerr << "Error: Invalid expression [unknown literal]" << std::endl;
                        exit(1);;
                }
            } else if (el == '.') {
                if (tmp.find('.') == std::string::npos and tmp.size() != 0) tmp += el;
                else {
                    std::cerr << "Error: Invalid expression [invalid float number format]" << std::endl;
                    exit(1);
                }
            } else if (el == '-') {
                std::string symbs = "(+-*/nsgp";
                if (symbs.find(prev_el) != std::string::npos or firstel) rez += "0 ";
                std::string str_tmp;
                str_tmp += el;
                while (!buff.empty() and priority(buff.top()) >= priority(str_tmp)) {
                    rez += buff.top() + " ";
                    buff.pop();
                }
                buff.push(str_tmp);
            } else if (el == '(') {
                std::string str_tmp;
                str_tmp += el;
                buff.push(str_tmp);
            } else if (el == ')') {
                while (buff.top() != "(") {
                    rez += buff.top() + " ";
                    buff.pop();
                }
                buff.pop();
            } else {
                std::string str_tmp;
                str_tmp += el;
                while (!buff.empty() and priority(buff.top()) >= priority(str_tmp)) {
                    rez += buff.top() + " ";
                    buff.pop();
                }
                buff.push(str_tmp);
            }
            prev_el_is_num = false;
        } else if (prev_char_is_num and el >= '0' and el <= '9' and !search_flag) tmp += el;
        else if (!prev_char_is_num and el >= '0' and el <= '9' and !search_flag) {
            prev_char_is_num = true;
            tmp += el;
        }
        std::string fsymbs = "nsgp";
        std::string symbs = "-+*/nsgp";
        std::string alls = "nsgpPx";
        if (!firstel)
            if ((prev_el == "." and (el > '9' or el < '0')) or
                (symbs.substr(1, 3).find(*str.begin()) != std::string::npos) or
                (symbs.find(*str.end()) != std::string::npos)) {
                std::cerr << "Error: Invalid expression [invalid input]" << std::endl;
                exit(1);
            }
        switch (el) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (prev_el == ")" or prev_el == "x" or prev_el == "P") {
                    std::cerr << "Error: Invalid expression [invalid symbol before number]" << std::endl;
                    exit(1);
                }
                break;
            case '+':
            case '/':
            case '*':
            case '-':
                if (symbs.contains(prev_el[0])) {
                    std::cerr << "Error: Invalid expression [wrong place for operator]" << std::endl;
                    exit(1);
                }
                break;
            case '(':
                if ((prev_el[0] >= '0' and prev_el[0] <= '9') or prev_el[0] == 'x' or prev_el[0] == 'P') {
                    std::cerr << "Error: Invalid expression [missing operator]" << std::endl;
                    exit(1);
                }
                break;
            case 'x':
            case 's':
            case 'c':
            case 't':
            case 'e':
            case 'P':
                if ((prev_el[0] >= '0' and prev_el[0] <= '9') or (alls.contains(prev_el[0]))) {
                    std::cerr << "Error: Invalid expression [double function]" << std::endl;
                    exit(1);
                }
                break;
            case ')':
                if ((prev_el[0] < '0' or prev_el[0] > '9') and prev_el[0] != 'x' and prev_el[0] != ')' and
                    prev_el[0] != '(' and prev_el[0] != 'P') {
                    std::cerr << "Error: Invalid expression [operator right before closing bracket]" << std::endl;
                    exit(1);
                }
                break;
            default:
                continue;
        }
        prev_el = el;
        firstel = false;
    }
    rez += tmp + " ";
    std::string ss = "0123456789";
    size_t buff_size = buff.size();
    for (int i = 0; i < buff_size; i++) {
        if (buff.top() != "(" and (ss.find(buff.top()) == std::string::npos)) {
            rez += buff.top() + " ";
            buff.pop();
        } else {
            std::cerr << "Error: Invalid expression" << std::endl;
            exit(1);
        }
    }
    return rez.substr(0, rez.size() - 1);
}
