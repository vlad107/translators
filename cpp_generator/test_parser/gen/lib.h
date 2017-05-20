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

    enum NodeType {e_And, e_CLOSE_BRACKET, e_Digit, e_Div, e_Eq, e_Gr, e_GrOrEq, e_If, e_Le, e_LeOrEq, e_Minus, e_Mult, e_Not, e_OPEN_BRACKET, e_Or, e_Plus, e_Print, e_WS, e_Xor, e_binaryBoolOp, e_binaryDigitOp, e_cmpDigits, e_cond_expr, e_digit, e_expr, e_if_expr, e_int_expr, e_start, e_unaryBoolOp, e_unaryDigitOp, e_void_expr};
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
    struct And : TerminalNode {
        static Parser::And* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_And; }
        static const std::vector<std::regex> regs;
    };

    struct CLOSE_BRACKET : TerminalNode {
        static Parser::CLOSE_BRACKET* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_CLOSE_BRACKET; }
        static const std::vector<std::regex> regs;
    };

    struct Digit : TerminalNode {
        static Parser::Digit* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Digit; }
        static const std::vector<std::regex> regs;
    };

    struct Div : TerminalNode {
        static Parser::Div* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Div; }
        static const std::vector<std::regex> regs;
    };

    struct Eq : TerminalNode {
        static Parser::Eq* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Eq; }
        static const std::vector<std::regex> regs;
    };

    struct Gr : TerminalNode {
        static Parser::Gr* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Gr; }
        static const std::vector<std::regex> regs;
    };

    struct GrOrEq : TerminalNode {
        static Parser::GrOrEq* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_GrOrEq; }
        static const std::vector<std::regex> regs;
    };

    struct If : TerminalNode {
        static Parser::If* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_If; }
        static const std::vector<std::regex> regs;
    };

    struct Le : TerminalNode {
        static Parser::Le* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Le; }
        static const std::vector<std::regex> regs;
    };

    struct LeOrEq : TerminalNode {
        static Parser::LeOrEq* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_LeOrEq; }
        static const std::vector<std::regex> regs;
    };

    struct Minus : TerminalNode {
        static Parser::Minus* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Minus; }
        static const std::vector<std::regex> regs;
    };

    struct Mult : TerminalNode {
        static Parser::Mult* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Mult; }
        static const std::vector<std::regex> regs;
    };

    struct Not : TerminalNode {
        static Parser::Not* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Not; }
        static const std::vector<std::regex> regs;
    };

    struct OPEN_BRACKET : TerminalNode {
        static Parser::OPEN_BRACKET* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_OPEN_BRACKET; }
        static const std::vector<std::regex> regs;
    };

    struct Or : TerminalNode {
        static Parser::Or* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Or; }
        static const std::vector<std::regex> regs;
    };

    struct Plus : TerminalNode {
        static Parser::Plus* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Plus; }
        static const std::vector<std::regex> regs;
    };

    struct Print : TerminalNode {
        static Parser::Print* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Print; }
        static const std::vector<std::regex> regs;
    };

    struct WS : TerminalNode {
        static Parser::WS* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_WS; }
        static const std::vector<std::regex> regs;
    };

    struct Xor : TerminalNode {
        static Parser::Xor* parse();
        static bool match();

        virtual NodeType get_structure_name() { return NodeType::e_Xor; }
        static const std::vector<std::regex> regs;
    };

    struct binaryBoolOp : VariableNode {
        static Parser::binaryBoolOp* parse();

        virtual NodeType get_structure_name() { return NodeType::e_binaryBoolOp; }
    };

    struct binaryDigitOp : VariableNode {
        static Parser::binaryDigitOp* parse();

        virtual NodeType get_structure_name() { return NodeType::e_binaryDigitOp; }
    };

    struct cmpDigits : VariableNode {
        static Parser::cmpDigits* parse();

        virtual NodeType get_structure_name() { return NodeType::e_cmpDigits; }
    };

    struct cond_expr : VariableNode {
        static Parser::cond_expr* parse();

        virtual NodeType get_structure_name() { return NodeType::e_cond_expr; }
    };

    struct digit : VariableNode {
        static Parser::digit* parse();

        virtual NodeType get_structure_name() { return NodeType::e_digit; }
    };

    struct expr : VariableNode {
        static Parser::expr* parse(int depth);

        virtual NodeType get_structure_name() { return NodeType::e_expr; }
        int depth;
    };

    struct if_expr : VariableNode {
        static Parser::if_expr* parse(int depth);

        virtual NodeType get_structure_name() { return NodeType::e_if_expr; }
        int depth;
    };

    struct int_expr : VariableNode {
        static Parser::int_expr* parse();

        virtual NodeType get_structure_name() { return NodeType::e_int_expr; }
    };

    struct start : VariableNode {
        static Parser::start* parse();

        virtual NodeType get_structure_name() { return NodeType::e_start; }
    };

    struct unaryBoolOp : VariableNode {
        static Parser::unaryBoolOp* parse();

        virtual NodeType get_structure_name() { return NodeType::e_unaryBoolOp; }
    };

    struct unaryDigitOp : VariableNode {
        static Parser::unaryDigitOp* parse();

        virtual NodeType get_structure_name() { return NodeType::e_unaryDigitOp; }
    };

    struct void_expr : VariableNode {
        static Parser::void_expr* parse(int depth);

        virtual NodeType get_structure_name() { return NodeType::e_void_expr; }
        int depth;
    };


};

#endif
