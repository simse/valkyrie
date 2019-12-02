#include <iostream>
#include "../include/node.hpp"
#include "../include/show_statement.hpp"

string ShowNode::render() {
    return context.access(input);
}