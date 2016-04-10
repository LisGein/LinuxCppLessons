#include "Node.h"


Node::Node()
        : token_(token_t())
        , left_node_(0)
        , right_node_(0)
        , result_(0)
        , indent_(0)
        , line_(0)
        , pos_(0)
{
}

Node::Node(token_t token)
        : token_(token)
        , left_node_(0)
        , right_node_(0)
        , result_(0)
        , indent_(0)
        , line_(0)
        , pos_(0)
{
    if (token_.value_)
        str_ = boost::lexical_cast<std::string>(*(token_.value_));
    else if (token_.type == TOKEN_TYPE::TT_PLUS)
        str_ =   "+" ;
    else if (token_.type == TOKEN_TYPE::TT_MINUS)
        str_ =   "-" ;
    else if (token_.type == TOKEN_TYPE::TT_MULTIPLY)
        str_ =   "*" ;
}

Node::~Node()
{

}

void Node::set_left_child(Node *node)
{
    left_node_ = node;
}

void Node::set_right_child(Node *node)
{
    right_node_ = node;
}

token_t Node::token() const
{
    return token_;
}

int Node::len_indent_left_str()
{
    int len = (left_node_ == 0) ? 0 : 2 + left_node_->len_indent_left_str();

    return len;
}

void Node::set_indent(int indent)
{
    indent_ = indent + 2;
    if (right_node_ != 0)
        right_node_->set_indent(indent_);
}

std::pair<std::vector<std::string>, int> Node::calc_pos(int root_indent, std::vector<std::string> msg)
{
    int l_pos = 0;
    if (left_node_ != 0)
    {
        left_node_->set_line(line_ + 1);
        std::pair<std::vector<std::string>, int> l = left_node_->calc_pos(root_indent + 1, msg);
        msg = l.first;
        l_pos = l.second;
    }

    pos_ = (l_pos != 0) ? l_pos : root_indent;


    int r_pos = 0;
    if (right_node_ != 0)
    {
        right_node_->set_line(line_ + 1);
        std::pair<std::vector<std::string>, int> r = right_node_->calc_pos(pos_ + 2, msg);
        msg = r.first;
        r_pos = r.second;
    }

    if (r_pos != 0 && l_pos != 0)
        pos_ += ((r_pos - l_pos) / 2);


    while (msg.size() <= line_)
        msg.push_back("");


    for (int i = msg[line_].size(); i < pos_; ++i)
        msg[line_] += ".";
    msg[line_] += str_;

    return std::pair<std::vector<std::string>, int>(msg, pos_);
}

void Node::set_line(int line)
{
    line_ = line;
}

Node *Node::right_node() const
{
    return right_node_;
}

