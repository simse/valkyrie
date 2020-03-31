#include <string>

#pragma once

class Build {
    private:
    std::string _path;

    public:
        void setPath(std::string path);
        bool verifyPath();
        void build(std::string outputPath);
};
