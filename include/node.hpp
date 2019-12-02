#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "context.hpp"
#include "output.hpp"

#pragma once


class Node
{
public:
    bool selfClosing;
    std::string openingTag;
    std::string closingTag;
    std::string output;
    Context context;
    valkyrie::Output console;

    virtual string render() {
        return output;
    };

    void setContext(Context input);
    void parse(string input);
};