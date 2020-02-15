#include "Lexer.hpp"

namespace Lexer
{
    Lex::Lex(char filePath[MAX_PATH])
    {
        // Create an instance of fstream
        std::fstream file;
        // Open a stream to the file
        file.open(filePath, std::ios::binary | std::ios::in);
        printf("File Path [%s]\n", filePath);
        // Check if the stream is okay to read on
        if(file.good())
        {
            // Read the file
            char* buffer;
            int fLength;
            file.seekg(0, file.end);
            fLength = file.tellg();
            file.seekg(0, file.beg);
            buffer = new char[fLength];
            file.read(buffer, fLength);
            // Convert the buffer into a string vector of each line
            std::string t;
            for (size_t i = 0; i < static_cast<size_t>(fLength); i++)
            {
                if(buffer[i] == '\n')
                {
                    this->fLines.push_back(std::pair<int, std::string>(this->fLines.size() + 1, t.data()));
                    t.clear();
                }
                else
                {
                    t += buffer[i];
                }
                
            }

            // [DEBUGGING]
            // for(std::string line : this->fLines)
            // {
            //     printf("Line [%s]\n", line.c_str());
            // }
            
        }
    }

    Lex::~Lex()
    {}

    void Lex::Parse()
    {
        std::regex r("(\\/\\/)");
        std::regex optOP("\\b(OPT)\\b");
        std::regex tdOP("\\b(TODO)\\b");

        Lex::Lexed          lexed;
        Lex::LexOptions     lOpts;

        // Using the lines created
        for(auto l : this->fLines)
        {
            // Check if the line is a comment line
            
            std::smatch sm;
            if(std::regex_search(l.second, sm, r))
            {
                std::string t;
                t = l.second.substr(l.second.find('/'), l.second.length());
                // Check what operator this comment is
                if(std::regex_search(t, sm, tdOP))
                {
                    // This Comment is of a TODO operator

                    // Get the Options Directive if there is one
                    if(std::regex_search(t, sm, optOP))
                    {
                        // There are options
                        std::string opts = t.substr(sm.position(), t.find(']', 0) - 1);
                        opts = opts.substr(4, opts.length());

                        // printf("Options: [%s]\n", opts.c_str());

                        //  Parse the options
                        if(std::regex_search(opts, sm, std::regex("\\b(n=)\\b")))
                        {
                            // Found a line option
                            // printf("Number of lines [%s]", opts.substr(sm.position() + 2, opts.find('/')).c_str());
                            // printf("STRING %s\n", opts.substr(sm.position() + 2, opts.find('/')).c_str());
                            // printf("DIG %d\n", std::stoi(opts.substr(sm.position() + 2, opts.find('/')).c_str()));
                            lOpts.numOfLines =  std::stoi(opts.substr(sm.position() + 2, opts.find('/')).c_str());
                        }

                        if(std::regex_search(opts, sm, std::regex("\\b(u=)\\b")))
                        {
                            // Found a assigment option
                            // printf("Number of lines [%s]", opts.substr(sm.position() + 2, opts.find('/')).c_str());
                            lOpts.assignment =  opts.substr(sm.position() + 2, opts.find('/')).c_str();
                        }
                    }
                    
                    // Create a Lexed Struct
                    lexed.type = "TODO";
                    lexed.lNumber = l.first;
                    if(lOpts.numOfLines != 0)
                    {
                        lexed.lOpts = lOpts;
                        std::string nc = t.substr(3, t.length());
                        lexed.comment = nc.substr(nc.find(' ', nc.find(' ', nc.find(' ') + 1) + 1) + 1, nc.length());
                    }
                    else
                    {
                        // Magic
                        lexed.lOpts.numOfLines = 0;
                        std::string nc = t.substr(3, t.length());
                        lexed.comment = nc.substr(nc.find(' ') + 1, nc.length());
                    }
                    // Get the num of code lines we need
                    std::string q;
                    int toLine = 0;
                    if(lexed.lOpts.numOfLines > 0)
                    {
                        for (size_t i = 0; i < static_cast<size_t>(lexed.lOpts.numOfLines); i++)
                        {
                            int z = i;
                            this->fLines.at(lexed.lNumber + z).second.erase(std::remove_if(this->fLines.at(lexed.lNumber + z).second.begin(), this->fLines.at(lexed.lNumber + z).second.end(), isspace), this->fLines.at(lexed.lNumber + z).second.end());
                            q += this->fLines.at(lexed.lNumber + z).second;
                            q += "\n\t\t\t";
                        }
                        toLine = lexed.lNumber;
                        toLine = toLine + lexed.lOpts.numOfLines;
                    }
                    else
                    {
                        this->fLines.at(lexed.lNumber).second.erase(std::remove_if(this->fLines.at(lexed.lNumber).second.begin(), this->fLines.at(lexed.lNumber).second.end(), isspace), this->fLines.at(lexed.lNumber).second.end());
                        q += this->fLines.at(lexed.lNumber).second;
                        toLine = lexed.lNumber + 1;
                    }
                    lexed.lNumber++;
                    
                    printf("Directive Found:\n\tLine Number [%d:%d]\n\tComment [%s]\n\tAffected Line   %s\n\n", lexed.lNumber, toLine, lexed.comment.c_str(), q.c_str());
                }
            }
        }
    }
};