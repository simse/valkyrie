#include <iostream>
#include <list>
#include <unordered_map>
#include "node.hpp"

#pragma once

using namespace std;

class TextNode : public Node
{
public:
    string content;
    TextNode(string input);

    string render() override;
};