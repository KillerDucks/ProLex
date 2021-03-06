#include "Directory.hpp"

namespace WebX
{
    Directory::Directory(int d)
    {
    }

    Directory::Directory(char* _baseDirectory, std::regex _fileExtensions)
    {
        if(strlen(_baseDirectory) != 0)
        {
            // [TODO] Assume a valid path has been passed, possible change?
            this->basePath = _baseDirectory;
            this->fileExts = _fileExtensions;
        }
    }

    Directory::~Directory()
    {}

    void Directory::ScanDir()
    {
        for(auto file : fs::recursive_directory_iterator(this->basePath))
        {
            printf("File found [%s]\n", file.path().c_str());
        }
    }

    vector<string> Directory::ScanDir(std::regex searchCriteria)
    {
        // [TODO] [OPT n=3/] Sample
        std::smatch sm;
        vector<string> files;
        for(auto file : fs::recursive_directory_iterator(this->basePath))
        {
            // Convert into a std::string
            string fPath(file.path());
            // Run the file against the regex
            if(std::regex_search(fPath, sm, searchCriteria))
            {
                // This file is a Web file
                files.push_back(file.path());
                // [TODO] Use printff();
                printf("File found [%s]\n", file.path().c_str());
            }
        }

        return files;
    }
    
    void Directory::GetWebFiles()
    {
        std::smatch sm;

        for(auto file : fs::recursive_directory_iterator(this->basePath))
        {
            // Convert into a std::string
            string fPath(file.path());
            // Run the file against the regex
            if(std::regex_search(fPath, sm, this->fileExts))
            {
                // This file is a Web file
                // [TODO] [OPT n=2/] Need to reflect the MINE type back to the header generator
                this->fVector.push_back(file.path());
                printf("File found [%s]\n", file.path().c_str());
            }
        }
    }
}