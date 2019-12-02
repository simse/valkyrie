#include <iostream>
#include <list>
#include <unordered_map>

#include "../include/nodes/text.hpp"

TextNode::TextNode(string input) {
    content = input;
}

string TextNode::render() {
    return content;
}