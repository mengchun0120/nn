#include <string>
#include <iostream>
#include "config_parser.hpp"

using namespace std;

ConfigParser::ConfigParser(const char *file):
    in_(file)
{
}

ConfigParser::~ConfigParser()
{
    in_.close();
}

bool ConfigParser::next_config(string& key, string& value)
{
    if(!in_.good()) return false;

    string line;

    while(in_.good()) {
        getline(in_, line);
        if(line.length() > 0) {
            unsigned int equal_pos = line.find('=');
            key = line.substr(0, equal_pos);
            value = line.substr(equal_pos + 1, line.length() - equal_pos - 1);
            break;
        }
    }

    return true;
}
