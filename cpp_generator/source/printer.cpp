#include "printer.h"
#include "helper.h"

#include <iostream>
#include <fstream>


uint32_t depth;

void print_impl(std::ofstream &out, std::string str)
{
    for ( uint32_t i = 0; i < depth; i++ )
    {
        out << TAB;
    }
    out << str;
}

void print_structure_term(std::ofstream &out, std::pair<std::string, Terminal*> pr)
{
    print_impl(out, "struct " + pr.first + " : TerminalNode {\n");
    ++depth;

//    print_impl(out, "static std::shared_ptr<" + "Node" + "> " + "parse();\n");
    print_impl(out, "static Parser::" + pr.first + "* parse();\n");
    print_impl(out, "static bool match();\n\n");
    print_impl(out, "virtual NodeType get_structure_name() { return NodeType::e_" + pr.first + "; }\n");
    print_impl(out, "static const std::vector<std::regex> regs;\n");

    --depth;
    print_impl(out, "};\n\n");

}

void print_structure_var(std::ofstream &out, std::pair<std::string, Variable*> pr) {

    print_impl(out, "struct " + pr.first + " : VariableNode {\n");
    ++depth;

    print_impl(out, "static Parser::" + pr.first + "*" + " parse(" + pr.second->_attr_s + ");\n\n");
    print_impl(out, "virtual NodeType get_structure_name() { return NodeType::e_" + pr.first + "; }\n");

    std::vector<std::pair<std::string, std::string>> attr_v;
    parse_attributes(pr.second->_attr_s, attr_v);

    for (auto &attr: attr_v) {
        print_impl(out, attr.first + " " + attr.second + ";\n");
    }

    --depth;
    print_impl(out, "};\n\n");

}

void print_structures(std::ofstream &out)
{
    out << "\n";

    print_impl(out, "enum NodeType {");
    bool first = true;
    for (auto &pr: terminals)
    {
        if (!first) out << ", ";
        first = false;
        out << "e_" << pr.first;
    }
    for (auto &pr: vars)
    {
        if (!first) out << ", ";
        first = false;
        out << "e_" << pr.first;
    }
    out << "};\n";

    print_impl(out, "struct Node\n");
    print_impl(out, "{\n");
    ++depth;

    print_impl(out, "virtual bool is_terminal() = 0;\n");
    print_impl(out, "virtual NodeType get_structure_name() = 0;\n");

    --depth;
    print_impl(out, "};\n");

    print_impl(out, "struct VariableNode : Node\n");
    print_impl(out, "{\n");
    ++depth;

    print_impl(out, "virtual bool is_terminal() { return false; }\n");
    print_impl(out, "std::vector<Node*> children;\n");

    --depth;
    print_impl(out, "};\n");

    print_impl(out, "struct TerminalNode : Node\n");
    print_impl(out, "{\n");
    ++depth;

    print_impl(out, "virtual bool is_terminal() { return true; }\n");
    print_impl(out, "std::string _value;\n");

    --depth;
    print_impl(out, "};\n");

    for (auto &pr: terminals)
    {
        print_structure_term(out, pr);
    }
    for (auto &pr: vars)
    {
        print_structure_var(out, pr);
    }
    out << "\n";
}

void print_header() {

    std::ofstream out("../cpp_generator/test_parser/gen/lib.h", std::ofstream::out);

    out << "#ifndef LIB_H\n";
    out << "#define LIB_H\n";

    out << "#include <regex>\n";
    out << "#include <iostream>\n";
    out << "#include <vector>\n";
    out << "#include <memory>\n";
    out << "\n\n";

    depth = 0;

    print_impl(out, "struct Parser {\n\n");
    ++depth;

    print_impl(out, "static std::string s;\n");
    print_impl(out, "static size_t pos;\n\n");

    print_impl(out, "Parser(std::string const &s);\n");

    print_structures(out);

    --depth;
    print_impl(out, "};\n\n");


    out << "#endif\n";

    out.close();

}

void print_rule_if(std::ofstream &out, Rule &rule) {

    std::vector<std::string> fst;
    add_first_by_rule(rule._children.begin(), rule._children.end(), fst);

    print_impl(out, "if (");

    bool first = true;

    for (auto &term: fst) {

        if (!first) {

            out << " || ";

        }
        first = false;

        out << term << "::match()";

    }

    out << ") {\n";

}

void print_match_functions(std::ofstream &out) {

    for (auto &pr: terminals) {

        print_impl(out, "bool Parser::" + pr.first + "::match() {\n");
        ++depth;

        print_impl(out, "for (auto &reg: regs) {\n");
        ++depth;

        print_impl(out, "std::smatch sm;\n");
        print_impl(out, "std::string tmp_str(s.begin() + pos, s.end());\n");
        print_impl(out, "if (std::regex_search(tmp_str, sm, reg)) {\n");
        ++depth;

        print_impl(out, "return true;\n");

        --depth;
        print_impl(out, "}\n");

        --depth;
        print_impl(out, "}\n");

        print_impl(out, "return false;\n");

        --depth;
        print_impl(out, "}\n");

    }

}

void print_parse_token(std::ofstream &out, std::pair<std::string, std::string> child) {

    print_impl(out, "result->children.push_back(" + child.first + "::parse(" + child.second + "));\n");

//    print_impl(out, "if (");

//    bool first = true;
//    std::set<std::string> follow;
//    get_follow(child.first, &follow);
//    for (auto &f: follow) {

//        if (!first) {

//            out << " && ";

//        }
//        first = false;

//        out << "!" << f << "::match()";

//    }

//    out << ") {\n";
//    ++depth;

//    print_impl(out, "std::cerr << \"WARNING: can not parse!!!\" << std::endl;\n");
//    print_impl(out, "exit(0);\n");

//    --depth;
//    print_impl(out, "}\n");

}

void print_parse_functions_terms(std::ofstream &out) {

    for (auto &pr: terminals) {

        print_impl(out, "Parser::" + pr.first + "* Parser::" + pr.first + "::parse() {\n");
//        print_impl(out, "std::shared_ptr<Node> Parser::")
        ++depth;

        print_impl(out, pr.first + "* result = new " + pr.first + ";\n");

        print_impl(out, "for (auto &reg: regs) {\n");
        ++depth;

        print_impl(out, "std::smatch sm;\n");
        print_impl(out, "std::string tmp_str(s.begin() + pos, s.end());\n");
        print_impl(out, "if (std::regex_search(tmp_str, sm, reg)) {\n");
        ++depth;

        print_impl(out, "size_t len = sm.length(0);\n");
        print_impl(out, "result->_value = tmp_str.substr(0, len);\n");
        print_impl(out, "pos += len;\n");
        print_impl(out, "while ((pos < s.size()) && (isspace(s[pos]))) ++pos;\n");
        print_impl(out, "return result;\n");

        --depth;
        print_impl(out, "}\n");

        --depth;
        print_impl(out, "}\n");

        print_impl(out, "return nullptr;\n");

        --depth;
        print_impl(out, "}\n");

    }

}

void print_parse_functions_vars(std::ofstream &out) {

    for (auto &pr: vars) {

        print_impl(out, "Parser::" + pr.first + "*" + " Parser::" + pr.first + "::parse(" + pr.second->_attr_s + ") {\n");
        depth++;

        print_impl(out, pr.first + "* result(new " + pr.first + ");\n");

        std::vector<std::pair<std::string, std::string>> attr_v;
        parse_attributes(pr.second->_attr_s, attr_v);
        for (auto &attr: attr_v) {

            print_impl(out, "result->" + attr.second + " = " + attr.second + ";\n");

        }

        for (auto &rule: pr.second->_cases) {

            print_rule_if(out, rule);
            ++depth;

            for (auto &child: rule._children) {

                print_parse_token(out, child);

            }
            print_impl(out, "return result;\n");

            --depth;
            print_impl(out, "}\n");

        }

        print_impl(out, "return nullptr;\n");

        depth--;
        print_impl(out, "}\n\n");

    }

}

void print_regex_definitions(std::ofstream &out)
{
    for (auto &pr: terminals)
    {
        print_impl(out, "const std::vector<std::regex> Parser::" + pr.first + "::" + "regs = {");

        bool first = true;
        for (auto &reg: pr.second->_regexps)
        {
            if (!first)
            {
                out << ", ";
            }
            first = false;
            bool literal;
            out << "std::regex(\"^" << normalize(reg, literal) << "\")";
        }
        out << "};\n";
    }
}

void print_source()
{

    std::ofstream out("../cpp_generator/test_parser/gen/lib.cpp", std::ofstream::out);

    out << "#include \"lib.h\"\n\n";

    depth = 0;

    print_impl(out, "std::string Parser::Parser::s;\n");
    print_impl(out, "size_t Parser::Parser::pos = 0;\n\n");


    print_impl(out, "Parser::Parser(std::string const &s) {\n");
    ++depth;

    print_impl(out, "Parser::s = s;\n");

    --depth;
    print_impl(out, "}\n\n");

    print_regex_definitions(out);

    print_match_functions(out);

    print_parse_functions_terms(out);

    print_parse_functions_vars(out);

    out.close();

}

void print_code()
{
    print_header();

    print_source();
}
