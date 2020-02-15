#include <fstream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <cctype>

// Change to work on other OS
#include <linux/limits.h>

#ifndef LEXER_LEX_H
#define LEXER_LEX_H

namespace Lexer
{
    #define MAX_PATH PATH_MAX

    class Lex 
    {
        private:
        std::vector<std::pair<int, std::string>> fLines;
        typedef struct LexOptions
        {
            int             numOfLines;
            std::string     assignment;
        } LEXOPTIONS, *PLEXOPTIONS;

        typedef struct Lexed
        {
            std::string     type;
            int             lNumber;
            LexOptions      lOpts;
            std::string     comment;
        } LEXED, *PLEXED;

        public:
        Lex(char filePath[MAX_PATH]);
        ~Lex();

        void Parse();
    };
};

#endif