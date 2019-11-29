#include <iostream>
#include <list>
#include <unordered_map>


using namespace std;

class TextNode: public Node {
    protected:
        string content;
    public:
        string render() {
            return content;
        }
};