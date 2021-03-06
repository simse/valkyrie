/* valkyrie.cpp

 * Entry-point to the Valkyrie static site generator. This
 * is where all the magic of delegation happens.
 * 
 * Simon Sorensen (hello@simse.io)
 * 01/12/19
 */

#include <iostream>
#include <fstream>

#include "include/core/output.hpp"
#include "include/core/constants.hpp"
#include "include/utils/json.hpp"
#include "include/utils/args.hpp"
#include "include/nodes/node.hpp"
#include "include/core/context.hpp"

using namespace std;

int main(int argc, char **argv)
{
    /* Prepare to ouput to console */
    valkyrie::Output output;
    output.info("Loading Valkyrie " + valkyrie::VERSION);

    /* Parse input parameters */
    cxxopts::Options options("Valkyrie", "Crazy fast C++ static site generator");
    options.add_options()("d,debug", "Enable debugging")("t,template", "File name", cxxopts::value<std::string>());
    auto result = options.parse(argc, argv);

    cout << result["t"].as<string>() << endl;

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