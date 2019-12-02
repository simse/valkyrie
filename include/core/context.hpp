#include <iostream>
#include "../utils/json.hpp"


#pragma once

using namespace std;
using namespace nlohmann;

class Context {
    public:
        json context;
        void parse(string input);
        void loadFile(string input);
        void set(json input);
        json access(string key);
};