#ifndef __CONFIG_PARSER_HPP__
#define __CONFIG_PARSER_HPP__

#include <fstream>
#include <string>

class ConfigParser {
public:
    ConfigParser(const char *file);

    virtual ~ConfigParser();

    bool next_config(std::string& key, std::string& value);

protected:
    std::ifstream in_;
};

#endif
