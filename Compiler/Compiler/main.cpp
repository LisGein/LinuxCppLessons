#include <iostream>
#include <fstream>
#include "lexer_t.h"

int main()
{
    std::string str;
    std::fstream fin("test_program.txt");
    std::string line;
    while (fin >> line)
        str += line + " ";
    fin.close();

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
