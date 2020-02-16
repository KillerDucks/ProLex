#include <fstream>
#include <string>
#include <vector>

#include "Lexer.hpp"

#ifndef LEXER_MD_H
#define LEXER_MD_H

namespace Lexer
{
    #define MAX_PATH PATH_MAX

    class MD 
    {
        private:
            // Data
            std::vector<Lex::Lexed> _vLxd;
            std::vector<std::vector<std::string>> _conv;
        public:
        MD(std::vector<Lex::Lexed> lxd);
        ~MD();

        void Convert();

        void CreateMDHeader();

        void WriteFile();
    };
};

#endif