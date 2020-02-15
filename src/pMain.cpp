#include "Lexer/Lexer.hpp"

int main(int argc, char** argv)
{
    printf("Lexing  Lexer.cpp\n");
    Lexer::Lex  l((char*)"./test/test.cpp");
    l.Parse();
    return 1;
}