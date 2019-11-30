#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "../core/context.hpp"

#pragma once

using namespace std;

class Node
{
public:
    bool selfClosing;
    string openingTag;
    string closingTag;
    string output;
    Context context;

    virtual string render() {
        return output;
    };

    void setContext(Context input);
    void parse(string input);
};