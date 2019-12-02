#include <iostream>
#include <regex>
#include <list>
#include <vector>
#include <unordered_map>
#include "../include/nodes/node.hpp"
#include "../include/nodes/if_statement.hpp"
#include "../include/utils/trim.hpp"

using namespace std;

void IfNode::parse()
{
    unsigned int elsePos = statementContent.find("{{ else }}");
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
    } else {
        return vector<string>{};
    }
}

bool IfNode::evaluateFragment(string fragment)
{
    /* Evaluate true and false */
    if (fragment == "true" || fragment == "!false")
    {
        return true;
    }
    else if (fragment == "false" || fragment == "!true")
    {
        return false;
    }

    /* TODO: Clear out repetition */
    /* Check which comparison if any to do */
    if (fragment.find("==") != string::npos)
    {
        vector<string> fragments = splitFragment(fragment, "==");
        json fragment1;
        json fragment2;
        if (fragments[0] == "true" || fragments[0] == "!false")
        {
            fragment1 = true;
        }
        else
        {
            fragment1 = context.access(fragments[0]);
        }

        if (fragments[0] == "false" || fragments[0] == "!true")
        {
            fragment2 = false;
        }
        else
        {
            fragment2 = context.access(fragments[1]);
        }

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
        if (fragment.find("!") != string::npos)
        {
            fragment = regex_replace(fragment, std::regex("!"), "");

            return !(bool)context.access(fragment);
        }
        else if (!context.access(fragment).is_boolean())
        {
            return false;
        }
        else
        {
            return (bool)context.access(fragment);
        }
    }
}

bool IfNode::evaluateCondition(string input)
{
    /* Dirty way of evaluating single true/false input */
    input = regex_replace(input, std::regex("if "), "");
    input = regex_replace(input, std::regex("&&"), "&");
    input = regex_replace(input, std::regex("\\|\\|"), "|");

    /* Remove all spaces */
    input = regex_replace(input, std::regex(" "), "");

    /* Check if input based on equality */
    if (!(input.find('(') != string::npos ||
          input.find(')') != string::npos ||
          input.find('&') != string::npos ||
          input.find('|') != string::npos))
    {
        /*cout << "simple input" << endl;
        cout << input << endl;
        cout << evaluateFragment(input) << endl;*/
        return evaluateFragment(input);
    }

    /* Evaluate groups since they have precedent */
    while (input.find('(') != string::npos &&
           input.find(')') != string::npos)
    {
        unsigned int cursor = 0;
        int depth = 0;
        int startingPos = 0;
        int endPos = 0;
        string stream;

        /*cout << cursor << endl;
        cout << input.length() << endl;*/

        /* Find a group */
        while (cursor < input.length())
        {
            char current_char = input[cursor];
            cursor++;

            if (current_char == '(')
            {
                if (depth == 0)
                {
                    startingPos = cursor - 1;
                }

                depth++;
            }
            else if (current_char == ')')
            {
                depth--;

                if (depth == 0)
                {
                    endPos = cursor;
                    break;
                }
            }
        }

        string cleanGroup = input.substr(startingPos + 1, endPos - startingPos - 2);
        input = input.replace(startingPos, endPos, evaluateCondition(cleanGroup) ? "true" : "false");
    }

    /* Evaluate AND statements */
    auto andPos = input.find('&');
    if (andPos != string::npos)
    {
        string fragment1 = input.substr(0, andPos);
        string fragment2 = input.substr(andPos + 1, input.length());

        return evaluateCondition(fragment1) && evaluateCondition(fragment2);
    }

    /* Evaluate OR statements */
    auto orPos = input.find('|');
    if (orPos != string::npos)
    {
        string fragment1 = input.substr(0, orPos);
        string fragment2 = input.substr(orPos + 1, input.length());

        return evaluateCondition(fragment1) || evaluateCondition(fragment2);
    }

    /* Handle the scenario where bracket recursion reduced the expression to single statement */
    return (input == "true") ? true : false;
}

string IfNode::render()
{
    if (evaluateCondition(condition))
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
    } else {
        return "";
    }
}