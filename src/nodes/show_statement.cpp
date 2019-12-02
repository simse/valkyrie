#include <iostream>
#include "../include/nodes/node.hpp"
#include "../include/nodes/show_statement.hpp"

string ShowNode::render() {
    return context.access(input);
}