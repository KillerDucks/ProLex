#include "MD.hpp"

namespace Lexer
{
    MD::MD(std::vector<Lex::Lexed> vlxd)
    {
        // Store this locally
        this->_vLxd = vlxd;
        this->CreateMDHeader();
        this->Convert();
        this->WriteFile();
    }

    MD::~MD()
    {}

    void MD::Convert()
    {
        using std::string;
        std::vector<string> section;
        // Convert
        for(auto com : this->_vLxd)
        {
            string t;
            // File Name + Link to line/s
            t += "### [";
            t += com.fileName;
            t += "[";
            t += std::to_string(com.lNumber);
            t += ":";
            if(com.lOpts.numOfLines > 1)
            {
                t += std::to_string(com.lNumber + com.lOpts.numOfLines);
            }
            else
            {
               t += std::to_string(com.lNumber);
            }
            t += "]](";
            t += com.fileName;
            t += "#L";
            t += std::to_string(com.lNumber);
            if(com.lOpts.numOfLines > 1)
            {
                t += "-L";
                t += std::to_string(com.lNumber + com.lOpts.numOfLines);
            }
            t += ")\n";
            // Push into Vector
            section.push_back(t);
            // Clear the string
            t.clear();
            // Comment
            t += com.comment;
            t += "\n";
            section.push_back(t);
            // Clear the string
            t.clear();
            // Code block
            t += "```cpp\n";
            for(auto l : com.affectedLines)
            {
                t += l.second;
                t += "\n";
            }
            t += "```\n";
            // Push into Vector
            section.push_back(t);
            // Clear the string
            t.clear();
        }
        this->_conv.push_back(section);
    }

    void MD::CreateMDHeader()
    {
        using std::string;
        using std::vector;
        vector<string> x;
        // Static header because why not
        string t = "# ProLex Analytics\n\n";
        x.push_back(t);
        // RAM it in
        this->_conv.push_back(x);
    }

    void MD::WriteFile()
    {
        // HARD CODE INCOMMING
        std::fstream fileStream;
        fileStream.open("./todo.md", std::ios::binary | std::ios::out | std::ios::app);
        // Check if the stream is good
        if(fileStream.good())
        {
            // Fuck it just write the file
            for(auto x : this->_conv)
            {
                for(auto y : x)
                {
                    fileStream.write(y.c_str(), y.length());
                }
            }

            fileStream.close();
        }
    }
};