#include <iostream>
#include <list>



#include "nodes/node.hpp"
#include "nodes/text.hpp"

using namespace std;


int main()
{
    cout << "Valkyrie 1.0" << endl;

    Node test;
    test.parse("<p>{{ test }}</p>");

    /*cout << test.openingTag << endl;
    cout << test.children.front().closingTag << endl;*/

    cout << test.render() << endl;


    return 0;
}