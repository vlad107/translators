#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <map>
#include <set>

std::string const WS = "\t\r\n ";
std::string const EPSILON = "EPSILON";
std::string const DOLLAR = "DOLLAR";


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

std::string &rtrim(std::string &s);

std::string &ltrim(std::string &s);

std::string &trim(std::string &s);

void read_tokens(std::vector<std::string> *tokens);

void add_rules(std::string s);

void generate_first(std::string const &var);

void generate_follow(std::string const &var);

#endif // HELPER_H
