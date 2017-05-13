#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <map>

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

};

struct Terminal {

    Terminal();
    Terminal(std::vector<std::string> const &);

    std::vector<std::string> _regexps;

};

extern std::map<std::string, Variable*> vars;
extern std::map<std::string, Terminal*> terminals;

std::string const WS = "\t\r\n ";

std::string &rtrim(std::string &s);

std::string &ltrim(std::string &s);

std::string &trim(std::string &s);

void read_tokens(std::vector<std::string> *tokens);

#endif // HELPER_H
