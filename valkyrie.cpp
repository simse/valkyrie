/* valkyrie.cpp

 * Entry-point to the Valkyrie static site generator. This
 * is where all the magic of delegation happens.
 * 
 * Simon Sorensen (hello@simse.io)
 * 01/12/19
 */

#include <iostream>
#include <fstream>

#include "core/output.hpp"
#include "core/constants.hpp"
#include "includes/json.hpp"
#include "nodes/node.hpp"
#include "core/context.hpp"

using namespace std;

int main(int argc, char **argv)
{
    /* Prepare to ouput to console */
    valkyrie::Output output;
    output.info("Loading Valkyrie " + valkyrie::VERSION);

    output.info("Loading input template...");
    string all;
    string line;
    ifstream myfile;
    myfile.open("index.vhtml");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            /*cout << line << '\n';*/
            all += line;
            all += '\n';
        }
        myfile.close();
    }

    output.info("Loading context...");
    Context context;
    context.loadFile("context.json");
    /*context.access("site.title");*/

    output.info("Rendering site...");
    Node test;
    test.setContext(context);
    test.parse(all);

    output.info("Site rendered!");
    /*cout << test.openingTag << endl;
    cout << test.children.front().closingTag << endl;*/

    /*cout << test.render() << endl;*/
    /*cout << "\n\n\nOUTPUT:\n";*/
    /*cout << test.output << endl;*/

    return 0;
}