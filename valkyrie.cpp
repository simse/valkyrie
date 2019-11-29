#include <iostream>
#include <fstream>

#include "nodes/node.hpp"

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
        }
        myfile.close();
    }

    Node test;
    test.parse(all);

    /*cout << test.openingTag << endl;
    cout << test.children.front().closingTag << endl;*/

    /*cout << test.render() << endl;*/
    cout << test.output << endl;

    return 0;
}