#include <iostream>
#include "node.hpp"

#pragma once

using namespace std;

class ShowNode : public Node
{
protected:
    string content;

public:
    ShowNode(string input)
    {
        content = input;
    }
    string render() override
    {
        return content;
    }
};