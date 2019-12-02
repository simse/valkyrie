/* valkyrie.cpp

 * Entry-point to the Valkyrie static site generator. This
 * is where all the magic of delegation happens.
 * 
 * Simon Sorensen (hello@simse.io)
 * 01/12/19
 */

#include <iostream>
#include <fstream>

#include "include/output.hpp"
#include "include/constants.hpp"
#include "include/json.hpp"
#include "include/node.hpp"
#include "include/context.hpp"

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
    output.success("Input template loaded");

    output.info("Loading context...");
    output.error("Failed to load context from context.json");
    Context context;
    context.loadFile("context.json");
    /*context.access("site.title");*/
    output.success("Context loaded");

    output.info("Rendering site...");
    Node test;
    test.console = output;
    test.setContext(context);
    test.parse(all);

    output.warning("Your formatting is shit!");

    output.success("Site rendered!");
    /*cout << test.openingTag << endl;
    cout << test.children.front().closingTag << endl;*/

    /*cout << test.render() << endl;*/
    /*cout << "\n\n\nOUTPUT:\n";*/
    /*cout << test.output << endl;*/


    return 0;
}