#include <iostream>
#include <fstream>
#include "lexer_t.h"

int main()
{
    std::string str = "55 * 4";

    lexer_t *lexer = new lexer_t(str);
    while (lexer->has_next())
    {
        std::cout << lexer->next().type << "\n";
    }


    return 0;
}

/*
struct parser_t
{
   parser_t(lexer_t const &lexer);

   void parse();
};
 */
