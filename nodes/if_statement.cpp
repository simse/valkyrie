#include <iostream>
#include "node.hpp"
#include "if_statement.hpp"

using namespace std;

void IfNode::parse()
{
    int elsePos = statementContent.find("{{ else }}");
    if (elsePos != string::npos)
    {
        hasElse = true;

        elseContent = statementContent.substr(elsePos + 10, statementContent.length() - elsePos - 23);
        statementContent = statementContent.substr(0, elsePos);
    }
}

bool IfNode::evaluateCondition() {
    // TODO: Actually evaluate condition
    return true;
}

string IfNode::render()
{
    if(evaluateCondition()) {
        Node tmp;
        tmp.parse(statementContent);
        return tmp.output;
    } else {
        Node tmp;
        tmp.parse(elseContent);
        return tmp.output;
    }
}