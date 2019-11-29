#include <iostream>
#include <list>

using namespace std;

class Node {
    public:
        bool selfClosing;
        string openingTag;
        string closingTag;
        list<Node> children;
};

int main() {
    cout << "Valkyrie 1.0" << endl;

    Node test;
    test.openingTag = "<html>";
    test.closingTag = "</html>";



    test.children.push_back(test);

    cout << test.openingTag << endl;
    cout << test.children.front().closingTag << endl;

    return 0;
}