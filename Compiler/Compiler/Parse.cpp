#include "Parse.h"
#include "Node.h"
#include "lexer_t.h"


Parse::Parse(lexer_t *lexer)
        : lexer_(lexer)
{
}

Parse::~Parse()
{

}

Block Parse::parse_blocks()
{
    Block blocks;
    while (lexer_->has_next())
    {
        lexer_->increment_next();
        Statement lines = parse_stmt();
        blocks.push_back(lines);
        lexer_->increment_next();
    }
    return blocks;
}

Statement Parse::parse_stmt()
{
    Statement lines;
    Node *node = 0;
    while (lexer_->has_next())
    {
        token_t next_token = lexer_->next();
        switch (next_token.type)
        {
            case TOKEN_TYPE::TT_END_BLOCK:
                return lines;
            case TOKEN_TYPE::TT_END_LINE:
                lines.push_back(node);
                lexer_->increment_next();
                node = 0;
                break;
            default:
                node = parse_expr(node);
                break;
        }
    }

    return lines;
}

Node *Parse::parse_expr(Node *node, bool loop)
{
    do
    {
        token_t next_token = lexer_->next();
        Node *next_node = new Node(next_token);
        switch (next_token.type)
        {
            case TOKEN_TYPE::TT_END_BLOCK:
                return node;
            case TOKEN_TYPE::TT_END_LINE:
                return node;
            case TOKEN_TYPE::TT_LP:
                node = expr(node);
                lexer_->increment_next();
                break;
            case TOKEN_TYPE::TT_RP:
                return node;
            case TOKEN_TYPE::TT_MULTIPLY:
                node = parse_term(node, next_node);
                break;
            case TOKEN_TYPE::TT_PLUS:
                node = parse_rest(node, next_node);
                break;
            case TOKEN_TYPE::TT_MINUS:
                node = parse_rest(node, next_node);
                break;
            default:
                if (node == 0)
                    node = next_node;
                break;
        }
        lexer_->increment_next();
    } while (loop && lexer_->has_next());
    return node;
}

Node *Parse::parse_rest(Node *left, Node *root)
{
    root->set_left_child(left);
    lexer_->increment_next();
    Node *right = 0;
    if (lexer_->next().type == TOKEN_TYPE::TT_LP)
        right = expr();
    else
        right = new Node(lexer_->next());

    root->set_right_child(right);

    return root;

}

Node *Parse::parse_term(Node *left, Node *root)
{

    if (left->token().type == TOKEN_TYPE::TT_NUMBER || left->token().type == TOKEN_TYPE::TT_MULTIPLY)
    {
        root->set_left_child(left);
        lexer_->increment_next();
        Node *right = new Node(lexer_->next());
        root->set_right_child(right);
        return root;
    }

    lexer_->increment_next();
    Node *right = 0;
    if (lexer_->next().type == TOKEN_TYPE::TT_LP)
        right = expr();
    else
        right = new Node(lexer_->next());

    root->set_right_child(right);
    root->set_left_child(left->right_node());

    left->set_right_child(root);
    return left;
}

Node *Parse::expr(Node *node)
{
    lexer_->increment_next();
    Node *next_node = 0;
    next_node = parse_expr(next_node, true);
    if (node)
        node->set_right_child(next_node);
    else
        node = next_node;

    return node;
}

