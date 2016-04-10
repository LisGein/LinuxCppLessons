#include "lexer_t.h"
#include <boost/algorithm/string.hpp>


lexer_t::lexer_t(const std::string &str)
:next_token_(0)
{
    std::vector<std::string> tokens;
    boost::split(tokens, str, boost::is_any_of(" "));
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i] == ";")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_END_LINE));

        else if (tokens[i] == "{")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_BEGIN_BLOCK));

        else if (tokens[i] == "}")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_END_BLOCK));

        else if (tokens[i] == "+")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_PLUS));

        else if (tokens[i] == "-")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_MINUS));

        else if (tokens[i] == "*")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_MULTIPLY));

        else if (tokens[i] == "(")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_LP));

        else if (tokens[i] == ")")
            tokens_.push_back(token_t(TOKEN_TYPE::TT_RP));

        else if (std::isdigit(tokens[i][0]))
        {
            int num = atoi(tokens[i].c_str());
            token_t token(TOKEN_TYPE::TT_NUMBER);
            token.value_ = num;
            tokens_.push_back(token);
        }

    }
}

bool lexer_t::has_next()
{
    return next_token_ < tokens_.size();
}

token_t const lexer_t::next()
{
    try
    {
        if (!has_next())
        {
            throw next_token_;
        }
        int next_token = next_token_;
        return tokens_[next_token];
    }
    catch(int i)
    {
        return token_t();
    }
}

bool lexer_t::increment_next()
{
    ++next_token_;
    return has_next();
}

void lexer_t::decrement_next()
{
    --next_token_;
}
