#pragma once

#include <string>
#include <map>
#include "token_t.h"
#include "Node.h"


struct lexer_t
{
    lexer_t(const std::string &str);
    bool has_next();
    token_t const next();
    bool increment_next();
    void decrement_next();

private:
    std::vector<token_t> tokens_;
    int next_token_;
};


