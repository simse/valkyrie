#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../libraries/json.hpp"
#include "context.hpp"

using namespace std;
using namespace nlohmann;

void Context::parse(string input)
{
    context = json::parse(input);
    /*cout << context["site"]["title"] << endl;*/
}

void Context::set(json input)
{
    context = input;
}

void Context::loadFile(string file)
{
    ifstream input(file);
    input >> context;
    input.close();
    context = context["context"];
}

json Context::access(string key)
{
    /* Split string by periods */
    istringstream iss(key);
    vector<string> tokens;
    string token;
    while (getline(iss, token, '.'))
    {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    /* Access value using loop */
    json buffer = context;
    for(auto const& value: tokens) {
        buffer = buffer[value];
    }
    
    return buffer;
}