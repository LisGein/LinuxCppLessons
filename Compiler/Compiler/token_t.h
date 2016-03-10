#pragma once
#include <boost/optional.hpp>
#include <fstream>
#include <boost/lexical_cast.hpp>
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
    token_t()
            : type(TT_INVALID)
    {

    }
    token_t(TOKEN_TYPE token_type)
            : type(token_type)
    {
    }
    token_t(TOKEN_TYPE token_type, boost::optional<int> v)
            : type(token_type)
            , value_(v)
    {
    }
    bool operator==(const token_t& right) const {
        return (type == right.type &&  value_ == right.value_);
    }

    boost::optional<int> value_;
//private:
    TOKEN_TYPE type;
};
inline  std::ostream& operator<<(std::ostream& stream, token_t const& line)
{
    std::string str = "token_t{ " + boost::lexical_cast<std::string>(line.type);

    if (line.value_)
        str += ", " + boost::lexical_cast<std::string>(*(line.value_));
    str +=" }";
    return stream << str;
}
