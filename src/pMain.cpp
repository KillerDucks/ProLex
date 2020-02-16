#include "Lexer/Lexer.hpp"
#include "Lexer/MD.hpp"

int main(int argc, char** argv)
{
    printf("Lexing  Lexer.cpp\n");
    Lexer::Lex  l((char*)"./test/test.cpp");
    l.Parse();
    Lexer::MD md(l._vLxd);
    return 1;
}