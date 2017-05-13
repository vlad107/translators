#include "helper.h"

#include <iostream>
#include <stdint.h>
#include <functional>

std::map<std::string, Variable*> vars;
std::map<std::string, Terminal*> terminals;

std::string &rtrim(std::string &s) {
    s.erase(s.find_last_not_of(WS) + 1);
    return s;
}

std::string &ltrim(std::string &s) {
    s.erase(0, s.find_first_not_of(WS));
    return s;
}

std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

std::string &normalize(std::string &s, std::string const escaped = "()[]+*\"\'") {

    if ((s.size() >= 2) && (s[0] == '\'') && (s[s.size() - 1] == '\'')) {
        s = s.substr(1, s.size() - 2);
    }

    std::string res;
    for (auto c: s) {

        if (escaped.find(c) != std::string::npos) {

            res += '\\';

        }
        res += c;

    }

    s = res;
    return s;

}


std::vector<std::string> &split(const std::string &s, std::function<bool(uint8_t)> issep, std::vector<std::string> &res) {

    std::string cur;
    for (auto c: s) {

        if (!issep(c)) {

            cur += c;

        } else {

            if (!cur.empty()) {

                res.push_back(cur);

            }

        }
    }
    return res;
}

Rule::Rule() {
}

Rule::Rule(std::string const &children_s) {

    std::vector<std::string> chld_v;
    split(children_s, [](char cur)
    {
        return isspace(cur);
    }, chld_v);

    if (chld_v.empty()) {
        _empty = true;
        return;
    }
    _empty = false;

    for (auto &chld: chld_v) {

        if (chld[0] == '[') {
            if ((!_children.empty()) && (chld[chld.size() - 1] == ']')) {

                if (_children.back().second == "") {

                    _children.back().second = chld.substr(1, chld.size() - 2);

                } else {

                    std::cerr << "WARNING: should be only one argument's block" << std::endl;
                    std::cerr << "    " << chld << " ignored" << std::endl;

                }

            } else {

                std::cerr << "WARNING: bad syntax" << std::endl;
                std::cerr << "   " << chld << " ignored" << std::endl;

            }

        } else {

            _children.emplace_back(chld, "");

        }

    }

}

Variable::Variable() {
}

Variable::Variable(std::string const &attr_s, std::vector<std::string> const &cases)
    : _attr_s(attr_s)
{

    _cases.clear();
    for (auto &cs: cases) {

        _cases.emplace_back(cs);

    }

}

Terminal::Terminal() {
}

Terminal::Terminal(std::vector<std::string> const &regexps)
    : _regexps(regexps) {

    for (auto &rg: _regexps) {
        trim(rg);
        normalize(rg);
    }

}

void read_tokens(std::vector<std::string> *tokens) {

    std::string line;
    while (getline(std::cin, line, ';')) {

        trim(line);
        if (!line.empty()) {

            tokens->push_back(line);

        }

    }

}

std::string extract_attributes(std::string &s) {

    size_t st = s.find("[");
    std::string attrs = "";
    if (st != std::string::npos) {

        size_t fi = s.find("]", st);

        if (fi != std::string::npos) {

            attrs = s.substr(st + 1, fi - st - 1);

        } else {

            std::cerr << "\"" << s << "\"" << " contains incorrect format for attributes" << std::endl;

        }

        s = s.substr(0, st);
        trim(s);

    }

    return attrs;
}

void add_terminal(std::string const &term_s, std::vector<std::string> const &cases) {

    if (terminals.find(term_s) != terminals.end()) {

        std::cerr << "WARNING: redefinition of terminal " << term_s << std::endl;

    }

    terminals[term_s] = new Terminal(cases);

}

void add_var(const std::string &var_s, const std::string &attributes, const std::vector<std::string> &cases) {

    if (vars.find(var_s) != vars.end()) {

        std::cerr << "WARNING: redefinition of variable " << var_s << std::endl;
        return;

    }

    vars[var_s] = new Variable(attributes, cases);

}

void add_rules(std::string s) {

    size_t index_delim = s.find(":");
    if (index_delim == std::string::npos) {
        std::cerr << "WARNING: should be \":\" in rule" << std::endl;
        return;
    }

    std::string rule_s = s.substr(0, index_delim);
    trim(rule_s);

    std::string attr_s = extract_attributes(rule_s);

    if (rule_s.empty()) {
        std::cerr << "rule is empty" << std::endl;
        return;
    }

    std::vector<std::string> cases;
    split(s.substr(index_delim + 1), [](char cur)
    {
        return cur == '|';
    }, cases);

    bool isterminal = isupper(rule_s[0]);

    if (!isterminal) {

        add_var(rule_s, attr_s, cases);

    } else {
        // Terminal

        if (!attr_s.empty()) {

            std::cerr << "WARNING: " << attr_s << " will be omitted for terminal" << std::endl;

        }

        add_terminal(rule_s, cases);

    }
}