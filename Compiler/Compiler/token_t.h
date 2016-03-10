#pragma once
#include <boost/optional.hpp>


enum TOKEN_TYPE
{
    TT_INVALID,
    TT_NUMBER,
    TT_PLUS,
    TT_MINUS,
    TT_MULTIPLY,
    TT_LP,
    TT_RP
};

struct token_t
{
    token_t(TOKEN_TYPE token_type)
    : type(token_type)
    {
    }
    boost::optional<int> value;
//private:
    TOKEN_TYPE type;
};

