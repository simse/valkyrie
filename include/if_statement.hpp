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
    bool isEqual(json fragment1, json fragment2);
    bool isLessThan(json fragment1, json fragment2);
    bool isGreaterThan(json fragment1, json fragment2);
    bool isLessThanOrEqual(json fragment1, json fragment2);
    bool isGreaterThanOrEqual(json fragment1, json fragment2);
    bool evaluateFragment(string fragment);
    vector<string> splitFragment(string fragment, string split);
public:
    IfNode(string statement, string stream)
    {
        condition = statement;
        statementContent = stream;
        parse();
    }
    bool evaluateCondition(string input);
    string render() override;
    void parse();
};