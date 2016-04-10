#pragma once
#include <vector>

struct Node;
struct lexer_t;

typedef std::vector<Node *> Statement;
typedef std::vector<Statement> Block;

struct Parse
{
    Parse(lexer_t *lexer);
    ~Parse();
    Block parse_blocks();
    Statement parse_stmt();
    Node *parse_expr(Node *node = 0, bool loop = false);
    Node *parse_rest(Node *left, Node *root);
    Node *parse_term(Node *left, Node *root);
    Node *expr(Node *node = 0);


private:
    lexer_t *lexer_;
};

