#include <iostream>
#include <list>

#include "nodes/node.hpp"

using namespace std;


int main() {
    cout << "Valkyrie 1.0" << endl;

    Node test;
    test.openingTag = "<html>";
    test.closingTag = "</html>";



    test.children.push_back(test);

    cout << test.openingTag << endl;
    cout << test.children.front().closingTag << endl;

    cout << test.render() << endl;

    return 0;
}