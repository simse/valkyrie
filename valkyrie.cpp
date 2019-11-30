#include <iostream>
#include <fstream>

#include "libraries/json.hpp"
#include "nodes/node.hpp"
#include "core/context.hpp"

using namespace std;

int main()
{
    cout << "Valkyrie 1.0" << endl;

    string all;
    string line;
    ifstream myfile;
    myfile.open("index.vhtml");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
            all += line;
            all += '\n';
        }
        myfile.close();
    }

    Context context;
    context.loadFile("context.json");
    /*context.access("site.title");*/

    Node test;
    test.setContext(context);
    test.parse(all);

    /*cout << test.openingTag << endl;
    cout << test.children.front().closingTag << endl;*/

    /*cout << test.render() << endl;*/
    cout << "\n\n\nOUTPUT:\n";
    cout << test.output << endl;

    return 0;
}