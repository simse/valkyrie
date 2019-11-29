#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Node
{
public:
    bool selfClosing;
    string openingTag;
    string closingTag;
    list<Node> children;
    unordered_map<string, string> context;

    string render()
    {
        return "";
    }

    void parse(string input)
    {
        unordered_map<string, bool> flags = {
            {"CURLY_OPENING", false},
            {"CURLY_OPENED", false},
            {"CURLY_CLOSING", false},
            {"CURLY_CLOSED", false},
            {"CURLY_JUST_CLOSED", false},
            {"TERMINATING", false}};
        unordered_map<string, string> tmp = {};
        unordered_map<string, int> runtime = {
            {"DEPTH", 0}};

        int length = input.length();
        int cursor = -1;
        string buffer;

        while (cursor++ < length)
        {
            char current_char = input[cursor];
            //cout << current_char << endl;

            if (flags["CURLY_JUST_CLOSED"])
            {
                flags["CURLY_JUST_CLOSED"] = false;
                buffer = "";
            }

            /* vHTML extension detection */
            if (!flags["CURLY_OPENING"] && current_char == '{')
            {
                flags["CURLY_OPENING"] = true;
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
            }

            if (flags["CURLY_OPENED"])
            {
                buffer += current_char;
            }

            /* Evaluate */
            if (flags["CURLY_JUST_CLOSED"])
            {
                cout << buffer << endl;

                // Clean up keyword
                tmp["CURRENT_STATEMENT"] = trim(buffer);
                tmp["CURRENT_KEYWORD"];

                for (char &c : tmp["CURRENT_STATEMENT"])
                {
                    
                }

                if (tmp["CURRENT_KEYWORD"] == "test")
                {
                    cout << "Hello world!" << endl;
                }
            }
        }
    }
};