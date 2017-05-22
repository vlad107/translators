#include "lib.h"

std::string Parser::Parser::s;
size_t Parser::Parser::pos = 0;

Parser::Parser(std::string const &s) {
    Parser::s = s;
}

const std::vector<std::regex> Parser::ZERO::regs = {std::regex("^0")};
bool Parser::ZERO::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
Parser::ZERO* Parser::ZERO::parse() {
    ZERO* result = new ZERO;
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            size_t len = sm.length(0);
            result->_value = tmp_str.substr(0, len);
            pos += len;
            while ((pos < s.size()) && (isspace(s[pos]))) ++pos;
            return result;
        }
    }
    return nullptr;
}
Parser::e* Parser::e::parse() {
    e* result(new e);
    if (ZERO::match()) {
        result->children.push_back(ZERO::parse());
        if ((pos != s.size()) && (!ZERO::match()) && (pos != s.size()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(e1::parse());
        if ((pos != s.size()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        return result;
    }
    return nullptr;
}

Parser::e1* Parser::e1::parse() {
    e1* result(new e1);
    if (ZERO::match()) {
        result->children.push_back(e::parse());
        if ((pos != s.size()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        return result;
    }
    if (pos == s.size()) {
        return result;
    }
    return nullptr;
}

Parser::start* Parser::start::parse() {
    start* result(new start);
    if (ZERO::match()) {
        result->children.push_back(e::parse());
        if ((pos != s.size()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        return result;
    }
    return nullptr;
}

