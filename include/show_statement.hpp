#include <iostream>
#include "node.hpp"

#pragma once

class ShowNode : public Node
{
protected:
    std::string input;

public:
    ShowNode(std::string input)
    {
        input = input;
    }
    std::string render() override;
};