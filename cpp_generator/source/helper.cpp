#include "helper.h"

#include <iostream>
#include <stdint.h>
#include <functional>
#include <regex>
#include <fstream>
#include <queue>

std::map<std::string, Variable*> vars;
std::map<std::string, Terminal*> terminals;

std::string &rtrim(std::string &s)
{
    s.erase(s.find_last_not_of(WS) + 1);
    return s;
}

std::string &ltrim(std::string &s)
{
    s.erase(0, s.find_first_not_of(WS));
    return s;
}

std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}

bool is_terminal(std::string const & name)
{
    if (name.empty())
    {
        std::cerr << "WARNING: empty name" << std::endl;
        return false;
    }
    return ('A' <= name[0]) && (name[0] <= 'Z');
}


std::string &normalize(std::string &s, bool &literal, std::string const escaped)
{
    literal = false;
    if ((s.size() >= 2) && (s[0] == '\'') && (s[s.size() - 1] == '\''))
    {
        s = s.substr(1, s.size() - 2);
        literal = true;
    }

    if (literal)
    {
        std::string res;
        for (auto c: s)
        {
            if (escaped.find(c) != std::string::npos)
            {
                res += '\\';
            }
            res += c;
        }
        s = res;
    }
    return s;

}


std::vector<std::string> &split(const std::string &s, std::function<bool(uint8_t)> issep, std::vector<std::string> &res, bool need_empty = false) {

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

                if (!cur.empty() || need_empty) {

                    res.push_back(cur);
                    cur = "";

                }

            }

        }

    }

    if (!cur.empty() || need_empty) {

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

Terminal::Terminal()
{
}

Terminal::Terminal(std::vector<std::string> const &regexps)
    : _regexps(regexps)
    , _eps(false)
{
    for (auto &rg: _regexps)
    {
        trim(rg);
        bool literal;
        normalize(rg, literal);

        if (std::regex_match("", std::regex(rg)))
        {
            _eps = true;
        }
        if (literal)
        {
            rg = "\'" + rg + "\'";
        }
    }
}

void read_tokens(std::istream & in, std::vector<std::string> & tokens)
{
    std::string line;
    while (getline(in, line, ';'))
    {
        trim(line);
        if (!line.empty())
        {
            tokens.push_back(line);
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

void add_rules(std::string const & s)
{
    size_t index_delim = s.find(":");
    if (index_delim == std::string::npos)
    {
        std::cerr << "WARNING: should be \":\" in rule" << std::endl;
        return;
    }

    std::string rule_s = s.substr(0, index_delim);
    trim(rule_s);

    std::string attr_s = extract_attributes(rule_s);

    if (rule_s.empty())
    {
        std::cerr << "rule is empty" << std::endl;
        return;
    }

    std::vector<std::string> cases;
    split(s.substr(index_delim + 1), [](char cur)
    {
        return cur == '|';
    }, cases, true);

    if (!is_terminal(rule_s))
    {
        add_var(rule_s, attr_s, cases);
    } else
    {                       // Terminal
        if (!attr_s.empty())
        {
            std::cerr << "WARNING: " << attr_s << " will be omitted for terminal" << std::endl;
        }
        add_terminal(rule_s, cases);
    }
}

void add_first_by_rule(std::vector<std::pair<std::string, std::string>>::iterator const &rule_start,
                       std::vector<std::pair<std::string, std::string>>::iterator const &rule_end,
                       std::vector<std::string> &fst)
{
    auto it = rule_start;
    for ( ; it != rule_end; ++it )
    {
        auto child = *it;

        if (is_terminal(child.first))
        {
            fst.push_back(child.first);
            if (!terminals[child.first]->_eps)
            {
                break;
            }
        } else
        {
            generate_first(child.first);
            fst.insert(fst.end(),
                       vars[child.first]->_first.begin(),
                       vars[child.first]->_first.end());

            if (!vars[child.first]->_eps)
            {
                break;
            }
        }
    }
    if (it == rule_end)
    {
        fst.push_back(EPSILON);
    }
}

std::map<std::string, int> color;

void generate_first(std::string const &var)
{
    if (vars.find(var) == vars.end())
    {
        std::cerr << "WARNING: " << var << " was not declarated" << std::endl;
        return;
    }

    if (color[var] == 2) return;

    if (color[var] == 1)
    {
        std::cerr << "WARNING: cyclic grammar" << std::endl;
        std::cerr << "    trying to define " << var << " via " << var << std::endl;
        return;
    }
    color[var] = 1;

    auto *info = vars[var];
    bool was_eps = false;

    for (auto &cs: info->_cases)
    {
        if (cs._children.empty())
        {
            if (!was_eps)
            {
                info->_first.push_back(EPSILON);
            }
        } else
        {
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

void add_follow(std::string const &name, std::vector<std::string> const &follow)
{
    if (name.empty())
    {
        std::cerr << "WARNING: trying to add follow to the empty entry";
        return;
    }

    if (is_terminal(name))
    {
        auto it = terminals.find(name);
        if (it == terminals.end())
        {
            std::cerr << "WARNING: invalid terminal -- " << name << std::endl;
        } else
        {
            it->second->_follow.insert(follow.begin(), follow.end());
        }
    } else
    {
        auto it = vars.find(name);
        if (it == vars.end())
        {
            std::cerr << "WARNING: invalid var -- " << name << std::endl;
        } else
        {
            it->second->_follow.insert(follow.begin(), follow.end());
        }
    }
}

void generate_follow(std::string const &var)
{
    if (vars.find(var) == vars.end())
    {
        std::cerr << "WARNING: " << var << " was not declarated" << std::endl;
        return;
    }

    auto *info = vars[var];

    for (auto &rule: info->_cases)
    {
        for ( auto it = rule._children.begin(); it != rule._children.end(); ++it )
        {
            std::vector<std::string> fst;
            add_first_by_rule(it + 1, rule._children.end(), fst);

            if (fst.empty())
            {
                fst.push_back(DOLLAR);
            }
            for (auto &cur: fst)
            {
                if (cur == EPSILON)
                {
                    cur = DOLLAR;
                }
            }
            add_follow(it->first, fst);
        }
    }
}

void parse_attributes(std::string const &attr_s, std::vector<std::pair<std::string, std::string>> &attr_v)
{
    std::vector<std::string> decls;
    split(attr_s, [](uint8_t c)
    {
        return (c == ',');
    }, decls);

    attr_v.resize(decls.size());
    for ( size_t i = 0; i < decls.size(); i++ )
    {
        std::vector<std::string> tokens;
        split(decls[i], isspace, tokens);
        if (tokens.size() == 2)
        {
            attr_v[i] = {tokens[0], tokens[1]};
        } else
        {
            std::cerr << "WARNING: wrong argument: " << decls[i] << std::endl;
        }
    }
}

void get_follow(std::string name, std::set<std::string> *fw)
{
    if (isupper(name[0]))
    {
        fw = &terminals[name]->_follow;
    } else
    {
        fw = &vars[name]->_follow;
    }
}

std::map<std::string, bool> reach_eps;

bool is_rule_eps(Rule &rule)
{
    for (auto &p: rule._children)
    {
        if ((is_terminal(p.first) && (!terminals[p.first]->_eps)) ||
            (!is_terminal(p.first) && (!vars[p.first]->_eps)))
        {
            return false;
        }
    }
    return true;
}

void make_eps() // slow algorithm
{
    bool found = true;
    while (found)
    {
        found = false;
        for ( auto &pr: vars )
        {
            if (!pr.second->_eps)
            {
                for ( auto &rule: pr.second->_cases )
                {
                    if (is_rule_eps(rule))
                    {
                        found = true;
                        pr.second->_eps = true;
                        break;
                    }
                }
            }
        }
    }
}

bool get_is_eps(std::string const & name)
{
    if (is_terminal(name))
    {
        return terminals[name]->_eps;
    } else
    {
        return vars[name]->_eps;
    }
}

void generate_cases(Rule &rule, std::vector<Rule> &res, Rule &cur_rule, uint32_t pos = 0)
{
    if (pos == rule._children.size())
    {
        res.push_back(cur_rule);
        return;
    }

    cur_rule._children.push_back(rule._children[pos]);
    generate_cases(rule, res, cur_rule, pos + 1);
    cur_rule._children.pop_back();

    if (get_is_eps(rule._children[pos].first))
    {
        generate_cases(rule, res, cur_rule, pos + 1);
    }
}

void remove_self_recursion(std::string &name)
{
    std::string name2 = name + "___" + name;
    vars[name2] = new Variable();
    vars[name2]->_attr_s = vars[name]->_attr_s;

    std::vector<std::pair<std::string, std::string>> attr_v;
    parse_attributes(vars[name]->_attr_s, attr_v);
    bool first = true;
    std::string str_attr;
    for (auto attr: attr_v)
    {
        if (!first)
        {
            str_attr += ", ";
        }
        first = false;
        str_attr += attr.second;
    }
    vars[name2]->_eps = false;

    std::vector<Rule> n_cases;
    for ( auto &rule: vars[name]->_cases )
    {
        if (rule._children.empty()) continue;

        if (rule._children[0].first != name)
        {
            n_cases.push_back(rule);
            n_cases.push_back(rule);
            n_cases.back()._children.push_back({name2, str_attr});
        } else
        {
            std::vector<std::pair<std::string, std::string>> nc(rule._children.begin() + 1, rule._children.end());
            Rule rl;
            rl._children = nc;
            rl._empty = false;
            vars[name2]->_cases.push_back(rl);
            rl._children.push_back({name2, rule._children[0].second});
            vars[name2]->_cases.push_back(rl);
        }
    }
    vars[name]->_cases = n_cases;
}

void remove_left_recursion()
{
//    make_eps();
//    for ( auto &pr: vars )
//    {
//        std::vector<Rule> n_cases;
//        for ( auto &rule: pr.second->_cases )
//        {
//            Rule cur_rule;
//            generate_cases(rule, n_cases, cur_rule);
//        }
//        pr.second->_cases = n_cases;
//    }

    std::vector<std::string> var_names;
    std::map<std::string, uint32_t> rev_num;
    for ( auto &pr: vars )
    {
        rev_num[pr.first] = var_names.size();
        var_names.push_back(pr.first);
    }
    for ( uint32_t i = 0; i < var_names.size(); i++ )
    {
        std::vector<Rule> n_cases;
        std::queue<Rule> q;
        for (auto &rule: vars[var_names[i]]->_cases)
        {
            q.push(rule);
        }
        while (!q.empty())
        {
            auto rule = q.front();
            q.pop();
            if ((rule._children.size() > 0) && (!is_terminal(rule._children[0].first)) && (rev_num[rule._children[0].first] < i))
            {
                std::string str = rule._children[0].first;
                for ( auto &str_rule: vars[str]->_cases)
                {
                    Rule t_rule = str_rule;
                    t_rule._children.insert(t_rule._children.end(), rule._children.begin() + 1, rule._children.end());
                    q.push(t_rule);
                }
            } else
            {
                n_cases.push_back(rule);
            }
        }
        vars[var_names[i]]->_cases = n_cases;
        remove_self_recursion(var_names[i]);
    }
}
