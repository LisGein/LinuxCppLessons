#pragma once

#include <string>
#include "token_t.h"


struct lexer_t
{
    lexer_t(std::string &str);
    bool has_next();
    token_t const &next();

private:
    std::vector<token_t> tokens_;
    int next_token_;
};


