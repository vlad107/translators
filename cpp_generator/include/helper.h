#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <map>
#include <set>

std::string const WS = "\t\r\n ";
std::string const EPSILON = "EPSILON";
std::string const DOLLAR = "DOLLAR";
std::string const TAB = "    ";

struct Rule {
    Rule();
    Rule(std::string const &);

    std::vector<std::pair<std::string, std::string>> _children;
    bool _empty;
};

struct Variable {

    Variable();
    Variable(std::string const &, std::vector<std::string> const &);

    std::string _attr_s;
    std::vector<Rule> _cases;
    std::vector<std::string> _first;
    bool _eps;
    std::set<std::string> _follow;

};

struct Terminal {

    Terminal();
    Terminal(std::vector<std::string> const &);

    std::vector<std::string> _regexps;
    bool _eps;
    std::set<std::string> _follow;

};

extern std::map<std::string, Variable*> vars;
extern std::map<std::string, Terminal*> terminals;

void read_tokens(std::istream & in, std::vector<std::string> & tokens);

void add_rules(std::string const & s);

void generate_first(std::string const &var);

void generate_follow(std::string const &var);

std::string &normalize(std::string &s, bool &literal, std::string const escaped = "()[]+*\"\'");

void parse_attributes(std::string const &attr_s, std::vector<std::pair<std::string, std::string>> &attr_v);

void add_first_by_rule(std::vector<std::pair<std::string, std::string>>::iterator const &rule_start,
                       std::vector<std::pair<std::string, std::string>>::iterator const &rule_end,
                       std::vector<std::string> &fst);

void remove_left_recursion();

#endif // HELPER_H
