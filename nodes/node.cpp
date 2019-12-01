#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

#include "../utils/trim.hpp"
#include "node.hpp"
#include "text.hpp"
#include "show_statement.hpp"
#include "if_statement.hpp"
#include "for_statement.hpp"

using namespace std;

void Node::setContext(Context input) {
    context = input;
}

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
    unordered_map<string, string> tmp = {
        {"CATCHING_FOR", ""},
        {"CATCHING_FOR_STREAM", ""}};
    unordered_map<string, int> runtime = {
        {"DEPTH", -1}};

    int length = input.length();
    int cursor = -1;
    string buffer;
    string stream;

    while (cursor++ < length)
    {
        char current_char = input[cursor];

        if (flags["CURLY_JUST_CLOSED"])
        {
            flags["CURLY_JUST_CLOSED"] = false;
            flags["VHTML_INTERPRETING"] = false;
            buffer = "";
        }

        /* Stream all text outside vHTML into Text Nodes */
        if (!flags["VHTML_INTERPRETING"] && cursor < length && runtime["DEPTH"] < 0)
        {
            stream.push_back(current_char);
        }
        else if(runtime["DEPTH"] >= 0 && cursor < length)
        {
            tmp["CATCHING_FOR_STREAM"].push_back(current_char);
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
            /*size_t spaces = count(tmp["CURRENT_STATEMENT"].begin(), tmp["CURRENT_STATEMENT"].end(), ' ');
            cout << spaces << endl;*/
            if (tmp["CURRENT_STATEMENT"].rfind("if", 0) == 0)
            {
                tmp["CURRENT_KEYWORD"] = "if";
            }
            else if (tmp["CURRENT_STATEMENT"].rfind("else", 0) == 0)
            {
                tmp["CURRENT_KEYWORD"] = "else";
            }
            else if (tmp["CURRENT_STATEMENT"].rfind("endif", 0) == 0)
            {
                tmp["CURRENT_KEYWORD"] = "endif";
            }
            else if (tmp["CURRENT_STATEMENT"].rfind("endelse", 0) == 0)
            {
                tmp["CURRENT_KEYWORD"] = "endelse";
            }
            else if (tmp["CURRENT_STATEMENT"].rfind("for", 0) == 0)
            {
                tmp["CURRENT_KEYWORD"] = "for";
            }
            else if (tmp["CURRENT_STATEMENT"].rfind("endfor", 0) == 0)
            {
                tmp["CURRENT_KEYWORD"] = "endfor";
            }
            else
            {
                tmp["CURRENT_KEYWORD"] = "show";
            }

            /* Take action on keyword */
            if (tmp["CURRENT_KEYWORD"] == "show" && runtime["DEPTH"] == -1)
            {
                /*cout << "{{show}} = " << tmp["CURRENT_STATEMENT"] << endl;*/
                ShowNode tmp_show(tmp["CURRENT_STATEMENT"]);
                tmp_show.setContext(context);
                output += tmp_show.render();
            }

            /* Handle if-statements */
            if (tmp["CURRENT_KEYWORD"] == "if" || tmp["CURRENT_KEYWORD"] == "for")
            {
                /* Depth of 0 indicates outer-most statement */
                runtime["DEPTH"]++;

                if(runtime["DEPTH"] == 0) {
                    tmp["CATCHING_FOR"] = tmp["CURRENT_STATEMENT"];
                }
            }
            else if (tmp["CURRENT_KEYWORD"] == "endif" || tmp["CURRENT_KEYWORD"] == "endfor")
            {
                runtime["DEPTH"]--;

                /* Detect if outer IF statement closed */
                if (runtime["DEPTH"] == -1 && tmp["CATCHING_FOR"].rfind("if", 0) == 0)
                {
                    // TODO: Dynamically remove {{ endif }} tag
                    tmp["CATCHING_FOR_STREAM"].erase(tmp["CATCHING_FOR_STREAM"].length()-11, 11);
                    
                    /* Debug */
                    /*cout << "IF statement just closed!" << endl;
                    cout << tmp["CATCHING_FOR_STREAM"] << endl;*/

                    IfNode tmp_if(trim(tmp["CATCHING_FOR"]), trim(tmp["CATCHING_FOR_STREAM"]));
                    tmp_if.setContext(context);
                    output += tmp_if.render();

                    /* Clear out temporary stream */
                    tmp["CATCHING_FOR_STREAM"] = "";
                }

                /* Detect if outer FOR statement closed */
                if (runtime["DEPTH"] == -1 && tmp["CATCHING_FOR"].rfind("for", 0) == 0)
                {
                    // TODO: Dynamically remove {{ endif }} tag
                    tmp["CATCHING_FOR_STREAM"].erase(tmp["CATCHING_FOR_STREAM"].length()-12, 12);
                    
                    /* Debug */
                    /*cout << "IF statement just closed!" << endl;
                    cout << tmp["CATCHING_FOR_STREAM"] << endl;*/

                    ForNode tmp_for(trim(tmp["CATCHING_FOR"]), trim(tmp["CATCHING_FOR_STREAM"]));
                    tmp_for.setContext(context);
                    output += tmp_for.render();

                    /* Clear out temporary stream */
                    tmp["CATCHING_FOR_STREAM"] = "";
                }
            }
        }
    }
}
