#include "lib.h"

std::string Parser::Parser::s;
size_t Parser::Parser::pos = 0;

Parser::Parser(std::string const &s) {
    Parser::s = s;
}

const std::vector<std::regex> Parser::And::regs = {std::regex("^and")};
const std::vector<std::regex> Parser::CLOSE_BRACKET::regs = {std::regex("^\\)")};
const std::vector<std::regex> Parser::Digit::regs = {std::regex("^[0-9]+")};
const std::vector<std::regex> Parser::Div::regs = {std::regex("^/")};
const std::vector<std::regex> Parser::Eq::regs = {std::regex("^=")};
const std::vector<std::regex> Parser::Gr::regs = {std::regex("^>")};
const std::vector<std::regex> Parser::GrOrEq::regs = {std::regex("^>=")};
const std::vector<std::regex> Parser::If::regs = {std::regex("^if")};
const std::vector<std::regex> Parser::Le::regs = {std::regex("^<")};
const std::vector<std::regex> Parser::LeOrEq::regs = {std::regex("^<=")};
const std::vector<std::regex> Parser::Minus::regs = {std::regex("^-")};
const std::vector<std::regex> Parser::Mult::regs = {std::regex("^\\*")};
const std::vector<std::regex> Parser::Not::regs = {std::regex("^not")};
const std::vector<std::regex> Parser::OPEN_BRACKET::regs = {std::regex("^\\(")};
const std::vector<std::regex> Parser::Or::regs = {std::regex("^or")};
const std::vector<std::regex> Parser::Plus::regs = {std::regex("^\\+")};
const std::vector<std::regex> Parser::Print::regs = {std::regex("^print")};
const std::vector<std::regex> Parser::WS::regs = {std::regex("^[\n\t]")};
const std::vector<std::regex> Parser::Xor::regs = {std::regex("^xor")};
bool Parser::And::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::CLOSE_BRACKET::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Digit::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Div::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Eq::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Gr::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::GrOrEq::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::If::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Le::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::LeOrEq::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Minus::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Mult::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Not::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::OPEN_BRACKET::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Or::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Plus::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Print::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::WS::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
bool Parser::Xor::match() {
    for (auto &reg: regs) {
        std::smatch sm;
        std::string tmp_str(s.begin() + pos, s.end());
        if (std::regex_search(tmp_str, sm, reg)) {
            return true;
        }
    }
    return false;
}
Parser::And* Parser::And::parse() {
    And* result = new And;
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
Parser::CLOSE_BRACKET* Parser::CLOSE_BRACKET::parse() {
    CLOSE_BRACKET* result = new CLOSE_BRACKET;
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
Parser::Digit* Parser::Digit::parse() {
    Digit* result = new Digit;
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
Parser::Div* Parser::Div::parse() {
    Div* result = new Div;
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
Parser::Eq* Parser::Eq::parse() {
    Eq* result = new Eq;
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
Parser::Gr* Parser::Gr::parse() {
    Gr* result = new Gr;
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
Parser::GrOrEq* Parser::GrOrEq::parse() {
    GrOrEq* result = new GrOrEq;
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
Parser::If* Parser::If::parse() {
    If* result = new If;
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
Parser::Le* Parser::Le::parse() {
    Le* result = new Le;
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
Parser::LeOrEq* Parser::LeOrEq::parse() {
    LeOrEq* result = new LeOrEq;
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
Parser::Minus* Parser::Minus::parse() {
    Minus* result = new Minus;
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
Parser::Mult* Parser::Mult::parse() {
    Mult* result = new Mult;
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
Parser::Not* Parser::Not::parse() {
    Not* result = new Not;
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
Parser::OPEN_BRACKET* Parser::OPEN_BRACKET::parse() {
    OPEN_BRACKET* result = new OPEN_BRACKET;
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
Parser::Or* Parser::Or::parse() {
    Or* result = new Or;
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
Parser::Plus* Parser::Plus::parse() {
    Plus* result = new Plus;
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
Parser::Print* Parser::Print::parse() {
    Print* result = new Print;
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
Parser::WS* Parser::WS::parse() {
    WS* result = new WS;
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
Parser::Xor* Parser::Xor::parse() {
    Xor* result = new Xor;
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
Parser::binaryBoolOp* Parser::binaryBoolOp::parse() {
    binaryBoolOp* result(new binaryBoolOp);
    if (And::match()) {
        result->children.push_back(And::parse());
        return result;
    }
    if (Or::match()) {
        result->children.push_back(Or::parse());
        return result;
    }
    if (Xor::match()) {
        result->children.push_back(Xor::parse());
        return result;
    }
    return nullptr;
}

Parser::binaryDigitOp* Parser::binaryDigitOp::parse() {
    binaryDigitOp* result(new binaryDigitOp);
    if (Minus::match()) {
        result->children.push_back(Minus::parse());
        return result;
    }
    if (Plus::match()) {
        result->children.push_back(Plus::parse());
        return result;
    }
    if (Mult::match()) {
        result->children.push_back(Mult::parse());
        return result;
    }
    if (Div::match()) {
        result->children.push_back(Div::parse());
        return result;
    }
    return nullptr;
}

Parser::cmpDigits* Parser::cmpDigits::parse() {
    cmpDigits* result(new cmpDigits);
    if (Eq::match()) {
        result->children.push_back(Eq::parse());
        return result;
    }
    if (Le::match()) {
        result->children.push_back(Le::parse());
        return result;
    }
    if (Gr::match()) {
        result->children.push_back(Gr::parse());
        return result;
    }
    if (LeOrEq::match()) {
        result->children.push_back(LeOrEq::parse());
        return result;
    }
    if (GrOrEq::match()) {
        result->children.push_back(GrOrEq::parse());
        return result;
    }
    return nullptr;
}

Parser::cond_expr* Parser::cond_expr::parse() {
    cond_expr* result(new cond_expr);
    if (Not::match()) {
        result->children.push_back(unaryBoolOp::parse());
        if ((!And::match()) and (!Eq::match()) and (!Gr::match()) and (!GrOrEq::match()) and (!Le::match()) and (!LeOrEq::match()) and (!Not::match()) and (!Or::match()) and (!Xor::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(cond_expr::parse());
        return result;
    }
    if (And::match() || Or::match() || Xor::match()) {
        result->children.push_back(binaryBoolOp::parse());
        if ((!And::match()) and (!Eq::match()) and (!Gr::match()) and (!GrOrEq::match()) and (!Le::match()) and (!LeOrEq::match()) and (!Not::match()) and (!Or::match()) and (!Xor::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(cond_expr::parse());
        if ((!And::match()) and (!Eq::match()) and (!Gr::match()) and (!GrOrEq::match()) and (!Le::match()) and (!LeOrEq::match()) and (!Not::match()) and (!Or::match()) and (!Xor::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(cond_expr::parse());
        return result;
    }
    if (Eq::match() || Gr::match() || GrOrEq::match() || Le::match() || LeOrEq::match()) {
        result->children.push_back(cmpDigits::parse());
        if ((!Digit::match()) and (!Div::match()) and (!Minus::match()) and (!Mult::match()) and (!Plus::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(int_expr::parse());
        if ((!Digit::match()) and (!Div::match()) and (!Minus::match()) and (!Mult::match()) and (!Plus::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(int_expr::parse());
        return result;
    }
    return nullptr;
}

Parser::digit* Parser::digit::parse() {
    digit* result(new digit);
    if (Digit::match()) {
        result->children.push_back(Digit::parse());
        return result;
    }
    return nullptr;
}

Parser::expr* Parser::expr::parse(int depth) {
    expr* result(new expr);
    result->depth = depth;
    if (If::match()) {
        result->children.push_back(if_expr::parse(depth));
        return result;
    }
    if (Print::match()) {
        result->children.push_back(void_expr::parse(depth));
        return result;
    }
    return nullptr;
}

Parser::if_expr* Parser::if_expr::parse(int depth) {
    if_expr* result(new if_expr);
    result->depth = depth;
    if (If::match()) {
        result->children.push_back(If::parse());
        if ((!And::match()) and (!Eq::match()) and (!Gr::match()) and (!GrOrEq::match()) and (!Le::match()) and (!LeOrEq::match()) and (!Not::match()) and (!Or::match()) and (!Xor::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(cond_expr::parse());
        if ((!If::match()) and (!Print::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(expr::parse(depth + 1));
        return result;
    }
    if (If::match()) {
        result->children.push_back(If::parse());
        if ((!And::match()) and (!Eq::match()) and (!Gr::match()) and (!GrOrEq::match()) and (!Le::match()) and (!LeOrEq::match()) and (!Not::match()) and (!Or::match()) and (!Xor::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(cond_expr::parse());
        if ((!If::match()) and (!Print::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(expr::parse(depth + 1));
        if ((!If::match()) and (!Print::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(expr::parse(depth + 1));
        return result;
    }
    return nullptr;
}

Parser::int_expr* Parser::int_expr::parse() {
    int_expr* result(new int_expr);
    if (Div::match() || Minus::match() || Mult::match() || Plus::match()) {
        result->children.push_back(binaryDigitOp::parse());
        if ((!Digit::match()) and (!Div::match()) and (!Minus::match()) and (!Mult::match()) and (!Plus::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(int_expr::parse());
        if ((!Digit::match()) and (!Div::match()) and (!Minus::match()) and (!Mult::match()) and (!Plus::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(int_expr::parse());
        return result;
    }
    if (Minus::match()) {
        result->children.push_back(unaryDigitOp::parse());
        if ((!Digit::match()) and (!Div::match()) and (!Minus::match()) and (!Mult::match()) and (!Plus::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(int_expr::parse());
        return result;
    }
    if (Digit::match()) {
        result->children.push_back(digit::parse());
        return result;
    }
    return nullptr;
}

Parser::start* Parser::start::parse() {
    start* result(new start);
    if (If::match() || Print::match()) {
        result->children.push_back(expr::parse(1));
        return result;
    }
    return nullptr;
}

Parser::unaryBoolOp* Parser::unaryBoolOp::parse() {
    unaryBoolOp* result(new unaryBoolOp);
    if (Not::match()) {
        result->children.push_back(Not::parse());
        return result;
    }
    return nullptr;
}

Parser::unaryDigitOp* Parser::unaryDigitOp::parse() {
    unaryDigitOp* result(new unaryDigitOp);
    if (Minus::match()) {
        result->children.push_back(Minus::parse());
        return result;
    }
    return nullptr;
}

Parser::void_expr* Parser::void_expr::parse(int depth) {
    void_expr* result(new void_expr);
    result->depth = depth;
    if (Print::match()) {
        result->children.push_back(Print::parse());
        if ((!Digit::match()) and (!Div::match()) and (!Minus::match()) and (!Mult::match()) and (!Plus::match()))
        {
            std::cerr << "Parse error\n";
            exit(1);
        }
        result->children.push_back(int_expr::parse());
        return result;
    }
    return nullptr;
}

