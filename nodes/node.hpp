#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Node {
    public:
        bool selfClosing;
        string openingTag;
        string closingTag;
        list<Node> children;
        unordered_map<string,string> context;

        string render() {
            return "nathing";
        }
};