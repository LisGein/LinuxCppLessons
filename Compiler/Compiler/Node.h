#pragma once
#include "token_t.h"
#include <deque>

typedef std::vector<std::deque<std::string>> LinesTree;

struct Node
{
    Node();
    Node(token_t token);
    ~Node();

    void set_left_child(Node *node);
    void set_right_child(Node *node);
    token_t token() const;
    int len_indent_left_str();
    void set_indent(int indent);
    void set_line(int line);
    std::pair<std::vector<std::string>, int> calc_pos(int root_indent, std::vector<std::string> msg);

    Node *right_node() const;

private:
    token_t token_;
    Node *left_node_;
    Node *right_node_;
    int result_;
    int indent_;
    int line_;
    int pos_;
    std::string str_;

};

