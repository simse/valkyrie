#include <iostream>
#include "node.hpp"

#pragma once

using namespace std;

class IfNode : public Node
{
protected:
    string condition;
    string statementContent;
    string elseContent;
    bool hasElse;
public:
    IfNode(string statement, string stream)
    {
        condition = statement;
        statementContent = stream;
        parse();
    }
    bool evaluateCondition();
    string render() override;
    void parse();
};