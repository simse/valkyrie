#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

#include "../utils/trim.hpp"
#include "node.hpp"
#include "text.hpp"
#include "show_statement.hpp"

using namespace std;

void Node::parse(string input)
{
    unordered_map<string, bool> flags = {
        {"CURLY_OPENING", false},
        {"CURLY_OPENED", false},
        {"CURLY_CLOSING", false},
        {"CURLY_CLOSED", false},
        {"VHTML_INTERPRETING", false},
        {"CURLY_JUST_CLOSED", false},
        {"TERMINATING", false}};
    unordered_map<string, string> tmp = {};
    unordered_map<string, int> runtime = {
        {"DEPTH", 0}};

    int length = input.length();
    int cursor = -1;
    string buffer;
    string stream;

    while (cursor++ < length)
    {
        char current_char = input[cursor];
        //cout << current_char << endl;

        if (flags["CURLY_JUST_CLOSED"])
        {
            flags["CURLY_JUST_CLOSED"] = false;
            flags["VHTML_INTERPRETING"] = false;
            buffer = "";
        }

        /* Stream all text outside vHTML into Text Nodes */
        if (!flags["VHTML_INTERPRETING"] && cursor < length)
        {
            stream.push_back(current_char);
        }
        else
        {
            if (stream != "")
            {
                // Clean up stream
                replace(stream.begin(), stream.end(), '{', '\0');
                replace(stream.begin(), stream.end(), '}', '\0');

                //cout << stream << endl;

                // Add text node child
                TextNode tmp_text(stream);
                output += tmp_text.render();
                stream = "";
            }
        }

        /* vHTML extension detection */
        if (!flags["CURLY_OPENING"] && current_char == '{')
        {
            
            flags["CURLY_OPENING"] = true;
            flags["VHTML_INTERPRETING"] = true;
            continue;
        }

        if (flags["CURLY_OPENING"] && current_char == '{')
        {
            flags["CURLY_OPENING"] = false;
            flags["CURLY_OPENED"] = true;
            flags["CURLY_CLOSED"] = false;
            continue;
        }

        if (!flags["CURLY_CLOSING"] && current_char == '}')
        {
            flags["CURLY_CLOSING"] = true;
            continue;
        }

        if (flags["CURLY_CLOSING"] && current_char == '}')
        {
            flags["CURLY_OPENED"] = false;
            flags["CURLY_CLOSING"] = false;
            flags["CURLY_CLOSED"] = true;
            flags["CURLY_JUST_CLOSED"] = true;
            flags["VHTML_INTERPRETING"] = false;
        }

        if (flags["CURLY_OPENED"])
        {
            buffer += current_char;
        }

        /* Evaluate */
        if (flags["CURLY_JUST_CLOSED"])
        {
            // Clean up keyword
            tmp["CURRENT_STATEMENT"] = trim(buffer);
            tmp["CURRENT_KEYWORD"];

            /*cout << tmp["CURRENT_STATEMENT"] << endl;*/

            // Determine keyword
            size_t spaces = count(tmp["CURRENT_STATEMENT"].begin(), tmp["CURRENT_STATEMENT"].end(), ' ');
            /*cout << spaces << endl;*/

            if (spaces == 0)
            {
                if (tmp["CURRENT_STATEMENT"] != "else")
                {
                    tmp["CURRENT_KEYWORD"] = "show";
                }
            }

            if (tmp["CURRENT_KEYWORD"] == "test")
            {
                cout << "Hello world!" << endl;
            }

            if (tmp["CURRENT_KEYWORD"] == "show")
            {
                /*cout << "{{show}} = " << tmp["CURRENT_STATEMENT"] << endl;*/
                ShowNode tmp_show(tmp["CURRENT_STATEMENT"]);
                output += tmp_show.render();
            }
            cout << tmp["CURRENT_KEYWORD"] << endl;
        }
    }
}
