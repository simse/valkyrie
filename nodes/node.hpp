#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

#pragma once

using namespace std;

class Node
{
public:
    bool selfClosing;
    string openingTag;
    string closingTag;
    string output;
    unordered_map<string, string> context;

    virtual string render() {
        return output;
    };

    void parse(string input);
};