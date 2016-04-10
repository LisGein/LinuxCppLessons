#include <iostream>
#include <fstream>
#include "lexer_t.h"
#include "Parse.h"


int main()
{


    std::string str;
    std::fstream fin("test_program.txt");
    std::string line;
    while (fin >> line)
        str += line + " ";
    fin.close();
    if (str.empty())
        str = " { "
                " 1 + 2 * ( 3 + 4 ) + 5 ; "
                " 4 + 5 ; "
                " } "
                " { "
                " 4 * 5 ; "
                " } ";

    lexer_t *lexer = new lexer_t(str);


    Parse *parser = new Parse(lexer);


    Block blocks = parser->parse_blocks();

    for (auto i = blocks.begin(); i != blocks.end(); ++i)
    {
        std::cout << "begin block " << std::endl;
        for (auto j = i->begin(); j != i->end(); ++j) {
            std::vector<std::string> v = (*j)->calc_pos(0, std::vector<std::string>()).first;
            for (int idx = 0; idx < v.size(); ++idx)
                std::cout << v[idx] << std::endl;
            std::cout << "end line " << std::endl;
        }
        std::cout << "end block " << std::endl;
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
