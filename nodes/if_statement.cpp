#include <iostream>
#include <regex>
#include <list>
#include <vector>
#include <unordered_map>
#include "node.hpp"
#include "if_statement.hpp"
#include "../utils/trim.hpp"

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

/* X == Y */
bool IfNode::isEqual(json fragment1, json fragment2)
{
    return fragment1 == fragment2;
}

/* X < Y */
bool IfNode::isLessThan(json fragment1, json fragment2)
{
    if (!fragment1.is_number() || !fragment2.is_number())
    {
        return false;
    }
    else
    {
        return fragment1.get<int>() < fragment2.get<int>();
    }
}

/* X > Y */
bool IfNode::isGreaterThan(json fragment1, json fragment2)
{
    if (!fragment1.is_number() || !fragment2.is_number())
    {
        return false;
    }
    else
    {
        return fragment1.get<int>() > fragment2.get<int>();
    }
}

bool IfNode::isLessThanOrEqual(json fragment1, json fragment2)
{
    return (isLessThan(fragment1, fragment2) || isEqual(fragment1, fragment2));
}

bool IfNode::isGreaterThanOrEqual(json fragment1, json fragment2)
{
    return (isGreaterThan(fragment1, fragment2) || isEqual(fragment1, fragment2));
}

vector<string> IfNode::splitFragment(string fragment, string split)
{
    auto splitPos = fragment.find(split);
    if (splitPos != string::npos)
    {
        string fragment1 = trim(fragment.substr(0, splitPos));
        string fragment2 = trim(fragment.substr(splitPos + 2, fragment.length()));
        return vector<string>{fragment1, fragment2};
    }
}

bool IfNode::evaluateFragment(string fragment)
{
    /* TODO: Clear out repetition */
    /* Check which comparison if any to do */
    if (fragment.find("==") != string::npos)
    {
        vector<string> fragments = splitFragment(fragment, "==");
        json fragment1 = context.access(fragments[0]);
        json fragment2 = context.access(fragments[1]);

        return isEqual(fragment1, fragment2);
    }
    else if (fragment.find(">=") != string::npos)
    {
        vector<string> fragments = splitFragment(fragment, ">=");
        json fragment1 = context.access(fragments[0]);
        json fragment2 = context.access(fragments[1]);

        return isGreaterThanOrEqual(fragment1, fragment2);
    }
    else if (fragment.find("<=") != string::npos)
    {
        vector<string> fragments = splitFragment(fragment, "<=");
        json fragment1 = context.access(fragments[0]);
        json fragment2 = context.access(fragments[1]);

        return isLessThanOrEqual(fragment1, fragment2);
    }
    else if (fragment.find("<") != string::npos)
    {
        vector<string> fragments = splitFragment(fragment, "<");
        json fragment1 = context.access(fragments[0]);
        json fragment2 = context.access(fragments[1]);

        return isLessThan(fragment1, fragment2);
    }
    else if (fragment.find(">") != string::npos)
    {
        vector<string> fragments = splitFragment(fragment, ">");
        json fragment1 = context.access(fragments[0]);
        json fragment2 = context.access(fragments[1]);

        return isGreaterThan(fragment1, fragment2);
    }
    else
    {
        return false;
    }
}

bool IfNode::evaluateCondition()
{
    /* Dirty way of evaluating single true/false condition */
    condition = regex_replace(condition, std::regex("if "), "");
    condition = regex_replace(condition, std::regex("&&"), "&");
    condition = regex_replace(condition, std::regex("\\|\\|"), "|");

    /* Check if condition is single group */
    if (!(condition.find('(') != string::npos ||
          condition.find(')') != string::npos ||
          condition.find('&') != string::npos ||
          condition.find('|') != string::npos))
    {
        /*cout << "simple condition" << endl;
        cout << condition << endl;
        cout << evaluateFragment(condition) << endl;*/
        return evaluateFragment(condition);
    }

    unordered_map<string, bool> flags = {
        {"CAPTURING_GROUP", false},
        {"CAPTURING_AND", false},
        {"CAPTURING_OR", false},
        {"HAS_STARTED", false}};
    string stream;
    bool currentState;
    int cursor = -1;
    int length = condition.length();

    while (cursor++ < length)
    {

    }

    return false;
}

string IfNode::render()
{
    if (evaluateCondition())
    {
        Node tmp;
        tmp.setContext(context);
        tmp.parse(statementContent);
        return tmp.output;
    }
    else if (hasElse)
    {
        Node tmp;
        tmp.setContext(context);
        tmp.parse(elseContent);
        return tmp.output;
    }
}