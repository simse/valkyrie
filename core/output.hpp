#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

#pragma once

namespace valkyrie
{
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string UNDERLINE = "\033[4m";
const std::string INVERSE = "\033[7m";
const std::string BG_RED = "\u001b[41m";

class Output
{
protected:
    std::string currentTime()
    {
        char buffer[50];
        std::time_t t = std::time(nullptr);
        std::strftime(buffer, 50, "%d/%m/%Y %H:%M:%S", std::localtime(&t));
        return buffer;
    }

public:
    void info(std::string input)
    {
        std::cout << "[" << currentTime() << "]" << CYAN << " INFO" << RESET << "    :: " << input << std::endl;
    }

    void success(std::string input)
    {
        std::cout << "[" << currentTime() << "]" << GREEN << " SUCCESS" << RESET << " :: " << input << std::endl;
    }

    void warning(std::string input)
    {
        std::cout << "[" << currentTime() << "]" << YELLOW << " WARNING" << RESET << " :: " << input << std::endl;
    }

    void error(std::string input)
    {
        std::cout << "[" << currentTime() << "]" << RED << " ERROR" << RESET << "   :: " << input << std::endl;
    }

    void fatal(std::string input)
    {
        std::cout << "[" << currentTime() << "] " << BG_RED << "FATAL" << RESET << "   :: " << input << std::endl;
        exit(EXIT_FAILURE);
    }
};
} // namespace valkyrie