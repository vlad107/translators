#ifndef LIB_H
#define LIB_H
#include <regex>
#include <iostream>
#include <vector>
#include <memory>


struct Parser {

    static std::string s;
    static size_t pos;

    Parser(std::string const &s);

    enum NodeType {e_ZERO, e_e, e_e1, e_start};
    struct Node
    {
        virtual bool is_terminal() = 0;
        virtual NodeType get_structure_name() = 0;
    };
    struct VariableNode : Node
    {
        virtual bool is_terminal() { return false; }
        std::vector<Node*> children;
    };
    struct TerminalNode : Node
    {
        virtual bool is_terminal() { return true; }
        std::string _value;
    };
    struct ZERO : TerminalNode {
        static Parser::ZERO* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_ZERO; }
        static const std::vector<std::regex> regs;
    };

    struct e : VariableNode {
        static Parser::e* parse();

        virtual NodeType get_structure_name() { return NodeType::e_e; }
    };

    struct e1 : VariableNode {
        static Parser::e1* parse();

        virtual NodeType get_structure_name() { return NodeType::e_e1; }
    };

    struct start : VariableNode {
        static Parser::start* parse();

        virtual NodeType get_structure_name() { return NodeType::e_start; }
    };


};

#endif
