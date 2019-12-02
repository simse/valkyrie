#include <iostream>
#include <regex>
#include "../include/context.hpp"
#include "../include/node.hpp"
#include "../include/for_statement.hpp"

using namespace std;

string ForNode::render()
{
    /* Parse iterator string */
    regex rgx("for (.*) in (.*)");
    smatch matches;
    regex_search(iterator, matches, rgx);

    /* Throw error if incorrect format */
    if (matches.size() != 3)
    {
        throw invalid_argument("for statement has wrong format");
    }

    json loop = context.access(matches[2]);

    for (auto &el : loop.items())
    {
        Context childContext;
        json childContextJson;
        childContextJson[matches[1]] = el.value();
        childContext.set(childContextJson);

        Node child;
        child.setContext(childContext);
        child.parse(content);

        output += child.output;
    }

    return output;
}