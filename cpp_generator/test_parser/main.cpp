#include "gen/lib.h"

#include <iostream>
#include <regex>
#include <string>

std::string TAB = "  ";

void print_tabs(std::ostream &out, int depth)
{
    for ( int i = 0; i < depth; ++i )
    {
        out << TAB;
    }
}

void visitor(std::ostream &out, Parser::Node *node)
{
    if (node->is_terminal())
    {
        Parser::TerminalNode* term = reinterpret_cast<Parser::TerminalNode*>(node);
        switch (term->get_structure_name())
        {
        default:
            out << term->_value;
            break;
        }
    } else
    {
        Parser::VariableNode* var = reinterpret_cast<Parser::VariableNode*>(node);
        switch (var->get_structure_name())
        {
        case Parser::NodeType::e_start:
            out << "begin\n";
            visitor(out, var->children[0]);
            out << "end\n";
            break;

        case Parser::NodeType::e_void_expr:
            print_tabs(out, reinterpret_cast<Parser::void_expr*>(var)->depth);

            out << "writeln(";
            visitor(out, var->children[1]);
            out << ");\n";
            break;

        case Parser::NodeType::e_if_expr:
            print_tabs(out, reinterpret_cast<Parser::if_expr*>(var)->depth);

            out << "if ";
            visitor(out, var->children[1]); // cond_expr
            out << " then begin\n";

            visitor(out, var->children[3]);

            print_tabs(out, reinterpret_cast<Parser::if_expr*>(var)->depth);
            out << "end;\n";
            break;
        case Parser::NodeType::e_int_expr:

            if ((var->children[0]->get_structure_name() != Parser::NodeType::e_digit)
              && (var->children[0]->get_structure_name() != Parser::NodeType::e_unaryDigitOp))
            {
                out << "(";
                visitor(out, var->children[1]);
                out << ") ";
                visitor(out, var->children[0]);
                out << " (";
                visitor(out, var->children[2]);
                out << ")";
                break;
            }
            goto label;

        case Parser::NodeType::e_cond_expr:

            if (var->children[0]->get_structure_name() != Parser::NodeType::e_unaryBoolOp)
            {
                out << "(";
                visitor(out, var->children[1]);
                out << ") ";
                visitor(out, var->children[0]);
                out << " (";
                visitor(out, var->children[2]);
                out << ")";
                break;
            }
            goto label;

        default:
label:
            bool first = true;
            for (auto &child: var->children)
            {
                if (!first) out << " ";
                first = false;
                visitor(out, child);
            }
            break;
        }
    }
}

int main()
{
    Parser parser("if < + 5 3 * 6 3 print 1235");
    auto root = Parser::start::parse();
    visitor(std::cout, root);
    return 0;
}
