#include "helper.h"

#include <iostream>
#include <stdint.h>
#include <functional>
#include <regex>
#include <fstream>

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

    const std::string op = "([{\"\'";
    const std::string cl = ")]}\"\'";

    std::string cur;
    size_t esc = std::string::npos;
    for (auto c: s) {

        if (esc != std::string::npos) {

            cur += c;
            if (c == cl[esc]) {

                esc = std::string::npos;

            }

        } else {

            if (!issep(c)) {

                cur += c;
                esc = op.find(c);

            } else {

                if (!cur.empty()) {

                    res.push_back(cur);
                    cur = "";

                }

            }

        }

    }

    if (!cur.empty()) {

        res.push_back(cur);

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

    for (auto &cs: cases) {

        _cases.emplace_back(cs);

    }

}

Terminal::Terminal() {
}

Terminal::Terminal(std::vector<std::string> const &regexps)
    : _regexps(regexps)
    , _eps(false) {

    for (auto &rg: _regexps) {

        trim(rg);
        normalize(rg);

        if (std::regex_match("", std::regex(rg))) {

            _eps = true;

        }

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

void add_first_by_rule(std::vector<std::pair<std::string, std::string>>::iterator const &rule_start,
                       std::vector<std::pair<std::string, std::string>>::iterator const &rule_end,
                       std::vector<std::string> &fst) {

    for ( auto it = rule_start; it != rule_end; ++it ) {

        auto child = *it;

        bool isterminal = isupper(child.first[0]);
        if (isterminal) {

            fst.push_back(child.first);
            if (terminals[child.first]->_eps) {

                fst.push_back(EPSILON);

            } else {

                break;

            }

        } else {

            generate_first(child.first);
            fst.insert(fst.end(),
                       vars[child.first]->_first.begin(),
                       vars[child.first]->_first.end());

            if (!vars[child.first]->_eps) {

                break;

            }

        }

    }
}

std::map<std::string, int> color;

void generate_first(std::string const &var) {

    if (vars.find(var) == vars.end()) {

        std::cerr << "WARNING: " << var << " was not declarated" << std::endl;
        return;

    }

    if (color[var] == 2) return;

    if (color[var] == 1) {

        std::cerr << "WARNING: cyclic grammar" << std::endl;
        std::cerr << "    trying to define " << var << " via " << var << std::endl;
        return;

    }
    color[var] = 1;

    auto *info = vars[var];
    bool was_eps = false;

    for (auto &cs: info->_cases) {

        if (cs._children.empty()) {

            if (!was_eps) {

                info->_first.push_back(EPSILON);

            }

        } else {

            add_first_by_rule(cs._children.begin(), cs._children.end(), info->_first);

        }

    }

    std::sort(info->_first.begin(), info->_first.end());
    info->_first.resize(std::unique(info->_first.begin(), info->_first.end()) - info->_first.begin());

    info->_eps = (std::find(info->_first.begin(),
                            info->_first.end(),
                            EPSILON)
                  != info->_first.end());

    color[var] = 2;

}

void add_follow(std::string const &name, std::vector<std::string> const &follow) {

    if (name.empty()) {

        std::cerr << "WARNING: trying to add follow to the empty entry";
        return;

    }

    bool isterminal = isupper(name[0]);
    if (isterminal) {

        auto it = terminals.find(name);
        if (it == terminals.end()) {

            std::cerr << "WARNING: invalid terminal -- " << name << std::endl;

        } else {

            it->second->_follow.insert(follow.begin(), follow.end());

        }

    } else {

        auto it = vars.find(name);
        if (it == vars.end()) {

            std::cerr << "WARNING: invalid var -- " << name << std::endl;

        } else {

            it->second->_follow.insert(follow.begin(), follow.end());

        }

    }

}

void generate_follow(std::string const &var) {

    if (vars.find(var) == vars.end()) {

        std::cerr << "WARNING: " << var << " was not declarated" << std::endl;
        return;

    }

    auto *info = vars[var];

    for (auto &rule: info->_cases) {

        for ( auto it = rule._children.begin(); it != rule._children.end(); ++it ) {

            std::vector<std::string> fst;
            add_first_by_rule(it + 1, rule._children.end(), fst);

            if (fst.empty()) {

                fst.push_back(DOLLAR);

            }
            for (auto &cur: fst) {
                if (cur == EPSILON) {

                    cur = DOLLAR;

                }
            }

            add_follow(it->first, fst);

        }

    }

}

uint32_t depth;

std::string const TAB = "    ";

void print_impl(std::ofstream &out, std::string str) {

    for ( uint32_t i = 0; i < depth; i++ ) {

        out << TAB;

    }

    out << str;

}

void print_structure(std::ofstream &out, std::pair<std::string, Variable*> pr) {

    print_impl(out, "struct " + pr.first + " {\n");
    ++depth;

    print_impl(out, "void parse(" + pr.second->_attr_s + ");\n");

    --depth;
    print_impl(out, "};\n\n");

}

void print_structures(std::ofstream &out) {

    out << "\n";

    for (auto &pr: vars) {

        print_structure(out, pr);

    }

    out << "\n";

}

void print_header() {

    std::ofstream out("../gen/lib.h", std::ofstream::out);

    out << "#ifndef LIB_H\n";
    out << "#define LIB_H\n";

    out << "#include <regex>\n";
    out << "#include <iostream>\n";
    out << "#include <vector>\n";
    out << "\n\n";


    print_impl(out, "struct Parser {\n\n");
    ++depth;

    print_impl(out, "std::string s;\n");
    print_impl(out, "int pos;\n\n");

    print_impl(out, "Parser(std::string s);\n");

    print_structures(out);

    --depth;
    print_impl(out, "};\n\n");


    out << "#endif\n";

    out.close();

}

void print_code() {

    print_header();

//    print_source();

//    std::cout << "std::string s;\n";
//    std::cout << "size_t pos;\n\n";

//    std::cout << "struct Node {\n";
//    std::cout << "};\n\n";
//    for (auto &name: names) {
//        std::cout << "struct " << name << " : Node {\n";
//        auto ninfo = info[name];
//        std::cout << TAB << "std::vector<Node> childs;\n\n";

//        for (auto attr: ninfo->attrs) {
//            std::cout << TAB << attr << ";\n";
//        }
//        if (isupper(name[0])) {
//            std::cout << TAB << "const std::vector<std::regex> regs = {";
//            bool first = true;
//            for (auto &rs: rules_by_name[name][0]->srs) {
//                if (!first) std::cout << ",";
//                first = false;
//                std::cout << "std::regex(\"" << rs << "\")";
//            }
//            std::cout << "};\n";
//        }
//        std::cout << TAB << "static " << name << " parse(";
//        bool first = true;
//        for (auto &attr: ninfo->attrs) {
//            if (!first) {
//                std::cout << ",";
//            }
//            first = false;
//            std::cout << trim(attr);
//        }
//        std::cout << ");\n";
//        if (isupper(name[0])) {
//            std::cout << TAB << "static bool match();\n";
//        }
//        std::cout << "};\n";
//    }
//    for (auto &name: names) {
//        auto ninfo = info[name];
//        //std::cout << "struct " << name << " : Node {\n";
//        std::cout << "static " << name << " " << name << "::parse(";
//        bool first = true;
//        for (auto &attr: ninfo->attrs) {
//            if (!first) {
//                std::cout << ",";
//            }
//            first = false;
//            std::cout << trim(attr);
//        }
//        std::cout << ") {\n";
//        if (islower(name[0])) {
//            // notTerminal
//            for (auto &rule: rules_by_name[name]) {
//                rule->first.erase(std::unique(rule->first.begin(), rule->first.end()), rule->first.end());
//                for (auto &term: rule->first) {
//                    std::cout << TAB << "if (" << term << "::" << "match())" << " {\n";
//                    for (auto &chld: rule->childs) {
//                        std::cout << TAB << TAB << chld.first << "::" << "parse(";
//                        bool first = false;
//                        std::cout << chld.second;
//                        std::cout << ");\n";
//                    }
//                    std::cout << TAB << "}\n";
//                }
//            }
//            std::cout <<  "};\n";
//        } else {
//            std::cout << "}\n";
//            // Terminal
//            for (auto &rule: rules_by_name[name]) {
//                std::cout << "bool " << name << "::match()" << " {\n";
//                std::cout << TAB << "for (auto &reg: regs) {\n";
//                std::cout << TAB << TAB << "for (int i = 1; i <= 10; i++) {\n";
//                std::cout << TAB << TAB << TAB << "if (std::regex_match(s.begin() + pos, s.begin() + pos + i, reg)) {\n";
//                std::cout << TAB << TAB << TAB << TAB << "return true;\n";
//                std::cout << TAB << TAB << TAB << "}\n";
//                std::cout << TAB << TAB << "}\n";
//                std::cout << TAB << "}\n";
//                std::cout << TAB << "return false;\n";
//                std::cout << "}\n";
//            }
//        }
//    }
//    std::cout << "int main() {\n}\n";

}
