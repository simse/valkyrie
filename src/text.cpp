#include <iostream>
#include <list>
#include <unordered_map>

#include "../include/text.hpp"

TextNode::TextNode(string input) {
    content = input;
}

string TextNode::render() {
    return content;
}