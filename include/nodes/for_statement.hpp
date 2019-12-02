#include <iostream>
#include "node.hpp"

#pragma once

using namespace std;

class ForNode : public Node
{
    protected:
        string iterator;
        string content;
        string output;
public:
    ForNode(string statement, string stream)
    {
        iterator = statement;
        content = stream;
    }
    string render() override;
};